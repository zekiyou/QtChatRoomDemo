#include "serverdemo.h"

ServerDemo::ServerDemo(QObject *parent) : QObject(parent)
{
    connect(&m_Server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}


ServerDemo::~ServerDemo()
{
    const QObjectList& list = m_Server.children();

    for(int i=0; i<list.length(); i++)
    {
        QTcpSocket* tcp = dynamic_cast<QTcpSocket*>(list[i]);

        if( tcp != nullptr )
        {
            tcp->close();
        }
    }
}


bool ServerDemo::start(quint16 port)
{
    bool ret = true;

    if(!m_Server.isListening()){
        ret = m_Server.listen(QHostAddress("127.0.0.1"), port);
    }

    return ret;
}

void ServerDemo::stop()
{
    if(m_Server.isListening()){
        m_Server.close();
    }
}

void ServerDemo::onNewConnection()
{
    QTcpSocket* m_client = m_Server.nextPendingConnection();
    connect(m_client, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_client, SIGNAL(readyRead()), this, SLOT(onDataReady()));
    connect(m_client, SIGNAL(bytesWritten(qint64)), this, SLOT(onByterWritten(qint64)));
}

void ServerDemo::onConnected()
{
    QTcpSocket* m_client = dynamic_cast<QTcpSocket*>(sender());
    qDebug() << "onConnected()" ;
    QHostAddress m_adress = m_client->localAddress();
    qDebug() << "Local_Address" << m_adress.toString();
    qDebug() << "Local_Port" << m_client->localPort();
}

void ServerDemo::onDisconnected()
{
    qDebug() << "onDisconnected()";
}

void ServerDemo::onDataReady()
{
    QTcpSocket* m_client = dynamic_cast<QTcpSocket*>(sender());
    char buf[256] = {0};
    qDebug() << "onDataReady:" << m_client->read(buf,sizeof(buf)-1);
    qDebug() << "Data:" << buf;
}

void ServerDemo::onByterWritten(qint64 bytes)
{
    qDebug() << "onByterWirtten:" << bytes;
}

