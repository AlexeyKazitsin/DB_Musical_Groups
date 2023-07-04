#include "mainwindow.h"
#include "login.h"
#include "navigation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login log;
    if (!log.exec())
        return 0;

    //Navigation n;
    //n.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
