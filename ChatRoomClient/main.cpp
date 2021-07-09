#include "mainwin.h"
#include <QApplication>
#include "databasedemo.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog ld;

    if ( ld.exec() == QDialog::Accepted ) {

        MainWin* w = new MainWin;
        w->setUsername(ld.getUser());
        w->show();

    }

    return a.exec();
}
