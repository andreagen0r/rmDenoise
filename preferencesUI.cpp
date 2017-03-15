#include "preferencesUI.h"
#include "ui_preferencesUI.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    showSettings();
    setStateChange(false);
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_toolButton_appPath_clicked()
{
    QSysInfo getOS; // Get OS infos
    QString fileName;

    if(getOS.productType() == "macos") // If OS is MacOS go to Applications folder otherwise go to OS homePath
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open Files"),QDir::rootPath() + "/Applications", tr("Unix executable (denoise denoise.exe)"));
    }
    else
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open Files"),QDir::homePath(), tr("Unix executable (denoise denoise.exe)"));
    }

    QFileInfo unixExec(fileName); // Get selected file infos

    if(unixExec.isExecutable() == true) // Check if selected file is a executable
    {
        ui->lineEdit_appPath->setText(fileName);
    }
    else if(fileName != "")
    {
        QMessageBox::warning(this, "Warning!", "The selected file is not an executable file.");
    }

    if(fileName != Settings::getInstance()->getApplicationPath().toString())
    {
        setStateChange(true);
    }

    //        qDebug() << getOS.productType();
    //        qDebug() << unixExec.isExecutable();
    //        qDebug() << fileName;
}

void Preferences::on_toolButton_configFiles_clicked()
{
    QSysInfo getOS; // Get OS infos
    QString dirName;

    if(getOS.productType() == "macos") // If OS is MacOS go to Applications folder otherwise go to OS homePath
    {
        dirName = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::rootPath() + "/Applications", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        dirName = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }

    QDir directory(dirName); // Get selected directory infos

    if(directory.exists()) // Check if directory exist
    {
        ui->lineEdit_configFiles->setText(dirName);
        setStateChange(true);
    }
}

void Preferences::on_btn_save_clicked()
{
    saveSettings();
    setStateChange(false);
    emit configFilesUpdate();
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

void Preferences::showSettings()
{
    QStringList myList = Settings::getInstance()->getSettings();

    ui->lineEdit_appPath->setText(myList.at(0));
    ui->lineEdit_configFiles->setText(myList.at(1));
    ui->lineEdit_envKeyRenderman->setText(myList.at(2));
    ui->lineEdit_envValueRenderman->setText(myList.at(3));
    ui->lineEdit_envKeyMaya->setText(myList.at(4));
    ui->lineEdit_envValueMaya->setText(myList.at(5));
    ui->lineEdit_envKeyPath->setText(myList.at(6));
    ui->lineEdit_envValuePath->setText(myList.at(7));
}

void Preferences::on_btn_loadDefault_clicked()
{
    QStringList myList = Settings::getInstance()->getDefaultSettings();

    ui->lineEdit_appPath->setText(myList.at(0));
    ui->lineEdit_configFiles->setText(myList.at(1));
    ui->lineEdit_envKeyRenderman->setText(myList.at(2));
    ui->lineEdit_envValueRenderman->setText(myList.at(3));
    ui->lineEdit_envKeyMaya->setText(myList.at(4));
    ui->lineEdit_envValueMaya->setText(myList.at(5));
    ui->lineEdit_envKeyPath->setText(myList.at(6));
    ui->lineEdit_envValuePath->setText(myList.at(7));

    setStateChange(true);
}

void Preferences::on_btn_close_clicked()
{
    if(getStateChange() == true)
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

    showSettings();
    emit configFilesUpdate();
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

void Preferences::on_lineEdit_appPath_editingFinished()
{
    QFileInfo file(ui->lineEdit_appPath->text()); // Get selected file infos

    if(file.isFile()) // Check if file or directory exist
    {
        //qDebug() << "É um arquivo";
        if(file.isExecutable()) // Check if selected file is a executable
        {
            //qDebug() << "É um arquivo executável";
            if(ui->lineEdit_appPath->text() == Settings::getInstance()->getApplicationPath().toString())
            {
                setStateChange(false);
                //qDebug() << "nivel 3";
            }
            else
            {
                setStateChange(true);
            }
        }
        else
        {
            //qDebug() << "Não é um arquivo executável";
            ui->lineEdit_appPath->setText(Settings::getInstance()->getApplicationPath().toString());
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", QString("The selected file: \n" + ui->lineEdit_appPath->text() + "\n is not an acceptable file." ));
        ui->lineEdit_appPath->setText(Settings::getInstance()->getApplicationPath().toString());
        //qDebug() << "Não é um arquivo";
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

void Preferences::on_lineEdit_configFiles_editingFinished()
{
    QDir directory(ui->lineEdit_configFiles->text()); // Get selected directory infos

    if(!directory.exists()) // Check if directory exist
    {
        QMessageBox::warning(this, "Warning!", "The directory selected dosen't exist!");
        ui->lineEdit_configFiles->setText(Settings::getInstance()->getConfigFilesPath().toString());
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

bool Preferences::getStateChange() const
{
    return stateChange;
}

void Preferences::setStateChange(bool value)
{
    stateChange = value;
}
