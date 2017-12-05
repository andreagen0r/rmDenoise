#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>

class QString;

class Settings        
{    
    Settings(){}
    Settings(Settings const&) = delete;
    void operator = (Settings const&) = delete;

public:
    // Singleton
    static Settings &getInstance();

    void setSettings(const std::map<QString, QString> &in_settings);

    std::map<QString, QString> getSettings() const;

    std::map<QString, QString> getDefaultSettings() const;

    static const QString APPLICATION_PATH;
    static const QString CONFIG_FILES;
    static const QString ENV_KEY_RENDERMAN;
    static const QString ENV_VALUE_RENDERMAN;
    static const QString ENV_KEY_MAYA;
    static const QString ENV_VALUE_MAYA;
    static const QString ENV_KEY_PATH;
    static const QString ENV_VALUE_PATH;
    static const QString FIRST_TIME;
};

#endif // SETTINGS_H
