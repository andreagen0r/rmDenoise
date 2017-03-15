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

//bool Utils::checkDir(const QString &value)
//{
//    // REVISAR TODA A FUNCAO PARA REMOVER OS BUGS

//    bool result;

//    QDir outDir(value);
//    if((!outDir.exists() && outDir.path() != "") || outDir.path() == ".") // If path is not valid
//    {
//        QMessageBox::StandardButton answer;
//        answer = QMessageBox::question(this, "Directory not found!", "Directory not found: \n" + ui->lineEdit_outdir->text() + "\n\nDo you want create a new directory? \n" + outDir.path(), QMessageBox::Yes | QMessageBox::No);

//        switch (answer) {
//        case QMessageBox::Yes:
//        {
//             QStringList listPath = outDir.path().split(QDir::separator());

//            QString newDirName = listPath.last(); // Get the name of new directory that should be created
//            listPath.removeLast();

//            QString basePath = listPath.join("/");

//            QDir myDir(basePath);

//            if(myDir.path() == ".")
//            {
//                //qDebug() << "This path is invalid";
//                QMessageBox::information(this, "Invalid Directory", "This path is invalid!\n\"" + myDir.path() + "\"");
//                ui->lineEdit_outdir->setText("");
//                result = false;
//            }
//            else if(!myDir.exists())
//            {
//                //qDebug() << "The path chosen to create new folder is invalid";
//                QMessageBox::information(this, "Invalid Directory", "The path is invalid!\n\"" + myDir.path() + "\"");
//                ui->lineEdit_outdir->setText("");
//                result = false;
//            }
//            else
//            {
//                qDebug() << "Esse caminho é valido, vamos criar o novo diretorio: " << outDir;
//                myDir.mkdir(newDirName);
//                setFlag_outDir(outDir);
//                result = true;
//            }
//        }
//            break;
//        default:
//            ui->lineEdit_outdir->setText("");
//            result = false;
//            break;
//        }
//    }
//    else
//    {
//        ui->lineEdit_outdir->setText(outDir.path()); //If path is valid
//        result = true;
//    }

//    return result;
//}
