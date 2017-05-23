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
    QSysInfo getOS;
    QProcess proc;
    emit renderStatus(true);

    if(getOS.productType() == "macos")
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.insert(Settings::getInstance()->getEnvKeyRenderman().toString(), Settings::getInstance()->getEnvValueRenderman().toString());
        env.insert(Settings::getInstance()->getEnvKeyMaya().toString(), Settings::getInstance()->getEnvValueMaya().toString());
        env.insert(Settings::getInstance()->getEnvKeyPath().toString(), Settings::getInstance()->getEnvValuePath().toString());
        proc.setProcessEnvironment(env);
    }


    proc.start(Settings::getInstance()->getApplicationPath().toString(), getFlagLine());
    //Wait for execution is completed
    proc.waitForFinished(-1);

    //Reads standard output
    emit renderOutputMessage(proc.readAllStandardOutput());
    emit renderStatus(false);
    emit isRenderFinished();
}

QStringList PXRDenoise::getFlagLine() const
{
    return flagLine;
}

void PXRDenoise::setFlagLine(const QStringList &value)
{
    flagLine = value;
}
