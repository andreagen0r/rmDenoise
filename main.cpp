#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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
