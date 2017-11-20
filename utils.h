#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
//#include <QFileInfo>
#include <QDir>


class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);

    bool checkImages(const QStringList &value);
    QStringList notValidImages(const QStringList &value);
    QStringList validImages(const QStringList &value);
    bool checkDir(const QString &value);
};

#endif // UTILS_H
