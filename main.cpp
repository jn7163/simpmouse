#include "mainwindow.h"
#include "func.h"

#include <QApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initialize();

    MainWindow w;
    w.show();
    
    //applyCurChanges(mainSet[0], 1);

    
    //return 0;
    return a.exec();
}
