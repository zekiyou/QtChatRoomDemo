#ifndef SERVERDEMO_H
#define SERVERDEMO_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerDemo : public QObject
{
    Q_OBJECT
QTcpServer m_Server;
public:
    explicit ServerDemo(QObject *parent = nullptr);
    ~ServerDemo();
    bool start(quint16 port);
    void stop();
signals:

public slots:
    void onNewConnection();

    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onByterWritten(qint64 bytes);
};

#endif // SERVERDEMO_H
