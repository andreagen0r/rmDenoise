#ifndef PXRDENOISE_H
#define PXRDENOISE_H

#include <QStringList>
#include <QProcess>
#include <QThread>
#include <QMutex>

#include "settings.h"

class PXRDenoise : public QThread
{
    Q_OBJECT

public:
    explicit PXRDenoise(QObject *parent = 0);

    void run();

    QStringList getCommandLine() const;
    void setCommandLine(const QStringList &in_value);

signals:
    void renderOutputMessage(QString);
    void renderStatus(bool);
    void isRenderFinished();

private:
    void renderDenoise();

    QStringList m_commandLine;
};

#endif // PXRDENOISE_H
