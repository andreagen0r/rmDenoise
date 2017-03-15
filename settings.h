#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <QVariant>
#include <QSettings>
#include <QString>
#include <QStringList>

class Settings
{

public:
    static Settings *getInstance();

    QSettings* settings = new QSettings(":/resource/", QSettings::IniFormat);

    void setSettings(const QString appPath, const QString configFilesPath, const QString keyRM, const QString valRM,
                      const QString keyMaya, const QString valMaya, const QString keyPath, const QString valPath);
    void setSettings(const QString appPath);
    QStringList getSettings();

    QStringList getDefaultSettings();

    QVariant getApplicationPath() const;
    void setAppPath(const QVariant &value);

    QVariant getConfigFilesPath() const;
    void setConfigFilesPath(const QVariant &value);

    QVariant getEnvKeyRenderman() const;
    void setEnvKeyRenderman(const QVariant &value);

    QVariant getEnvValueRenderman() const;
    void setEnvValueRenderman(const QVariant &value);

    QVariant getEnvKeyMaya() const;
    void setEnvKeyMaya(const QVariant &value);

    QVariant getEnvValueMaya() const;
    void setEnvValueMaya(const QVariant &value);

    QVariant getEnvKeyPath() const;
    void setEnvKeyPath(const QVariant &value);

    QVariant getEnvValuePath() const;
    void setEnvValuePath(const QVariant &value);

private:
    Settings(){}
    static Settings *myInstance;

    QVariant applicationPath;
    QVariant configFilesPath;
    QVariant envKeyRenderman;
    QVariant envValueRenderman;
    QVariant envKeyMaya;
    QVariant envValueMaya;
    QVariant envKeyPath;
    QVariant envValuePath;

};

#endif // SETTINGS_H
