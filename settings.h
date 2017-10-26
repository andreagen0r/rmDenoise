#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QDir>
#include <QDebug>

class Settings
{    
public:
    static Settings &getInstance();

    void setSettings(const QMap<QString, QVariant> &in_value);

    QMap<QString, QVariant> getSettings() const;

    QMap<QString, QVariant> getDefaultSettings() const;

    const QString APPLICATION_PATH = QStringLiteral("ApplicationPath");
    const QString CONFIG_FILES = QStringLiteral("ConfigFiles");
    const QString ENV_KEY_RENDERMAN = QStringLiteral("EnvKeyRenderman");
    const QString ENV_VALUE_RENDERMAN = QStringLiteral("EnvValueRenderman");
    const QString ENV_KEY_MAYA = QStringLiteral("EnvKeyMaya");
    const QString ENV_VALUE_MAYA = QStringLiteral("EnvValueMaya");
    const QString ENV_KEY_PATH = QStringLiteral("EnvKeyPath");
    const QString ENV_VALUE_PATH = QStringLiteral("EnvValuePath");

private:
    Settings(){}
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;
};

#endif // SETTINGS_H
