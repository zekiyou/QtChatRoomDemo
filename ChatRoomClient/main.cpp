#include "mainwin.h"
#include <QApplication>
#include "databasedemo.h"
extern DataBaseDemo db;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBaseDemo db;
    MainWin w;
    w.show();

    return a.exec();
}
