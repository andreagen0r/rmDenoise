#ifndef PXRDENOISE_H
#define PXRDENOISE_H

#include <QThread>

class PXRDenoise : public QThread
{
    Q_OBJECT

public:
    explicit PXRDenoise(QObject *parent = 0);

    QStringList getCommandLine() const;
    void setCommandLine(const QStringList &in_value);

signals:
    void renderOutputMessage(QString);
    void renderStatus(bool);
    void isRenderFinished();

private:
    void renderDenoise();

    QStringList m_commandLine;

protected:
    void run() override;
};

#endif // PXRDENOISE_H
