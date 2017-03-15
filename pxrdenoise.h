#ifndef PXRDENOISE_H
#define PXRDENOISE_H

#include <iostream>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDir>
#include <QThread>

#include "settings.h"

class PXRDenoise : public QThread
{
    Q_OBJECT

public:
    explicit PXRDenoise(QObject *parent = 0);
    ~PXRDenoise();

    void run();

    QStringList getFlagLine() const;
    void setFlagLine(const QStringList &value);

private:
    QStringList flagLine;

signals:
    void renderOutputMessage(QString);
    void renderStatus(bool);
    void isRenderFinished();

public slots:
    void renderDenoise();

};

#endif // PXRDENOISE_H
