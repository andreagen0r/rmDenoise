#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //set app icon
   app.setWindowIcon(QIcon(":/icons/app.ico"));

    // Load style sheet
//    app.setStyle("windows");

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
