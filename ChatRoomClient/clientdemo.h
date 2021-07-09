#ifndef CLIENTDEMO_H
#define CLIENTDEMO_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include "textmessage.h"
#include "txtmsgassembler.h"
#include "txtmsghandler.h"

class ClientDemo : public QObject
{
    Q_OBJECT
private:
    QTcpSocket m_client;
    TxtMsgAssembler m_assembler;
    TxtMsgHandler* m_handler;
public:

    ClientDemo(QObject* parent = nullptr);
    bool connectTo(QString ip, int port);
    qint64 send(TextMessage& message);
    qint64 available();
    void setHandler(TxtMsgHandler* handler);
    void close();

private slots:
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);

};

#endif // CLIENTDEMO_H
