#include "settings.h"

#include <QSettings>

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

    m_settings.setValue(APPLICATION_PATH, in_settings.value(APPLICATION_PATH));
    m_settings.setValue(CONFIG_FILES, in_settings.value(CONFIG_FILES));
    m_settings.setValue(ENV_KEY_RENDERMAN, in_settings.value(ENV_KEY_RENDERMAN));
    m_settings.setValue(ENV_VALUE_RENDERMAN, in_settings.value(ENV_VALUE_RENDERMAN));
    m_settings.setValue(ENV_KEY_MAYA, in_settings.value(ENV_KEY_MAYA));
    m_settings.setValue(ENV_VALUE_MAYA, in_settings.value(ENV_VALUE_MAYA));
    m_settings.setValue(ENV_KEY_PATH, in_settings.value(ENV_KEY_PATH));
    m_settings.setValue(ENV_VALUE_PATH, in_settings.value(ENV_VALUE_PATH));

    m_settings.endGroup();
}

QHash<QString, QString> Settings::getSettings() const
{
    QHash<QString, QString> m_hash;

    QSettings m_settings(APP_COMPANY, APP_PRODUCT);
    m_settings.beginGroup(APP_PRODUCT);

    m_hash[APPLICATION_PATH] = m_settings.value(APPLICATION_PATH).toString();
    m_hash[CONFIG_FILES] = m_settings.value(CONFIG_FILES).toString();
    m_hash[ENV_KEY_RENDERMAN] = m_settings.value(ENV_KEY_RENDERMAN).toString();
    m_hash[ENV_VALUE_RENDERMAN] = m_settings.value(ENV_VALUE_RENDERMAN).toString();
    m_hash[ENV_KEY_MAYA] = m_settings.value(ENV_KEY_MAYA).toString();
    m_hash[ENV_VALUE_MAYA] = m_settings.value(ENV_VALUE_MAYA).toString();
    m_hash[ENV_KEY_PATH] = m_settings.value(ENV_KEY_PATH).toString();
    m_hash[ENV_VALUE_PATH] = m_settings.value(ENV_VALUE_PATH).toString();

    m_settings.endGroup();

    return m_hash;
}

QHash<QString, QString> Settings::getDefaultSettings() const
{
    QHash<QString, QString> m_hash;

    const QString m_prmanRoot = QString("%1%2").arg("/Pixar/", APP_PRMAN_PROSERVER);
    const QString m_denoiseAppPath = QString("%1%2").arg(m_prmanRoot, "/bin/");
    const QString m_denoiseLibPath = QString("%1%2").arg(m_prmanRoot, "/lib/denoise");
    const QString m_prmanEnvKey = QStringLiteral("RMANTREE");
    const QString m_mayaEnvKey = QStringLiteral("RMSTREE");
    const QString m_pathEnvKey = QStringLiteral("PATH");

#ifdef __APPLE__
    m_hash[APPLICATION_PATH] = "/Applications" + m_denoiseAppPath + "denoise";
    m_hash[CONFIG_FILES] = "/Applications" + m_denoiseLibPath;
    m_hash[ENV_KEY_RENDERMAN] = m_prmanEnvKey;
    m_hash[ENV_VALUE_RENDERMAN] = "/Applications" + m_prmanRoot;
    m_hash[ENV_KEY_MAYA] = m_mayaEnvKey;
    m_hash[ENV_VALUE_MAYA] = QStringLiteral("/Applications/Pixar/RenderManForMaya-21.5-maya2017");
    m_hash[ENV_KEY_PATH] = m_pathEnvKey;
    m_hash[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");

#elif WIN32
    m_hash[APPLICATION_PATH] = "C:/Program Files" + m_denoiseAppPath + "denoise.exe";
    m_hash[CONFIG_FILES] = "C:/Program Files" + m_denoiseLibPath;

#elif __linux__
    m_hash[APPLICATION_PATH] = "/Applications" + m_denoiseAppPath + "denoise";
    m_hash[CONFIG_FILES] = "/Applications" + m_denoiseLibPath;
    m_hash[ENV_KEY_RENDERMAN] = m_prmanEnvKey;
    m_hash[ENV_VALUE_RENDERMAN] = "/Applications" + m_prmanRoot;
    m_hash[ENV_KEY_MAYA] = m_mayaEnvKey;
    m_hash[ENV_VALUE_MAYA] = QStringLiteral("/Applications/Pixar/RenderManForMaya-21.5-maya2017");
    m_hash[ENV_KEY_PATH] = m_pathEnvKey;
    m_hash[ENV_VALUE_PATH] = QStringLiteral("${RMANTREE}/bin:${PATH}");

#endif

    return m_hash;
}
