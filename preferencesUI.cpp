#include "preferencesUI.h"
#include "ui_preferencesUI.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    showSettings(Settings::getInstance()->getSettings());
    setStateChange(false);

    connect(ui->btn_close, SIGNAL(released()), this, SLOT(closeCheck()));
    connect(this, SIGNAL(finished(int)), ui->btn_close, SLOT(click()));

    myCompleter = new QCompleter(this);
    myCompleter->setModel(new QDirModel(myCompleter));
    myCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    myCompleter->setCompletionMode(QCompleter::PopupCompletion);
    ui->lineEdit_appPath->setCompleter(myCompleter);
    ui->lineEdit_configFiles->setCompleter(myCompleter);
    ui->lineEdit_envValueMaya->setCompleter(myCompleter);
    ui->lineEdit_envValueRenderman->setCompleter(myCompleter);
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_toolButton_appPath_clicked()
{
    QSysInfo getOS;
    QFileInfo myExecFile;

    // If OS is MacOS go to Applications folder otherwise go to OS homePath
    if(getOS.productType() == "macos")
    {
        myExecFile = QFileDialog::getOpenFileName(this, tr("Open Files"),QDir::rootPath() + "/Applications", tr("Unix executable (denoise)"));
    }
    else
    {
        myExecFile = QFileDialog::getOpenFileName(this, tr("Open Files"),QDir::homePath(), tr("Executable file (denoise denoise.exe)"));
    }


    if(myExecFile.isExecutable())
    {
        ui->lineEdit_appPath->setText(myExecFile.absoluteFilePath());
    }
    else if(myExecFile.absoluteFilePath() != "")
    {
        QMessageBox::warning(this, "Warning!", "The selected file is not an executable file.");
    }

    if(myExecFile.absoluteFilePath() != Settings::getInstance()->getApplicationPath().toString())
    {
        setStateChange(true);
    }
}

void Preferences::on_toolButton_configFiles_clicked()
{
    QSysInfo getOS;
    QDir myDir;

    // If OS is MacOS go to Applications folder otherwise go to OS Home
    if(getOS.productType() == "macos")
    {
        myDir = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::rootPath() + "/Applications", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        myDir = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }

    if(myDir.exists())
    {
        ui->lineEdit_configFiles->setText(myDir.absolutePath());
        setStateChange(true);
    }
}

void Preferences::on_btn_save_clicked()
{
    saveSettings();
    setStateChange(false);
}

void Preferences::saveSettings()
{
    Settings::getInstance()->setSettings(ui->lineEdit_appPath->text().simplified(),
                                          ui->lineEdit_configFiles->text().simplified(),
                                          ui->lineEdit_envKeyRenderman->text().simplified(),
                                          ui->lineEdit_envValueRenderman->text().simplified(),
                                          ui->lineEdit_envKeyMaya->text().simplified(),
                                          ui->lineEdit_envValueMaya->text().simplified(),
                                          ui->lineEdit_envKeyPath->text().simplified(),
                                          ui->lineEdit_envValuePath->text().simplified() );

}

void Preferences::showSettings(const QStringList &value)
{
    ui->lineEdit_appPath->setText(value.at(0));
    ui->lineEdit_configFiles->setText(value.at(1));
    ui->lineEdit_envKeyRenderman->setText(value.at(2));
    ui->lineEdit_envValueRenderman->setText(value.at(3));
    ui->lineEdit_envKeyMaya->setText(value.at(4));
    ui->lineEdit_envValueMaya->setText(value.at(5));
    ui->lineEdit_envKeyPath->setText(value.at(6));
    ui->lineEdit_envValuePath->setText(value.at(7));
}

void Preferences::on_btn_loadDefault_clicked()
{
    showSettings(Settings::getInstance()->getDefaultSettings());
    setStateChange(true);
}

void Preferences::on_lineEdit_appPath_editingFinished()
{
    QFileInfo file(ui->lineEdit_appPath->text());

    if(file.isFile())
    {
        if(file.isExecutable())
        {
            //qDebug() << "This is a executable file";
            if(ui->lineEdit_appPath->text() == Settings::getInstance()->getApplicationPath().toString())
            {
                setStateChange(false);
            }
            else
            {
                setStateChange(true);
            }
        }
        else
        {
            //qDebug() << "This is not an executable file";
            ui->lineEdit_appPath->setText(Settings::getInstance()->getApplicationPath().toString());
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", QString("The selected file: \n" + ui->lineEdit_appPath->text() + "\n is not an acceptable file."));
        ui->lineEdit_appPath->setText(Settings::getInstance()->getApplicationPath().toString());
    }
}

void Preferences::on_lineEdit_configFiles_editingFinished()
{
    QDir directory(ui->lineEdit_configFiles->text());

    if(!directory.exists())
    {
        QMessageBox::warning(this, "Warning!", "The directory selected does not exist!");
        ui->lineEdit_configFiles->setText(Settings::getInstance()->getConfigFilesPath().toString());
    }
}

void Preferences::closeCheck()
{
    if(isStateChange() == true)
    {
        QMessageBox::StandardButton msg;
        msg = QMessageBox::question(this, "Settings Change", "Your setting change, do you want save new setting?", QMessageBox::Yes | QMessageBox::No);

        switch (msg) {
        case QMessageBox::Yes:
            // saveSettings
            saveSettings();
            break;
        default:
            break;
        }
    }

    emit preferencesUpdate();
    setStateChange(false);
    close();
}

void Preferences::on_lineEdit_appPath_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getApplicationPath().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_configFiles_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getConfigFilesPath().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envKeyRenderman_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvKeyRenderman().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envValueRenderman_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvValueRenderman().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envKeyMaya_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvKeyMaya().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envValueMaya_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvValueMaya().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envKeyPath_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvKeyPath().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

void Preferences::on_lineEdit_envValuePath_textChanged(const QString &arg1)
{
    if(arg1 == Settings::getInstance()->getEnvValuePath().toString())
    {
        setStateChange(false);
    }
    else
    {
        setStateChange(true);
    }
}

bool Preferences::isStateChange() const
{
    return stateChange;
}

void Preferences::setStateChange(const bool &value)
{
    stateChange = value;
}
