#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set icon to dock
   app.setWindowIcon(QIcon(":/icons/app.ico"));


    //app.setStyle("windows");

//    QFile file(":/stylesheet.qss");
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        app.setStyleSheet(file.readAll());
//        file.close();
//    }

    MainWindow w;
    w.show();

    return app.exec();
}
