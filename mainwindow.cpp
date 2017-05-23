#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prefUi = new Preferences(this);
    pxrD = new PXRDenoise;
    timer = new QTimer(this);
    utl = new Utils(this);

    connect(prefUi, SIGNAL(preferencesUpdate()), this, SLOT(loadConfigFiles()));
    emit prefUi->preferencesUpdate();

    // Verify how many threads there are in the computer and set the max number of threads to the spinBox
    ui->spnBox_threads->setMaximum(QThread::idealThreadCount());

    ui->lineEdit_imagePath->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_layers->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_name->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_outdir->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->lineEdit_override->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->spnBox_threads->setAttribute(Qt::WA_MacShowFocusRect, 0);

    // Connect UI elements
    connect(ui->chbox_o, SIGNAL(toggled(bool)), ui->lineEdit_name, SLOT(setEnabled(bool)));
    connect(ui->chbox_outdir, SIGNAL(toggled(bool)), ui->lineEdit_outdir, SLOT(setEnabled(bool)));
    connect(ui->chbox_outdir, SIGNAL(toggled(bool)), ui->btn_outDir, SLOT(setEnabled(bool)));
    connect(ui->chbox_f, SIGNAL(toggled(bool)), ui->listWidget_configFiles, SLOT(setEnabled(bool)));
    connect(ui->chbox_crossframe, SIGNAL(toggled(bool)), ui->chbox_skipfirst, SLOT(setEnabled(bool)));
    connect(ui->chbox_crossframe, SIGNAL(toggled(bool)), ui->chbox_skiplast, SLOT(setEnabled(bool)));
    connect(ui->chbox_crossframe, SIGNAL(toggled(bool)), ui->chbox_v, SLOT(setEnabled(bool)));
    connect(ui->chbox_layers, SIGNAL(toggled(bool)), ui->lineEdit_layers, SLOT(setEnabled(bool)));
    connect(ui->chbox_t, SIGNAL(toggled(bool)), ui->spnBox_threads, SLOT(setEnabled(bool)));
    connect(ui->chbox_override, SIGNAL(toggled(bool)), ui->lineEdit_override, SLOT(setEnabled(bool)));

    connect(ui->btn_close, SIGNAL(released()), this, SLOT(close()));

    connect(pxrD, SIGNAL(renderStatus(bool)), this, SLOT(renderStatus(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(renderProgress()));

    connect(pxrD, SIGNAL(renderOutputMessage(QString)), this, SLOT(statusBarMsg(QString)));
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
        if(utl->checkImages(ui->lineEdit_imagePath->text().simplified().split(QRegularExpression("\\s+"))))
        {
            if(ui->lineEdit_outdir->isEnabled())
            {
                if(utl->checkDir(ui->lineEdit_outdir->text()))
                {
                    // Render...
                    msg = render();
                }
                else
                {
                    QMessageBox::information(this, "Information!", "Cannot render because the selected directory is not valid!");
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
            QStringList files = utl->notValidImages(ui->lineEdit_imagePath->text().simplified().split(QRegularExpression("\\s+")));
            msg = "Some file(s) don't exist:\n";
            foreach (QString item, files)
            {
                msg+=item + "\n";
            }
        }
    }
    else
    {
        msg = "No image(s) selected!";
    }

    ui->statusBar->clearMessage();
    ui->textEdit_commandLine->setText(msg);
}

QString MainWindow::render()
{
    //Call method to create a Flag line
    createFlagLine();

    // Start render in new thread
    pxrD->start();


    // Show output command line
    QString commandLine = "denoise";
    foreach (QString item, pxrD->getFlagLine())
    {
        commandLine += " " + item;
    }

    return commandLine;
}

void MainWindow::on_btn_ImagePath_clicked()
{
    QDir path;
    if(!getFlag_images().isEmpty())
    {
        path = getFlag_images().at(0);
    }
    else
    {
        path = QDir::homePath();
    }

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"), path.path(), tr("Images (*.exr)"));
    setFlag_images(fileNames);
    ui->lineEdit_imagePath->setText(fileNames.join(" "));
}

void MainWindow::on_lineEdit_imagePath_editingFinished()
{
     ui->lineEdit_imagePath->setText(ui->lineEdit_imagePath->text().simplified());
     setFlag_images(ui->lineEdit_imagePath->text().split(QRegularExpression("\\s+")));
}

void MainWindow::on_lineEdit_name_editingFinished()
{
    ui->lineEdit_name->setText(ui->lineEdit_name->text().replace(QRegularExpression("\\s+"), "_"));
}

void MainWindow::on_btn_outDir_clicked()
{
    QDir path;
    if(!getFlag_images().isEmpty())
    {
        path = getFlag_images().at(0);
    }
    else
    {
        path = QDir::homePath();
    }

    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", path.path(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

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
    utl->checkDir(ui->lineEdit_outdir->text().simplified());
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
            setFlag_name(ui->lineEdit_name->text());
            tmpFlag.append("-o");
            tmpFlag.append(getFlag_name());
        }
    }

    // Flag --outdir (Output Directory)
    if(ui->chbox_outdir->isChecked())
    {
        if(ui->lineEdit_outdir->text() != "")
        {
            setFlag_outDir(ui->lineEdit_outdir->text());
            tmpFlag.append("--outdir");
            tmpFlag.append(getFlag_outDir().path());
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
            setFlag_layers(ui->lineEdit_layers->text());
            tmpFlag.append("--layers");
            tmpFlag.append(getFlag_layers());
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
        setFlag_configFiles(mflag);

        tmpFlag.append(getFlag_configFiles());
    }

    // Flag -t (Thread)
    if(ui->chbox_t->isChecked())
    {
        setFlag_Threads(ui->spnBox_threads->value());
        tmpFlag.append("-t");
        tmpFlag.append(QString::number(getFlag_Threads()));
    }

    // Flag --override (Override)
    if(ui->chbox_override->isChecked())
    {
        if(ui->lineEdit_override->text() != "")
        {
            // Set override
            QRegularExpression exp = QRegularExpression("\\s+(?!\\d+])");
            QStringList myList = ui->lineEdit_override->text().split(exp);
            setFlag_override(myList);

            tmpFlag.append("--override");
            tmpFlag.append(getFlag_override());
        }
    }

    // Image Path
    if(ui->lineEdit_imagePath->text() != "")
    {
        setFlag_images(ui->lineEdit_imagePath->text().split(QRegularExpression("\\s+")));
        tmpFlag.append(getFlag_images());
    }

    // Flag -n (Output basename)
    if(ui->chbox_n->isChecked())
    {
        tmpFlag.append("-n");
    }

    pxrD->setFlagLine(tmpFlag);
}

void MainWindow::on_actionAboutQT_triggered()
{
    QMessageBox::aboutQt(this, "About QT");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox about;

    about.setWindowTitle("About Denoise UI for Renderman");
    about.setTextFormat(Qt::RichText);
    about.setStandardButtons(QMessageBox::Ok);
    about.setText("Hyperion Denoising Filter<br/>"
                  "Copyright (c) 2014-2017 Walt Disney Animation Studios.<br/>"
                  "RenderMan 21.3 version<br/><br/>"
                  "Denoise UI for Renderman<br/>"
                  "Created by André Agenor<br/>"
                  "Behance: <a href=\"http://www.behance.net/andreagenor\">www.behance.net/andreagenor</a>");

    about.exec();
}

void MainWindow::on_actionPreferences_triggered()
{
    prefUi->exec();
}

QString MainWindow::getFlag_name() const
{
    return flag_name;
}

void MainWindow::setFlag_name(const QString &value)
{
    flag_name = value;
}

QDir MainWindow::getFlag_outDir() const
{
    return flag_outDir;
}

void MainWindow::setFlag_outDir(const QDir &value)
{
    flag_outDir = value;
}

QStringList MainWindow::getFlag_images() const
{
    return flag_images;
}

void MainWindow::setFlag_images(const QStringList &value)
{
    flag_images = value;
}

QString MainWindow::getFlag_layers() const
{
    return flag_layers;
}

void MainWindow::setFlag_layers(const QString &value)
{
    flag_layers = value;
}

QStringList MainWindow::getFlag_override() const
{
    return flag_override;
}

void MainWindow::setFlag_override(const QStringList &value)
{
    flag_override = value;
}

int MainWindow::getFlag_Threads() const
{
    return flag_Threads;
}

void MainWindow::setFlag_Threads(const int &value)
{
    flag_Threads = value;
}

int MainWindow::getProg() const
{
    return prog;
}

void MainWindow::setProg(const int &value)
{
    prog = value;
}

QStringList MainWindow::getFlag_configFiles() const
{
    return flag_configFiles;
}

void MainWindow::setFlag_configFiles(const QStringList &value)
{
    flag_configFiles = value;
}

void MainWindow::renderStatus(const bool &arg1)
{
    if(arg1)
    {
        timer->start(10);
    }
    else
    {
        timer->stop();
        ui->progressBar->setValue(100);
    }
}

void MainWindow::renderProgress()
{
    setProg(getProg()+1);
    if(getProg() >= 100)
    {
        setProg(0);
    }

    ui->progressBar->setValue(getProg());
}

void MainWindow::statusBarMsg(const QString &value)
{
    QStringList myList = value.split("\n", QString::SkipEmptyParts);
    ui->statusBar->showMessage(myList.at(myList.length()-1));
}

void MainWindow::loadConfigFiles()
{
    QDir configFiles(Settings::getInstance()->getConfigFilesPath().toString());
    configFiles.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QStringList fileFilters;
    fileFilters.append("*.json"); // Filter to only read *.json files
    QStringList myList = configFiles.entryList(fileFilters);

    if(!myList.isEmpty())
    {
        // Load config files to configFiles
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
