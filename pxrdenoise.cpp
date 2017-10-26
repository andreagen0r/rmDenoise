#include "pxrdenoise.h"

PXRDenoise::PXRDenoise(QObject *parent) : QThread(parent)
{

}

void PXRDenoise::run()
{
    QMutex mtx;
    mtx.lock();
    renderDenoise();
    mtx.unlock();
}

void PXRDenoise::renderDenoise()
{
    QProcess proc;
    emit renderStatus(true);

#ifdef __APPLE__
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_RENDERMAN).toString(),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_RENDERMAN).toString());

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_MAYA).toString(),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_MAYA).toString());

    env.insert(Settings::getInstance().getSettings().value(Settings::getInstance().ENV_KEY_PATH).toString(),
               Settings::getInstance().getSettings().value(Settings::getInstance().ENV_VALUE_PATH).toString());

    proc.setProcessEnvironment(env);
#endif

    proc.start(Settings::getInstance().getSettings().value(
                   Settings::getInstance().APPLICATION_PATH).toString(), getCommandLine());

    proc.waitForFinished(-1);

    //Reads standard output
    emit renderOutputMessage(proc.readAllStandardOutput());
    emit renderStatus(false);
    emit isRenderFinished();
}

QStringList PXRDenoise::getCommandLine() const
{
    return m_commandLine;
}

void PXRDenoise::setCommandLine(const QStringList &in_value)
{
    m_commandLine = in_value;
}
