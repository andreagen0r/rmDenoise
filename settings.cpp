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

    m_settings.setValue(APPLICATION_PATH, in_value.value(APPLICATION_PATH));
    m_settings.setValue(CONFIG_FILES, in_value.value(CONFIG_FILES));
    m_settings.setValue(ENV_KEY_RENDERMAN, in_value.value(ENV_KEY_RENDERMAN));
    m_settings.setValue(ENV_VALUE_RENDERMAN, in_value.value(ENV_VALUE_RENDERMAN));
    m_settings.setValue(ENV_KEY_MAYA, in_value.value(ENV_KEY_MAYA));
    m_settings.setValue(ENV_VALUE_MAYA, in_value.value(ENV_VALUE_MAYA));
    m_settings.setValue(ENV_KEY_PATH, in_value.value(ENV_KEY_PATH));
    m_settings.setValue(ENV_VALUE_PATH, in_value.value(ENV_VALUE_PATH));

    m_settings.endGroup();
}

QMap<QString, QVariant> Settings::getSettings() const
{
    QMap<QString, QVariant> m_list;

    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    m_list[APPLICATION_PATH] = m_settings.value(APPLICATION_PATH).toString();
    m_list[CONFIG_FILES] = m_settings.value(CONFIG_FILES).toString();
    m_list[ENV_KEY_RENDERMAN] = m_settings.value(ENV_KEY_RENDERMAN).toString();
    m_list[ENV_VALUE_RENDERMAN] = m_settings.value(ENV_VALUE_RENDERMAN).toString();
    m_list[ENV_KEY_MAYA] = m_settings.value(ENV_KEY_MAYA).toString();
    m_list[ENV_VALUE_MAYA] = m_settings.value(ENV_VALUE_MAYA).toString();
    m_list[ENV_KEY_PATH] = m_settings.value(ENV_KEY_PATH).toString();
    m_list[ENV_VALUE_PATH] = m_settings.value(ENV_VALUE_PATH).toString();

    m_settings.endGroup();

    return m_list;
}

QMap<QString, QVariant> Settings::getDefaultSettings() const
{
    QMap<QString, QVariant> m_list;

    const QString rootPath = QDir::rootPath();
    const QString rmVersion = QStringLiteral(APP_PRMAN_PROSERVER);

    qDebug() << rootPath + rmVersion;

#ifdef __APPLE__
    m_list[APPLICATION_PATH] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5/bin/denoise");

//    m_list[APPLICATION_PATH] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5/bin/denoise");
    m_list[CONFIG_FILES] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5/lib/denoise");
    m_list[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_list[ENV_VALUE_RENDERMAN] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5");
    m_list[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_list[ENV_VALUE_MAYA] = QStringLiteral("/Applications/Pixar/RenderManForMaya-21.5-maya2017");
    m_list[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_list[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");
#endif

#ifdef WIN32
    m_list[APPLICATION_PATH] = QStringLiteral("C:/Program Files/Pixar/RenderManProServer-21.5/bin/denoise.exe");
    m_list[CONFIG_FILES] = QStringLiteral("C:/Program Files/Pixar/RenderManProServer-21.5/lib/denoise");
    m_list[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_list[ENV_VALUE_RENDERMAN] = QStringLiteral("C:/Program Files/Pixar/RenderManProServer-21.5");
    m_list[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_list[ENV_VALUE_MAYA] = QStringLiteral("C:/Program Files/Pixar/RenderManForMaya-21.5-maya2017");
    m_list[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_list[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");
#endif

#ifdef LINUX
    m_list[APPLICATION_PATH] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5/bin/denoise");
    m_list[CONFIG_FILES] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5/lib/denoise");
    m_list[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_list[ENV_VALUE_RENDERMAN] = QStringLiteral("/Applications/Pixar/RenderManProServer-21.5");
    m_list[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_list[ENV_VALUE_MAYA] = QStringLiteral("/Applications/Pixar/RenderManForMaya-21.5-maya2017");
    m_list[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_list[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");
#endif

    return m_list;
}
