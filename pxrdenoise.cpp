#include "pxrdenoise.h"
#include "settings.h"

#include <QSettings>
#include <QMutex>
#include <QProcess>
#include <QStringList>

PXRDenoise::PXRDenoise(QObject *parent) : QThread(parent)
{

}

void PXRDenoise::renderDenoise()
{
    QProcess proc;
    emit renderStatus(true);

#ifdef __APPLE__
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_RENDERMAN),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_RENDERMAN));

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_MAYA),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_MAYA));

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_PATH),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_PATH));

    proc.setProcessEnvironment(env);
#endif

    proc.start(Settings::getInstance().getSettings().value(Settings::getInstance().APPLICATION_PATH), getCommandLine());

    proc.waitForFinished(-1);

    //Reads standard output
    emit renderOutputMessage(proc.readAllStandardOutput());
    emit renderStatus(false);
    emit isRenderFinished();
}

void PXRDenoise::run()
{
    QMutex mtx;
    mtx.lock();
    renderDenoise();
    mtx.unlock();
}

QStringList PXRDenoise::getCommandLine() const
{
    return m_commandLine;
}

void PXRDenoise::setCommandLine(const QStringList &in_value)
{
    m_commandLine = in_value;
}
