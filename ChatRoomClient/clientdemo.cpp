#include "clientdemo.h"

ClientDemo::ClientDemo()
{
    connect(&m_client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&m_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&m_client, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(&m_client, SIGNAL(bytesWritten(qint64)), this, SLOT(onByterWritten(qint64)));
}

void ClientDemo::connectTo(QString ip, quint16 port)
{
    m_client.connectToHost(ip, port);
}

qint64 ClientDemo::send(const char *data, int len)
{
    return m_client.write(data,len);
}

qint64 ClientDemo::available()
{
    return m_client.bytesAvailable();
}

void ClientDemo::close()
{
    m_client.close();
}

void ClientDemo::onConnected()
{
    qDebug() << "onConnected()" ;
    QHostAddress m_adress = m_client.localAddress();
    qDebug() << "Local_Address" << m_adress.toString();
    qDebug() << "Local_Port" << m_client.localPort();
}

void ClientDemo::onDisconnected()
{
    qDebug() << "onDisconnected()";
}

void ClientDemo::onDataReady()
{
    char buf[256] = {0};
    qDebug() << "onDataReady:" << m_client.read(buf,sizeof(buf)-1);
    qDebug() << "Data:" << buf;
}

void ClientDemo::onByterWritten(qint64 bytes)
{
    qDebug() << "onByterWirtten:" << bytes;
}

