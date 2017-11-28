#include "preferencesUI.h"
#include "ui_preferencesUI.h"
#include "settings.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QCompleter>
#include <QDirModel>

#include <QDebug>

Preferences::Preferences(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::Preferences),
      m_isStateChange(false),
      m_completer(new QCompleter(this))
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);

    loadSettings();

    connect(ui->btn_close, &QPushButton::released, this, &Preferences::closeCheck);
    connect(this, &Preferences::rejected, this, &Preferences::closeCheck);

    m_completer->setModel(new QDirModel(m_completer.get()));
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->lineEdit_appPath->setCompleter(m_completer.get());
    ui->lineEdit_configFiles->setCompleter(m_completer.get());
    ui->lineEdit_envValueMaya->setCompleter(m_completer.get());
    ui->lineEdit_envValueRenderman->setCompleter(m_completer.get());

#ifdef WIN32
    ui->groupBox->setVisible(false);
    this->adjustSize();
#endif

}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_toolButton_appPath_clicked()
{
    QFileInfo m_file;

#ifdef __APPLE__
    m_file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::rootPath() +
                                          "/Applications/Pixar/", tr("Unix executable (denoise)"));
#else
    m_file = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                              tr("Executable file (denoise denoise.exe)"));
#endif

    if(m_file.isExecutable())
    {
        ui->lineEdit_appPath->setText(m_file.absoluteFilePath());
    }

    if(m_file.absoluteFilePath() != Settings::getInstance().getSettings().value(Settings::APPLICATION_PATH))
    {
        m_isStateChange = true;
    }
}

void Preferences::on_toolButton_configFiles_clicked()
{
    QDir m_dir;

#ifdef __APPLE__
    m_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::rootPath() + "/Applications/Pixar",
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
    m_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath(),
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif

    if(m_dir.exists())
    {
        ui->lineEdit_configFiles->setText(m_dir.absolutePath());
        m_isStateChange = true;
    }
}

void Preferences::on_lineEdit_appPath_editingFinished()
{
    QFileInfo m_file(ui->lineEdit_appPath->text());

    if( ! m_isStateChange)
    {
        m_isStateChange = (m_file.absoluteFilePath() !=
                Settings::getInstance().getSettings().value(Settings::APPLICATION_PATH));

    }

    if(m_file.isFile())
    {
        if(m_file.isExecutable())
        {
            m_isStateChange = (ui->lineEdit_appPath->text() !=
                               Settings::getInstance().getSettings().value(Settings::APPLICATION_PATH));
        }
        else
        {
            ui->lineEdit_appPath->setText(Settings::getInstance().getSettings().value(Settings::APPLICATION_PATH));
            m_isStateChange = false;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle(tr("Warning!"));
        msgBox.setText(tr("Invalid file                                                "));
        msgBox.setInformativeText(tr("The selected file: <b>%1</b> is not a valid file.").arg
                                  (ui->lineEdit_appPath->text()));
        msgBox.exec();

        ui->lineEdit_appPath->setText(Settings::getInstance().getSettings().value(Settings::APPLICATION_PATH));
        m_isStateChange = false;
    }
}

void Preferences::on_lineEdit_configFiles_editingFinished()
{
    QDir m_dir(ui->lineEdit_configFiles->text());

    if( ! m_isStateChange)
    {
        m_isStateChange = (m_dir.absolutePath() != Settings::getInstance().getSettings().value(Settings::CONFIG_FILES));

    }

    if( ! m_dir.exists())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle(tr("Warning!"));
        msgBox.setText(tr("The directory has been modified."));
        msgBox.setInformativeText(tr("The directory <b>%1</b> does not exist!").arg(m_dir.dirName()));
        msgBox.exec();

        ui->lineEdit_configFiles->setText(Settings::getInstance().getSettings().value(Settings::CONFIG_FILES));
    }
}

void Preferences::on_lineEdit_envKeyRenderman_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envKeyRenderman->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_KEY_RENDERMAN));
    }
}

void Preferences::on_lineEdit_envValueRenderman_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envValueRenderman->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_VALUE_RENDERMAN));
    }
}

void Preferences::on_lineEdit_envKeyMaya_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envKeyMaya->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_KEY_MAYA));
    }
}

