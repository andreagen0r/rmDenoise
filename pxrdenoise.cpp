#include "pxrdenoise.h"

PXRDenoise::PXRDenoise(QObject *parent) : QThread(parent)
{

}

PXRDenoise::~PXRDenoise()
{

}

void PXRDenoise::run()
{
    QMutex mtx;
    mtx.lock();
    qDebug() << "Dentro de run: " << QThread::currentThread();
    renderDenoise();
    mtx.unlock();
}

void PXRDenoise::renderDenoise()
{
    emit renderStatus(true);

    QProcess proc;

    QString commandPath = Settings::getInstance()->getApplicationPath().toString(); // set path to run process. Pixar denoise path

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert(Settings::getInstance()->getEnvKeyRenderman().toString(), Settings::getInstance()->getEnvValueRenderman().toString());
    env.insert(Settings::getInstance()->getEnvKeyMaya().toString(), Settings::getInstance()->getEnvValueMaya().toString());
    env.insert(Settings::getInstance()->getEnvKeyPath().toString(), Settings::getInstance()->getEnvValuePath().toString());
    proc.setProcessEnvironment(env);
    proc.start(commandPath,getFlagLine(),QIODevice::ReadOnly); //Starts execution of command
    proc.waitForFinished(-1); //Waits for execution to complete

    QString StdOut      =   proc.readAllStandardOutput();  //Reads standard output

    emit renderOutputMessage(StdOut);
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
