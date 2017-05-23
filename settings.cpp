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

void Settings::setSettings(const QString &appPath, const QString &configFiles, const QString &keyRM, const QString &valRM,
                           const  QString &keyMaya, const QString &valMaya, const QString &keyPath, const QString &valPath)
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
    QStringList myList;

    QSettings settings("NankinCGI", "Denoise_for_Renderman");
    settings.beginGroup("Preferences");

    setAppPath(settings.value("ApplicationPath"));
    setConfigFilesPath(settings.value("ConfigFiles"));
    setEnvKeyRenderman(settings.value("EnvKeyRenderman"));
    setEnvValueRenderman(settings.value("EnvValueRenderman"));
    setEnvKeyMaya(settings.value("EnvKeyMaya"));
    setEnvValueMaya(settings.value("EnvValueMaya"));
    setEnvKeyPath(settings.value("EnvKeyPath"));
    setEnvValuePath(settings.value("EnvValuePath"));

    settings.endGroup();

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
    QSysInfo getOS;
    QStringList myList;

    if(getOS.productType() == "macos")
    {
        myList.append("/Applications/Pixar/RenderManProServer-21.3/bin/denoise");
        myList.append("/Applications/Pixar/RenderManProServer-21.3/lib/denoise");
        myList.append("RMANTREE");
        myList.append("/Applications/Pixar/RenderManProServer-21.3");
        myList.append("RMSTREE");
        myList.append("/Applications/Pixar/RenderManForMaya-21.3-maya2017");
        myList.append("PATH");
        myList.append("${RMANTREE}/bin:${PATH}");
    }
    else if(getOS.productType() == "windows")
    {
        myList.append("C:/Program Files/Pixar/RenderManProServer-21.3/bin/denoise.exe");
        myList.append("C:/Program Files/Pixar/RenderManProServer-21.3/lib/denoise");
        myList.append("RMANTREE");
        myList.append("C:/Program Files/Pixar/RenderManProServer-21.3");
        myList.append("RMSTREE");
        myList.append("C:/Program Files/Pixar/RenderManForMaya-21.3-maya2017");
        myList.append("PATH");
        myList.append("${RMANTREE}/bin:${PATH}");
    }
    else // Linux
    {
        myList.append("/Applications/Pixar/RenderManProServer-21.3/bin/denoise");
        myList.append("/Applications/Pixar/RenderManProServer-21.3/lib/denoise");
        myList.append("RMANTREE");
        myList.append("/Applications/Pixar/RenderManProServer-21.3");
        myList.append("RMSTREE");
        myList.append("/Applications/Pixar/RenderManForMaya-21.3-maya2017");
        myList.append("PATH");
        myList.append("${RMANTREE}/bin:${PATH}");
    }

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
