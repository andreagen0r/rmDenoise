#include "preferencesUI.h"
#include "ui_preferencesUI.h"

Preferences::Preferences(QWidget *parent) : QDialog(parent), ui(new Ui::Preferences)
{
    ui->setupUi(this);

    readSettings();
    m_isStateChange = false;

    connect(ui->btn_close, &QPushButton::released, this, &Preferences::closeCheck);
    connect(this, &Preferences::finished, ui->btn_close, &QPushButton::click);

    m_Completer = new QCompleter(this);
    m_Completer->setModel(new QDirModel(m_Completer));
    m_Completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_Completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->lineEdit_appPath->setCompleter(m_Completer);
    ui->lineEdit_configFiles->setCompleter(m_Completer);
    ui->lineEdit_envValueMaya->setCompleter(m_Completer);
    ui->lineEdit_envValueRenderman->setCompleter(m_Completer);
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_toolButton_appPath_clicked()
{
    QFileInfo myExecFile;

#ifdef __APPLE__
    myExecFile = QFileDialog::getOpenFileName(this, tr("Open Files"), QDir::rootPath() +
                                              "/Applications/Pixar/", tr("Unix executable (denoise)"));
#else
    myExecFile = QFileDialog::getOpenFileName(this, tr("Open Files"), QDir::homePath(),
                                              tr("Executable file (denoise denoise.exe)"));
#endif

    if(myExecFile.isExecutable())
    {
        ui->lineEdit_appPath->setText(myExecFile.absoluteFilePath());
    }
    else if(myExecFile.absoluteFilePath() != "")
    {
        QMessageBox::warning(this, "Warning!", "The selected file is not an executable file.");
    }

    if(myExecFile.absoluteFilePath() != Settings::getInstance().getSettings().value(
                Settings::getInstance().APPLICATION_PATH).toString())
    {
        m_isStateChange = true;
    }
}

void Preferences::on_toolButton_configFiles_clicked()
{
    QDir myDir;

#ifdef __APPLE__
    myDir = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::rootPath() + "/Applications/Pixar",
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
    myDir = QFileDialog::getExistingDirectory(this, "Open Directory", QDir::homePath(),
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif


    if(myDir.exists())
    {
        ui->lineEdit_configFiles->setText(myDir.absolutePath());
        m_isStateChange = true;
    }
}

void Preferences::on_btn_save_clicked()
{
    saveSettings();
    m_isStateChange = false;
}

void Preferences::saveSettings()
{
    QMap<QString, QVariant> m_map;

    m_map[Settings::getInstance().APPLICATION_PATH] = ui->lineEdit_appPath->text().simplified();
    m_map[Settings::getInstance().CONFIG_FILES] = ui->lineEdit_configFiles->text().simplified();
    m_map[Settings::getInstance().ENV_KEY_RENDERMAN] = ui->lineEdit_envKeyRenderman->text().simplified();
    m_map[Settings::getInstance().ENV_VALUE_RENDERMAN] = ui->lineEdit_envValueRenderman->text().simplified();
    m_map[Settings::getInstance().ENV_KEY_MAYA] = ui->lineEdit_envKeyMaya->text().simplified();
    m_map[Settings::getInstance().ENV_VALUE_MAYA] = ui->lineEdit_envValueMaya->text().simplified();
    m_map[Settings::getInstance().ENV_KEY_PATH] = ui->lineEdit_envKeyPath->text().simplified();
    m_map[Settings::getInstance().ENV_VALUE_PATH] = ui->lineEdit_envValuePath->text().simplified();

    Settings::getInstance().setSettings(m_map);
}

void Preferences::readSettings()
{
    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    ui->lineEdit_appPath->setText(m_settings.value(Settings::getInstance().APPLICATION_PATH).toString());
    ui->lineEdit_configFiles->setText(m_settings.value(Settings::getInstance().CONFIG_FILES).toString());
    ui->lineEdit_envKeyRenderman->setText(m_settings.value(Settings::getInstance().ENV_KEY_RENDERMAN).toString());
    ui->lineEdit_envValueRenderman->setText(m_settings.value(Settings::getInstance().ENV_VALUE_RENDERMAN).toString());
    ui->lineEdit_envKeyMaya->setText(m_settings.value(Settings::getInstance().ENV_KEY_MAYA).toString());
    ui->lineEdit_envValueMaya->setText(m_settings.value(Settings::getInstance().ENV_VALUE_MAYA).toString());
    ui->lineEdit_envKeyPath->setText(m_settings.value(Settings::getInstance().ENV_KEY_PATH).toString());
    ui->lineEdit_envValuePath->setText(m_settings.value(Settings::getInstance().ENV_VALUE_PATH).toString());

    m_settings.endGroup();
}

void Preferences::on_btn_loadDefault_clicked()
{
    ui->lineEdit_appPath->setText(Settings::getInstance().getDefaultSettings().value(
                                      Settings::getInstance().APPLICATION_PATH).toString());

    ui->lineEdit_configFiles->setText(Settings::getInstance().getDefaultSettings().value(
                                          Settings::getInstance().CONFIG_FILES).toString());

    ui->lineEdit_envKeyRenderman->setText(Settings::getInstance().getDefaultSettings().value(
                                              Settings::getInstance().ENV_KEY_RENDERMAN).toString());

    ui->lineEdit_envValueRenderman->setText(Settings::getInstance().getDefaultSettings().value(
                                                Settings::getInstance().ENV_VALUE_RENDERMAN).toString());

    ui->lineEdit_envKeyMaya->setText(Settings::getInstance().getDefaultSettings().value(
                                         Settings::getInstance().ENV_KEY_MAYA).toString());

    ui->lineEdit_envValueMaya->setText(Settings::getInstance().getDefaultSettings().value(
                                           Settings::getInstance().ENV_VALUE_MAYA).toString());

    ui->lineEdit_envKeyPath->setText(Settings::getInstance().getDefaultSettings().value(
                                         Settings::getInstance().ENV_KEY_PATH).toString());

    ui->lineEdit_envValuePath->setText(Settings::getInstance().getDefaultSettings().value(
                                           Settings::getInstance().ENV_VALUE_PATH).toString());

    m_isStateChange = true;
}

void Preferences::on_lineEdit_appPath_editingFinished()
{
    QFileInfo file(ui->lineEdit_appPath->text());

    if(file.isFile())
    {
        if(file.isExecutable())
        {
            //qDebug() << "This is a executable file";
            m_isStateChange = (ui->lineEdit_appPath->text() ==
                               Settings::getInstance().getSettings().value(
                                   Settings::getInstance().APPLICATION_PATH).toString());
        }
        else
        {
            //qDebug() << "This is not an executable file";
            ui->lineEdit_appPath->setText(Settings::getInstance().getSettings().value(
                                              Settings::getInstance().APPLICATION_PATH).toString());
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning!", QString("The selected file: \n" + ui->lineEdit_appPath->text()
                                                       + "\n is not an acceptable file."));
        ui->lineEdit_appPath->setText(Settings::getInstance().getSettings().value(
                                          Settings::getInstance().APPLICATION_PATH).toString());
    }
}

void Preferences::on_lineEdit_configFiles_editingFinished()
{
    QDir directory(ui->lineEdit_configFiles->text());

    if(!directory.exists())
    {
        QMessageBox::warning(this, "Warning!", "The directory selected does not exist!");
        ui->lineEdit_configFiles->setText(Settings::getInstance().getSettings().value(Settings::getInstance().
                                                                                      CONFIG_FILES).toString());
    }
}

void Preferences::closeCheck()
{
    qDebug() << "antes de fechar: " << m_isStateChange;

    if(m_isStateChange)
    {
        QMessageBox::StandardButton msg;
        msg = QMessageBox::question(this, "Settings Change", "Your setting change, do you want save new setting?",
                                    QMessageBox::Yes | QMessageBox::No);

        switch (msg) {
        case QMessageBox::Yes:
            saveSettings();
            break;
        default:
            break;
        }
    }

    emit preferencesUpdate();
    m_isStateChange = false;
    close();
}

void Preferences::on_lineEdit_appPath_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().APPLICATION_PATH).toString());
}

void Preferences::on_lineEdit_configFiles_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().CONFIG_FILES).toString());
}

void Preferences::on_lineEdit_envKeyRenderman_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_KEY_RENDERMAN).toString());
}

void Preferences::on_lineEdit_envValueRenderman_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_VALUE_RENDERMAN).toString());
}

void Preferences::on_lineEdit_envKeyMaya_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_KEY_MAYA).toString());
}

void Preferences::on_lineEdit_envValueMaya_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_VALUE_MAYA).toString());
}

void Preferences::on_lineEdit_envKeyPath_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_KEY_PATH).toString());
}

void Preferences::on_lineEdit_envValuePath_textChanged(const QString &arg1)
{
    m_isStateChange = (arg1 == Settings::getInstance().getSettings().value(
                           Settings::getInstance().ENV_VALUE_PATH).toString());
}