void Preferences::on_lineEdit_envValueMaya_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envValueMaya->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_VALUE_MAYA));
    }
}

void Preferences::on_lineEdit_envKeyPath_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envKeyPath->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_KEY_PATH));
    }
}

void Preferences::on_lineEdit_envValuePath_editingFinished()
{
    if( ! m_isStateChange)
    {
        m_isStateChange = (ui->lineEdit_envValuePath->text() !=
                Settings::getInstance().getSettings().value(Settings::ENV_VALUE_PATH));
    }
}

void Preferences::on_btn_loadDefault_clicked()
{
    QHash<QString, QString> m_hash(Settings::getInstance().getDefaultSettings());

    ui->lineEdit_appPath->setText(m_hash.value(Settings::APPLICATION_PATH));
    ui->lineEdit_configFiles->setText(m_hash.value(Settings::CONFIG_FILES));
    ui->lineEdit_envKeyRenderman->setText(m_hash.value(Settings::ENV_KEY_RENDERMAN));
    ui->lineEdit_envValueRenderman->setText(m_hash.value(Settings::ENV_VALUE_RENDERMAN));
    ui->lineEdit_envKeyMaya->setText(m_hash.value(Settings::ENV_KEY_MAYA));
    ui->lineEdit_envValueMaya->setText(m_hash.value(Settings::ENV_VALUE_MAYA));
    ui->lineEdit_envKeyPath->setText(m_hash.value(Settings::ENV_KEY_PATH));
    ui->lineEdit_envValuePath->setText(m_hash.value(Settings::ENV_VALUE_PATH));

    m_isStateChange = true;
}

void Preferences::on_btn_save_clicked()
{
    saveSettings();
}

void Preferences::closeCheck()
{
    if(m_isStateChange)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle(tr("Settings Change"));
        msgBox.setText(tr("The settings was changed."));
        msgBox.setInformativeText(tr("Would you like to save the new settings?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int buttons = msgBox.exec();

        switch (buttons)
        {
        case QMessageBox::Yes:
            saveSettings();
            emit preferencesUpdated();
            break;
        default:
            break;
        }
    }

    m_isStateChange = false;
    close();
}

void Preferences::saveSettings()
{
    QHash<QString, QString> m_hash;

    m_hash[Settings::APPLICATION_PATH] = ui->lineEdit_appPath->text().simplified();
    m_hash[Settings::CONFIG_FILES] = ui->lineEdit_configFiles->text().simplified();
    m_hash[Settings::ENV_KEY_RENDERMAN] = ui->lineEdit_envKeyRenderman->text().simplified();
    m_hash[Settings::ENV_VALUE_RENDERMAN] = ui->lineEdit_envValueRenderman->text().simplified();
    m_hash[Settings::ENV_KEY_MAYA] = ui->lineEdit_envKeyMaya->text().simplified();
    m_hash[Settings::ENV_VALUE_MAYA] = ui->lineEdit_envValueMaya->text().simplified();
    m_hash[Settings::ENV_KEY_PATH] = ui->lineEdit_envKeyPath->text().simplified();
    m_hash[Settings::ENV_VALUE_PATH] = ui->lineEdit_envValuePath->text().simplified();

    Settings::getInstance().setSettings(m_hash);

    m_isStateChange = false;
}

void Preferences::loadSettings()
{
    QHash<QString, QString> m_hash(Settings::getInstance().getSettings());

    ui->lineEdit_appPath->setText(m_hash.value(Settings::APPLICATION_PATH));
    ui->lineEdit_configFiles->setText(m_hash.value(Settings::CONFIG_FILES));
    ui->lineEdit_envKeyRenderman->setText(m_hash.value(Settings::ENV_KEY_RENDERMAN));
    ui->lineEdit_envValueRenderman->setText(m_hash.value(Settings::ENV_VALUE_RENDERMAN));
    ui->lineEdit_envKeyMaya->setText(m_hash.value(Settings::ENV_KEY_MAYA));
    ui->lineEdit_envValueMaya->setText(m_hash.value(Settings::ENV_VALUE_MAYA));
    ui->lineEdit_envKeyPath->setText(m_hash.value(Settings::ENV_KEY_PATH));
    ui->lineEdit_envValuePath->setText(m_hash.value(Settings::ENV_VALUE_PATH));
}
