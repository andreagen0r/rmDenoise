#include "settings.h"

#include <QSettings>
#include <QDir>
#include <QDebug>

const QString Settings::APPLICATION_PATH = QStringLiteral("APPLICATION_PATH");
const QString Settings::CONFIG_FILES = QStringLiteral("CONFIG_FILES");
const QString Settings::ENV_KEY_RENDERMAN = QStringLiteral("ENV_KEY_RENDERMAN");
const QString Settings::ENV_VALUE_RENDERMAN = QStringLiteral("ENV_VALUE_RENDERMAN");
const QString Settings::ENV_KEY_MAYA = QStringLiteral("ENV_KEY_MAYA");
const QString Settings::ENV_VALUE_MAYA = QStringLiteral("ENV_VALUE_MAYA");
const QString Settings::ENV_KEY_PATH = QStringLiteral("ENV_KEY_PATH");
const QString Settings::ENV_VALUE_PATH = QStringLiteral("ENV_VALUE_PATH");
const QString Settings::FIRST_TIME = QStringLiteral("FIRST_TIME");

Settings &Settings::getInstance()
{
    // Singleton
    static Settings m_instance;
    return m_instance;
}

void Settings::setSettings(const std::map<QString, QString> &in_settings)
{
    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    for(auto it : in_settings)
    {
        m_settings.setValue(it.first, it.second);
    }

    m_settings.endGroup();
}

std::map<QString, QString> Settings::getSettings() const
{
    std::map<QString, QString> m_hash;

    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    for(QString it : m_settings.allKeys())
    {
        m_hash[it] = m_settings.value(it).toString();
    }

    m_settings.endGroup();

    return m_hash;
}

std::map<QString, QString> Settings::getDefaultSettings() const
{
    std::map<QString, QString> m_default;

    const QString m_prmanProServer = QString("%1%2").arg("Pixar/", APP_PRMAN_PROSERVER);
    const QString m_rms = QString("%1%2").arg("Pixar/", APP_PRMAN_FOR_MAYA);
    const QString m_defaultDenoise = QString("%1%2").arg(m_prmanProServer, "/bin/denoise");
    const QString m_defaultConfigFiles = QString("%1%2").arg(m_prmanProServer, "/lib/denoise");

#ifdef __APPLE__
    // Dynamic
    m_default[APPLICATION_PATH] = QDir::rootPath() + "Applications/" + m_defaultDenoise;
    m_default[CONFIG_FILES] = QDir::rootPath() + "Applications/" + m_defaultConfigFiles;
    m_default[ENV_VALUE_RENDERMAN] = QDir::rootPath() + "Applications/" + m_prmanProServer;
    m_default[ENV_VALUE_MAYA] = QDir::rootPath() + "Applications/" + m_rms;
    // Literal
    m_default[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_default[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_default[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_default[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");


#elif WIN32
    // Dynamic
    m_default[APPLICATION_PATH] = QDir::rootPath() + "Program Files" + m_defaultDenoise + ".exe";
    m_default[CONFIG_FILES] = QDir::rootPath() + "Program Files" + m_defaultConfigFiles;

#elif __linux__
    // Dynamic
    m_default[APPLICATION_PATH] = QDir::rootPath() + "Applications/" + m_defaultDenoise;
    m_default[CONFIG_FILES] = QDir::rootPath() + "Applications/" + m_defaultConfigFiles;
    m_default[ENV_VALUE_RENDERMAN] = QDir::rootPath() + "Applications/" + m_prmanProServer;
    m_default[ENV_VALUE_MAYA] = QDir::rootPath() + "Applications/" + m_rms;
    // Literal
    m_default[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_default[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_default[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_default[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");

#endif

    return m_default;
}
