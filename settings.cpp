#include "settings.h"

Settings *Settings::myInstance = nullptr;

Settings *Settings::getInstance()
{
    if(myInstance == nullptr)
    {
        myInstance = new Settings();
    }
    return myInstance;
}

void Settings::setSettings(const QString appPath)
{
    QSettings settings("NankinCGI", "Denoise_for_Renderman");
    settings.beginGroup("Preferences");
    settings.setValue("ApplicationPath", appPath);
    settings.endGroup();

    setAppPath(appPath);
}

void Settings::setSettings(QString appPath, QString configFiles, QString keyRM, QString valRM,
                            QString keyMaya, QString valMaya, QString keyPath, QString valPath)
{
    QSettings settings("NankinCGI", "Denoise_for_Renderman");
    settings.beginGroup("Preferences");

    settings.setValue("ApplicationPath", appPath);
    settings.setValue("ConfigFiles", configFiles);
    settings.setValue("EnvKeyRenderman", keyRM);
    settings.setValue("EnvValueRenderman",valRM);
    settings.setValue("EnvKeyMaya",keyMaya);
    settings.setValue("EnvValueMaya",valMaya);
    settings.setValue("EnvKeyPath",keyPath);
    settings.setValue("EnvValuePath",valPath);

    settings.endGroup();

    setAppPath(appPath);
    setConfigFilesPath(configFiles);
    setEnvKeyRenderman(keyRM);
    setEnvValueRenderman(valRM);
    setEnvKeyMaya(keyMaya);
    setEnvValueMaya(valMaya);
    setEnvKeyPath(keyPath);
    setEnvValuePath(valPath);
}

QStringList Settings::getSettings()
{
    QSettings settings("NankinCGI", "Denoise_for_Renderman");
    settings.beginGroup("Preferences");

    QVariant appPath = settings.value("ApplicationPath");
    QVariant cFiles = settings.value("ConfigFiles");
    QVariant keyRM = settings.value("EnvKeyRenderman");
    QVariant vRM = settings.value("EnvValueRenderman");
    QVariant keyMaya = settings.value("EnvKeyMaya");
    QVariant vMaya = settings.value("EnvValueMaya");
    QVariant keyPath = settings.value("EnvKeyPath");
    QVariant vPath = settings.value("EnvValuePath");
    settings.endGroup();

    // Seta as variaveis
    setAppPath(appPath);
    setConfigFilesPath(cFiles);
    setEnvKeyRenderman(keyRM);
    setEnvValueRenderman(vRM);
    setEnvKeyMaya(keyMaya);
    setEnvValueMaya(vMaya);
    setEnvKeyPath(keyPath);
    setEnvValuePath(vPath);

    QStringList myList;

    myList.append(getApplicationPath().toString());
    myList.append(getConfigFilesPath().toString());
    myList.append(getEnvKeyRenderman().toString());
    myList.append(getEnvValueRenderman().toString());
    myList.append(getEnvKeyMaya().toString());
    myList.append(getEnvValueMaya().toString());
    myList.append(getEnvKeyPath().toString());
    myList.append(getEnvValuePath().toString());

    return myList;
}

QStringList Settings::getDefaultSettings()
{
    QStringList myList;

    myList.append("/Applications/Pixar/RenderManProServer-21.3/bin/denoise");
    myList.append("/Applications/Pixar/RenderManProServer-21.3/lib/denoise");
    myList.append("RMANTREE");
    myList.append("/Applications/Pixar/RenderManProServer-21.3");
    myList.append("RMSTREE");
    myList.append("/Applications/Pixar/RenderManForMaya-21.3-maya2017");
    myList.append("PATH");
    myList.append("${RMANTREE}/bin:${PATH}");

    return myList;
}

QVariant Settings::getApplicationPath() const
{
    return applicationPath;
}

void Settings::setAppPath(const QVariant &value)
{
    applicationPath = value;
}

QVariant Settings::getConfigFilesPath() const
{
    return configFilesPath;
}

void Settings::setConfigFilesPath(const QVariant &value)
{
    configFilesPath = value;
}

QVariant Settings::getEnvKeyRenderman() const
{
    return envKeyRenderman;
}

void Settings::setEnvKeyRenderman(const QVariant &value)
{
    envKeyRenderman = value;
}

QVariant Settings::getEnvValueRenderman() const
{
    return envValueRenderman;
}

void Settings::setEnvValueRenderman(const QVariant &value)
{
    envValueRenderman = value;
}

QVariant Settings::getEnvKeyMaya() const
{
    return envKeyMaya;
}

void Settings::setEnvKeyMaya(const QVariant &value)
{
    envKeyMaya = value;
}

QVariant Settings::getEnvValueMaya() const
{
    return envValueMaya;
}

void Settings::setEnvValueMaya(const QVariant &value)
{
    envValueMaya = value;
}

QVariant Settings::getEnvKeyPath() const
{
    return envKeyPath;
}

void Settings::setEnvKeyPath(const QVariant &value)
{
    envKeyPath = value;
}

QVariant Settings::getEnvValuePath() const
{
    return envValuePath;
}

void Settings::setEnvValuePath(const QVariant &value)
{
    envValuePath = value;
}
