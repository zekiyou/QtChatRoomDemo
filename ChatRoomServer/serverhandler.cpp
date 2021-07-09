#include "serverhandler.h"

ServerHandler::ServerHandler()
{

}

void ServerHandler::handle(QTcpSocket &obj, TextMessage &message)
{

    qDebug() << &obj;
    qDebug() << message.type();
    qDebug() << message.data();


    if ( message.type() == "CONN") {

    }

    if ( message.type() == "DSCN") {

    }

}
