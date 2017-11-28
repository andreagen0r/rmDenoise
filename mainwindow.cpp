#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

#include <QSettings>
#include <QCompleter>
#include <QTimer>
#include <QDirModel>
#include <QFileDialog>
#include <QThread>
#include <QMessageBox>
#include <QRegularExpression>
#include <QProgressDialog>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_pxrDenoise(new PXRDenoise),
      m_timer(new QTimer(this)),
      m_completer(new QCompleter)
{
    ui->setupUi(this);

    this->setWindowTitle(APP_PRODUCT);

    // Load default settings at first time
    loadFirstTime();

    // Load *.json config files to listwidget
    loadConfigFiles();

    // Verify how many threads there are in the computer and set the max number of threads to the spinBox
    ui->spnBox_threads->setMaximum(QThread::idealThreadCount());

    ui->lineEdit_imagePath->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_layers->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_name->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_outdir->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_override->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->spnBox_threads->setAttribute(Qt::WA_MacShowFocusRect, 0);

    // Connect UI elements
    connect(ui->chbox_o, &QCheckBox::toggled, ui->lineEdit_name, &QLineEdit::setEnabled);
    connect(ui->chbox_outdir, &QCheckBox::toggled, ui->lineEdit_outdir, &QLineEdit::setEnabled);
    connect(ui->chbox_outdir, &QCheckBox::toggled, ui->btn_outDir, &QPushButton::setEnabled);
    connect(ui->chbox_f, &QCheckBox::toggled, ui->listWidget_configFiles, &QListWidget::setEnabled);
    connect(ui->chbox_crossframe, &QCheckBox::toggled, ui->chbox_skipfirst, &QCheckBox::setEnabled);
    connect(ui->chbox_crossframe, &QCheckBox::toggled, ui->chbox_skiplast, &QCheckBox::setEnabled);
    connect(ui->chbox_crossframe, &QCheckBox::toggled, ui->chbox_v, &QCheckBox::setEnabled);
    connect(ui->chbox_layers, &QCheckBox::toggled, ui->lineEdit_layers, &QLineEdit::setEnabled);
    connect(ui->chbox_t, &QCheckBox::toggled, ui->spnBox_threads, &QSpinBox::setEnabled);
    connect(ui->chbox_override, &QCheckBox::toggled, ui->lineEdit_override, &QLineEdit::setEnabled);
    connect(ui->btn_close, &QPushButton::released, this, &MainWindow::close);
    connect(m_pxrDenoise.get(), &PXRDenoise::renderStatus, this, &MainWindow::renderStatus);
    connect(m_pxrDenoise.get(), &PXRDenoise::renderOutputMessage, this, &MainWindow::statusBarMsg);
    connect(m_timer.get(), &QTimer::timeout, this, &MainWindow::renderProgress);


    m_completer->setModel(new QDirModel(m_completer.get()));
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->lineEdit_imagePath->setCompleter(m_completer.get());
    ui->lineEdit_outdir->setCompleter(m_completer.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_run_clicked()
{
    QString msg;

    if(ui->lineEdit_imagePath->text() != "")
    {
        if(checkImages(ui->lineEdit_imagePath->text().simplified().split(QRegularExpression("\\s+"))))
        {
            if(ui->lineEdit_outdir->isEnabled())
            {
                if(checkDir(ui->lineEdit_outdir->text()))
                {
                    // Render...
                    msg = render();
                }
                else
                {
                    QMessageBox::information(this, tr("Information!"), tr("Cannot render because the selected directory is not valid!"));
                }
            }
            else
            {
                // Render...
                msg = render();
            }
        }
        else
        {
            QStringList files = notValidImages(ui->lineEdit_imagePath->text().simplified().split(QRegularExpression("\\s+")));
            msg = tr("Some file(s) don't exist:\n");
            foreach (QString item, files)
            {
                msg+=item + "\n";
            }
        }
    }
    else
    {
        msg = tr("No image(s) selected!");
    }

    ui->statusBar->clearMessage();
    ui->textEdit_commandLine->setText(msg);
}

QString MainWindow::render()
{
    //Call method to create a Flag line
    createFlagLine();

    // Start render in new thread
    m_pxrDenoise->start();


    // Show output command line
    QString commandLine = "denoise";
    foreach (QString item, m_pxrDenoise->getCommandLine())
    {
        commandLine += " " + item;
    }

    return commandLine;
}

void MainWindow::on_btn_ImagePath_clicked()
{
    QDir path;
    if(!m_flagImages.isEmpty())
    {
        path = m_flagImages.at(0);
    }
    else
    {
        path = QDir::homePath();
    }

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), path.path(), tr("Images (*.exr)"));
    m_flagImages = fileNames;
    ui->lineEdit_imagePath->setText(fileNames.join(" "));
}

void MainWindow::on_lineEdit_imagePath_editingFinished()
{
     ui->lineEdit_imagePath->setText(ui->lineEdit_imagePath->text().simplified());
     m_flagImages = ui->lineEdit_imagePath->text().split(QRegularExpression("\\s+"));
}

