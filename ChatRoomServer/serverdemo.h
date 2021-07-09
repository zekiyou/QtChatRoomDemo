#ifndef SERVERDEMO_H
#define SERVERDEMO_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "textmessage.h"
#include "txtmsgassembler.h"
#include "txtmsghandler.h"

class ServerDemo : public QObject
{
    Q_OBJECT

    QTcpServer m_server;
    QMap<QTcpSocket*, TxtMsgAssembler*> m_map;
    TxtMsgHandler* m_handler;
public:
    ServerDemo(QObject* parent = nullptr);
    bool start(int port);
    void stop();
    void setHandler(TxtMsgHandler* handler);
    ~ServerDemo();

protected slots:
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);
};

#endif // SERVERDEMO_H
