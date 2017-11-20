#include "utils.h"


Utils::Utils(QObject *parent) : QObject(parent)
{

}

bool Utils::checkImages(const QStringList &value)
{
    bool result;

    if(value.isEmpty())
    {
        result = false;
    }
    else
    {
        QFileInfo selectedFiles;
        foreach (QString file, value)
        {
            selectedFiles = file;
            if(selectedFiles.exists() && selectedFiles.isFile())
            {
                if(selectedFiles.suffix() == "exr" || selectedFiles.suffix() == "EXR" )
                {
                    //qDebug() << "The file suffix is ok!";
                    result = true;
                }
            }
            else
            {
                //qDebug() << "The file doesn't exist";
                result = false;
                break;
            }
        }
    }

    return result;
}

QStringList Utils::notValidImages(const QStringList &value)
{
    QStringList result;

    if(!value.isEmpty())
    {
        QFileInfo selectedFiles;

        foreach (QString file, value)
        {
            selectedFiles = file;
            if(!selectedFiles.exists() && !selectedFiles.isFile())
            {
                result.append(file);
            }
        }
    }

    return result; // List of invalid images
}

QStringList Utils::validImages(const QStringList &value)
{
    QStringList result;

    if(!value.isEmpty())
    {
        QFileInfo selectedFiles;

        foreach (QString file, value)
        {
            selectedFiles = file;
            if(selectedFiles.exists() && selectedFiles.isFile())
            {
                if(selectedFiles.suffix() == "exr" || selectedFiles.suffix() == "EXR" )
                {
                    result.append(file);
                }
            }
        }
    }

    return result; // List of valid images
}

bool Utils::checkDir(const QString &value)
{
    bool result;

    if(value.isEmpty() || value.isNull())
    {
        result = false;
    }
    else
    {
        QDir outDir(value);

        if((!outDir.exists() && outDir.path() != "") || outDir.path() == QDir::separator() || outDir.path() == ".")
        {
            result = false;
        }
        else
        {
            result = true;
        }
    }

    return result;
}
