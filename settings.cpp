#include "settings.h"

Settings &Settings::getInstance()
{
    static Settings m_instance;
    return m_instance;
}

void Settings::setSettings(const QMap<QString, QVariant> &in_value)
{
    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    m_settings.setValue(APPLICATION_PATH, in_value.value("ApplicationPath"));
    m_settings.setValue("ConfigFiles", in_value.value("ConfigFiles"));
    m_settings.setValue("EnvKeyRenderman", in_value.value("EnvKeyRenderman"));
    m_settings.setValue("EnvValueRenderman", in_value.value("EnvValueRenderman"));
    m_settings.setValue("EnvKeyMaya", in_value.value("EnvKeyMaya"));
    m_settings.setValue("EnvValueMaya", in_value.value("EnvValueMaya"));
    m_settings.setValue("EnvKeyPath", in_value.value("EnvKeyPath"));
    m_settings.setValue("EnvValuePath", in_value.value("EnvValuePath"));

    m_settings.endGroup();
}

QMap<QString, QVariant> Settings::getSettings() const
{
    QMap<QString, QVariant> myList;

    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    myList["ApplicationPath"] = m_settings.value("ApplicationPath").toString();
    myList["ConfigFiles"] = m_settings.value("ConfigFiles").toString();
    myList["EnvKeyRenderman"] = m_settings.value("EnvKeyRenderman").toString();
    myList["EnvValueRenderman"] = m_settings.value("EnvValueRenderman").toString();
    myList["EnvKeyMaya"] = m_settings.value("EnvKeyMaya").toString();
    myList["EnvValueMaya"] = m_settings.value("EnvValueMaya").toString();
    myList["EnvKeyPath"] = m_settings.value("EnvKeyPath").toString();
    myList["EnvValuePath"] = m_settings.value("EnvValuePath").toString();

    m_settings.endGroup();

    return myList;
}

QMap<QString, QVariant> Settings::getDefaultSettings() const
{
    QMap<QString, QVariant> myList;

#ifdef __APPLE__
    myList["ApplicationPath"] = "/Applications/Pixar/RenderManProServer-21.5/bin/denoise";
    myList["ConfigFiles"] = "/Applications/Pixar/RenderManProServer-21.5/lib/denoise";
    myList["EnvKeyRenderman"] = "RMANTREE";
    myList["EnvValueRenderman"] = "/Applications/Pixar/RenderManProServer-21.5";
    myList["EnvKeyMaya"] = "RMSTREE";
    myList["EnvValueMaya"] = "/Applications/Pixar/RenderManForMaya-21.5-maya2017";
    myList["EnvKeyPath"] = "PATH";
    myList["EnvValuePath"] = "${RMANTREE}/bin:${PATH}";
#endif

#ifdef WIN32
    myList["ApplicationPath"] = "C:/Program Files/Pixar/RenderManProServer-21.5/bin/denoise.exe";
    myList["ConfigFiles"] = "C:/Program Files/Pixar/RenderManProServer-21.5/lib/denoise";
    myList["EnvKeyRenderman"] = "RMANTREE";
    myList["EnvValueRenderman"] = "C:/Program Files/Pixar/RenderManProServer-21.5";
    myList["EnvKeyMaya"] = "RMSTREE";
    myList["EnvValueMaya"] = "C:/Program Files/Pixar/RenderManForMaya-21.5-maya2017";
    myList["EnvKeyPath"] = "PATH";
    myList["EnvValuePath"] = "${RMANTREE}/bin:${PATH}";
#endif

#ifdef LINUX
    myList["ApplicationPath"] = "/Applications/Pixar/RenderManProServer-21.5/bin/denoise";
    myList["ConfigFiles"] = "/Applications/Pixar/RenderManProServer-21.5/lib/denoise";
    myList["EnvKeyRenderman"] = "RMANTREE";
    myList["EnvValueRenderman"] = "/Applications/Pixar/RenderManProServer-21.5";
    myList["EnvKeyMaya"] = "RMSTREE";
    myList["EnvValueMaya"] = "/Applications/Pixar/RenderManForMaya-21.5-maya2017";
    myList["EnvKeyPath"] = "PATH";
    myList["EnvValuePath"] = "${RMANTREE}/bin:${PATH}";
#endif

    return myList;
}
