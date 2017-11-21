#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

class Settings        
{    
public:
    // Singleton
    static Settings &getInstance();

    void setSettings(const QHash<QString, QString> &in_settings);

    QHash<QString, QString> getSettings() const;

    QHash<QString, QString> getDefaultSettings() const;

    static const QString APPLICATION_PATH;
    static const QString CONFIG_FILES;
    static const QString ENV_KEY_RENDERMAN;
    static const QString ENV_VALUE_RENDERMAN;
    static const QString ENV_KEY_MAYA;
    static const QString ENV_VALUE_MAYA;
    static const QString ENV_KEY_PATH;
    static const QString ENV_VALUE_PATH;
    static const QString FIRST_TIME;

private:
    Settings(){}
    Settings(Settings const&) = delete;
    void operator = (Settings const&) = delete;
};

#endif // SETTINGS_H
