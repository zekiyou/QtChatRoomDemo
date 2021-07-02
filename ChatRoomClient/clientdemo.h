#ifndef CLIENTDEMO_H
#define CLIENTDEMO_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>

class ClientDemo : public QObject
{
    Q_OBJECT
private:
    QTcpSocket m_client;
public:
    ClientDemo();
    void connectTo(QString ip, quint16 port);
    qint64 send(const char* data, int len);
    qint64 available();
    void close();
private slots:
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onByterWritten(qint64 bytes);
};

#endif // CLIENTDEMO_H
