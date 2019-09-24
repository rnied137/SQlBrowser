#include "mainwindownew.h"
#include <QApplication>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindowNew w;
    MainWindowNew w;
    w.show();

    return a.exec();
}