void MainWindow::on_lineEdit_name_editingFinished()
{
    ui->lineEdit_name->setText(ui->lineEdit_name->text().replace(QRegularExpression("\\s+"), "_"));
}

void MainWindow::on_btn_outDir_clicked()
{
    QDir path;
    if(!m_flagImages.isEmpty())
    {
        path = m_flagImages.at(0);
    }
    else
    {
        path = QDir::homePath();
    }

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), path.path(), QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty() && !dir.isNull())
    {
        ui->lineEdit_outdir->setText(dir);
    }
    else
    {
        ui->lineEdit_outdir->clear();
    }
}

void MainWindow::on_lineEdit_outdir_editingFinished()
{
    checkDir(ui->lineEdit_outdir->text().simplified());
}

void MainWindow::on_chbox_crossframe_stateChanged(int arg1)
{
    if(!arg1)
    {
        ui->chbox_skipfirst->setChecked(false);
        ui->chbox_skiplast->setChecked(false);
        ui->chbox_v->setChecked(false);
    }
}

void MainWindow::createFlagLine()
{
    QStringList tmpFlag;

    // Flag -o (Output name)
    if(ui->chbox_o->isChecked())
    {
        if(ui->lineEdit_name->text() != "")
        {
            m_flagName = ui->lineEdit_name->text();
            tmpFlag.append("-o");
            tmpFlag.append(m_flagName);
        }
    }

    // Flag --outdir (Output Directory)
    if(ui->chbox_outdir->isChecked())
    {
        if(ui->lineEdit_outdir->text() != "")
        {
            m_flagOutDir = ui->lineEdit_outdir->text();
            tmpFlag.append("--outdir");
            tmpFlag.append(m_flagOutDir.path());
        }
    }

    // Flag --filtervariance
    if(ui->chbox_filtervariance->isChecked())
    {
        tmpFlag.append("--filtervariance");
    }

    // Flag -v (Motion Vectors)
    if(ui->chbox_v->isChecked())
    {
        tmpFlag.append("-v");
        tmpFlag.append("variance");
    }

    // Flag --crossframe (Cross-Frame)
    if(ui->chbox_crossframe->isChecked())
    {
        tmpFlag.append("--crossframe");
    }

    // Flag --skipfirst, -F, -L (Skip First Frame)
    if(ui->chbox_skipfirst->isChecked())
    {
        tmpFlag.append("--skipfirst");
    }

    // Flag --skiplast, -L (Skip Last Frame)
    if(ui->chbox_skiplast->isChecked())
    {
        tmpFlag.append("--skiplast");
    }

    // Flag --layers (Layers)
    if(ui->chbox_layers->isChecked())
    {
        if(ui->lineEdit_layers->text() != "")
        {
            m_flagLayers = ui->lineEdit_layers->text();
            tmpFlag.append("--layers");
            tmpFlag.append(m_flagLayers);
        }
    }

    // Flag -f (Config. Files)
    if(ui->chbox_f->isChecked())
    {
        // Set configFiles
        QList<QString> selectedFiles;
        foreach (QListWidgetItem *item, ui->listWidget_configFiles->selectedItems())
        {
            selectedFiles.append(item->text());
        }
        QStringList mflag;
        foreach (QString item, selectedFiles)
        {
            mflag.append("-f");
            mflag.append(item);
        }
        m_flagConfigFiles = mflag;

        tmpFlag.append(m_flagConfigFiles);
    }

    // Flag -t (Thread)
    if(ui->chbox_t->isChecked())
    {
        m_flagThreads = ui->spnBox_threads->value();
        tmpFlag.append("-t");
        tmpFlag.append(QString::number(m_flagThreads));
    }

    // Flag --override (Override)
    if(ui->chbox_override->isChecked())
    {
        if(ui->lineEdit_override->text() != "")
        {
            // Set override
            QRegularExpression exp = QRegularExpression("\\s+(?!\\d+])");
            QStringList myList = ui->lineEdit_override->text().split(exp);
            m_flagOverride = myList;

            tmpFlag.append("--override");
            tmpFlag.append(m_flagOverride);
        }
    }

    // Image Path
    if(ui->lineEdit_imagePath->text() != "")
    {
        m_flagImages = ui->lineEdit_imagePath->text().split(QRegularExpression("\\s+"));
        tmpFlag.append(m_flagImages);
    }

    // Flag -n (Output basename)
    if(ui->chbox_n->isChecked())
    {
        tmpFlag.append("-n");
    }

    m_pxrDenoise->setCommandLine(tmpFlag);
}

void MainWindow::loadFirstTime()
{
    QHash<QString, QString> m_hash{Settings::getInstance().getSettings()};

    if( ! m_hash.contains(Settings::FIRST_TIME))
    {
        // First time
        m_hash[Settings::FIRST_TIME] = QStringLiteral("1");
        Settings::getInstance().setSettings(m_hash);
        Settings::getInstance().setSettings(Settings::getInstance().getDefaultSettings());
    }
}

