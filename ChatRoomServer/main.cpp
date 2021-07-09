#include <QCoreApplication>
#include "serverdemo.h"
#include "serverhandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerDemo server;
    ServerHandler handler;
    server.setHandler(&handler);
    server.start(8080);

    return a.exec();
}
