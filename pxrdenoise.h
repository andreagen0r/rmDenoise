#ifndef PXRDENOISE_H
#define PXRDENOISE_H

#include <iostream>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDir>
#include <QThread>
#include <QMutex>
#include <QSysInfo>
#include "settings.h"

class PXRDenoise : public QThread
{
    Q_OBJECT

public:
    explicit PXRDenoise(QObject *parent = 0);

    void run();

    QStringList getFlagLine() const;
    void setFlagLine(const QStringList &value);

private:
    void renderDenoise();

    QStringList flagLine;

signals:
    void renderOutputMessage(QString);
    void renderStatus(bool);
    void isRenderFinished();
};

#endif // PXRDENOISE_H
