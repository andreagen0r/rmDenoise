#include "settings.h"

#include <QSettings>
#include <QDir>

const QString Settings::APPLICATION_PATH = QStringLiteral("ApplicationPath");
const QString Settings::CONFIG_FILES = QStringLiteral("ConfigFiles");
const QString Settings::ENV_KEY_RENDERMAN = QStringLiteral("EnvKeyRenderman");
const QString Settings::ENV_VALUE_RENDERMAN = QStringLiteral("EnvValueRenderman");
const QString Settings::ENV_KEY_MAYA = QStringLiteral("EnvKeyMaya");
const QString Settings::ENV_VALUE_MAYA = QStringLiteral("EnvValueMaya");
const QString Settings::ENV_KEY_PATH = QStringLiteral("EnvKeyPath");
const QString Settings::ENV_VALUE_PATH = QStringLiteral("EnvValuePath");

Settings &Settings::getInstance()
{
    // Singleton
    static Settings m_instance;
    return m_instance;
}

void Settings::setSettings(const QHash<QString, QString> &in_settings)
{
    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    for(auto m_keys : in_settings.keys())
    {
        m_settings.setValue(m_keys, in_settings.value(m_keys));
    }

    m_settings.endGroup();
}

QHash<QString, QString> Settings::getSettings() const
{
    QHash<QString, QString> m_hash;

    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    for(auto m_keys : m_settings.allKeys())
    {
        m_hash[m_keys] = m_settings.value(m_keys).toString();
    }

    m_settings.endGroup();

    return m_hash;
}

QHash<QString, QString> Settings::getDefaultSettings() const
{
    QHash<QString, QString> m_hash;

    const QString m_prmanProServer = QString("%1%2").arg("Pixar/", APP_PRMAN_PROSERVER);
    const QString m_rms = QString("%1%2").arg("Pixar/", APP_PRMAN_FOR_MAYA);
    const QString m_defaultDenoise = QString("%1%2").arg(m_prmanProServer, "/bin/denoise");
    const QString m_defaultConfigFiles = QString("%1%2").arg(m_prmanProServer, "/lib/denoise");

#ifdef __APPLE__
    // Dynamic
    m_hash[APPLICATION_PATH] = QDir::rootPath() + "Applications/" + m_defaultDenoise;
    m_hash[CONFIG_FILES] = QDir::rootPath() + "Applications/" + m_defaultConfigFiles;
    m_hash[ENV_VALUE_RENDERMAN] = QDir::rootPath() + "Applications/" + m_prmanProServer;
    m_hash[ENV_VALUE_MAYA] = QDir::rootPath() + "Applications/" + m_rms;
    // Literal
    m_hash[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_hash[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_hash[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_hash[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");


#elif WIN32
    // Dynamic
    m_hash[APPLICATION_PATH] = QDir::rootPath() + "Program Files" + m_defaultDenoise + ".exe";
    m_hash[CONFIG_FILES] = QDir::rootPath() + "Program Files" + m_defaultConfigFiles;

#elif __linux__
    // Dynamic
    m_hash[APPLICATION_PATH] = QDir::rootPath() + "Applications/" + m_defaultDenoise;
    m_hash[CONFIG_FILES] = QDir::rootPath() + "Applications/" + m_defaultConfigFiles;
    m_hash[ENV_VALUE_RENDERMAN] = QDir::rootPath() + "Applications/" + m_prmanProServer;
    m_hash[ENV_VALUE_MAYA] = QDir::rootPath() + "Applications/" + m_rms;
    // Literal
    m_hash[ENV_KEY_RENDERMAN] = QStringLiteral("RMANTREE");
    m_hash[ENV_KEY_MAYA] = QStringLiteral("RMSTREE");
    m_hash[ENV_KEY_PATH] = QStringLiteral("PATH");
    m_hash[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");

#endif

    return m_hash;
}
