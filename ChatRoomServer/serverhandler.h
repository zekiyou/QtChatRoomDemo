#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include "txtmsghandler.h"
#include "textmessage.h"
#include <QList>
#include <QMap>
#include <QTcpSocket>
#include <QTcpServer>

class ServerHandler : public TxtMsgHandler
{

    typedef void(ServerHandler::*MSGHandler)(QTcpSocket&, TextMessage&);

    struct Node {
        QString id;
        QString pwd;
        QTcpSocket* socket;
    public:
        Node() : id(""),pwd(""),socket(nullptr) {

        }
    };

    QList<Node*> m_nodeList;

    QString getOnlineUserId();
    void sendToAllOnlineUser(TextMessage& tm);

public:
    ServerHandler();
    void handle(QTcpSocket& obj, TextMessage& message);

};

#endif // SERVERHANDLER_H