void MainWindow::on_actionAboutQT_triggered()
{
    QMessageBox::aboutQt(this, "About QT");
}

void MainWindow::on_actionAbout_triggered()
{
    QString aboutCaption;
    aboutCaption = QMessageBox::tr("<h3>About %1</h3>"
                                   "<p>Version %2</p>").arg(APP_PRODUCT, APP_VERSION);
    QString AboutBodyText;
    AboutBodyText = QMessageBox::tr(
                "<p>%1 is a Graphic User Interface for Renderman Denoise Tool.<br>"
                "<p>Hyperion Denoising Filter <br>"
                "Copyright (c) 2014-2017 Walt Disney Animation Studios. <br>"
                "For more information about Renderman and denoise filter visit <a href=\"http://%2\">%2</a><br>"
                "<p>Created by André Agenor <a href=\"http://%3\">%3</a>.<br>"
                "Windows version deployed by Arleson Tonnera.<br>"
                "Visit the <a href=\"http://%4/andreagen0r/rmDenoise\">%4</a> for the source code.</p>"
                "All rights reserved to your respective owners.</p>"
                ).arg((APP_PRODUCT),
                      QStringLiteral("renderman.pixar.com"),
                      QStringLiteral("andreagenor.com"),
                      QStringLiteral("github.com"));

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("About %1").arg(APP_PRODUCT));
    msgBox.setText(aboutCaption);
    msgBox.setInformativeText(AboutBodyText);

    QPixmap pm(QStringLiteral(":/app-64.png"));
    if (!pm.isNull())
    {
        msgBox.setIconPixmap(pm);
    }

    msgBox.exec();
}

void MainWindow::on_actionPreferences_triggered()
{
    Preferences m_prefUi(this);
    m_prefUi.exec();
    loadConfigFiles();
}

void MainWindow::renderStatus(const bool &arg1)
{
    if(arg1)
    {
        m_timer->start(10);
    }
    else
    {
        m_timer->stop();
        ui->progressBar->setValue(100);
    }
}

void MainWindow::renderProgress()
{
    m_progress += 1;
    if(m_progress >= 100)
    {
        m_progress = 0;
    }

    ui->progressBar->setValue(m_progress);
}

void MainWindow::statusBarMsg(const QString &value)
{
    QStringList myList = value.split("\n", QString::SkipEmptyParts);
    ui->statusBar->showMessage(myList.at(myList.length()-1));
}

void MainWindow::loadConfigFiles()
{
    QDir configFiles(Settings::getInstance().getSettings().value(Settings::getInstance().CONFIG_FILES));
    configFiles.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QStringList myList(configFiles.entryList(QStringList(QStringLiteral("*.json"))));

    if(!myList.isEmpty())
    {
        ui->listWidget_configFiles->clear();
        ui->listWidget_configFiles->addItems(myList);
        ui->listWidget_configFiles->setCurrentRow(0);
        ui->chbox_f->setEnabled(true);
    }
    else
    {
        ui->listWidget_configFiles->clear();
        ui->chbox_f->setEnabled(false);
    }
}



bool MainWindow::checkImages(const QStringList &value)
{
    bool result;

    if(value.isEmpty())
    {
        result = false;
    }
    else
    {
        QFileInfo selectedFiles;
        foreach (QString file, value)
        {
            selectedFiles = file;
            if(selectedFiles.exists() && selectedFiles.isFile())
            {
                if(selectedFiles.suffix() == "exr" || selectedFiles.suffix() == "EXR" )
                {
                    //qDebug() << "The file suffix is ok!";
                    result = true;
                }
            }
            else
            {
                //qDebug() << "The file doesn't exist";
                result = false;
                break;
            }
        }
    }

    return result;
}

QStringList MainWindow::notValidImages(const QStringList &value)
{
    QStringList result;

    if(!value.isEmpty())
    {
        QFileInfo selectedFiles;

        foreach (QString file, value)
        {
            selectedFiles = file;
            if(!selectedFiles.exists() && !selectedFiles.isFile())
            {
                result.append(file);
            }
        }
    }

    return result; // List of invalid images
}

QStringList MainWindow::validImages(const QStringList &value)
{
    QStringList result;

    if(!value.isEmpty())
    {
        QFileInfo selectedFiles;

        foreach (QString file, value)
        {
            selectedFiles = file;
            if(selectedFiles.exists() && selectedFiles.isFile())
            {
                if(selectedFiles.suffix() == "exr" || selectedFiles.suffix() == "EXR" )
                {
                    result.append(file);
                }
            }
        }
    }

    return result; // List of valid images
}

bool MainWindow::checkDir(const QString &value)
{
    bool result;

    if(value.isEmpty() || value.isNull())
    {
        result = false;
    }
    else
    {
        QDir outDir(value);

        if((!outDir.exists() && outDir.path() != "") || outDir.path() == QDir::separator() || outDir.path() == ".")
        {
            result = false;
        }
        else
        {
            result = true;
        }
    }

    return result;
}

