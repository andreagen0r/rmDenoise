#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>

#define APPLICATION_PATH "ApplicationPath"
#define CONFIG_FILES "ConfigFiles"
#define ENV_KEY_RENDERMAN "EnvKeyRenderman"
#define ENV_VALUE_RENDERMAN "EnvValueRenderman"
#define ENV_KEY_MAYA "EnvKeyMaya"
#define ENV_VALUE_MAYA "EnvValueMaya"
#define ENV_KEY_PATH "EnvKeyPath"
#define ENV_VALUE_PATH "EnvValuePath"

class Settings
{    
public:
    static Settings &getInstance();

    void setSettings(const QMap<QString, QVariant> &in_value);

    QMap<QString, QVariant> getSettings() const;

    QMap<QString, QVariant> getDefaultSettings() const;

private:
    Settings(){}
    Settings(Settings const&) = delete;
    void operator=(Settings const&) = delete;
};

#endif // SETTINGS_H
