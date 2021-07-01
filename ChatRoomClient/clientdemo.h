#ifndef CLIENTDEMP_H
#define CLIENTDEMP_H

#include <QObject>

class ClientDemo : public QObject
{
    Q_OBJECT
public:
    explicit ClientDemo(QObject *parent = nullptr);

signals:

public slots:
    void onConnected();
    void onDisconnected();
    void onDataReady();
    void onBytesWritten(qint64 bytes);
};

#endif // CLIENTDEMP_H
