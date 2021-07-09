#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include <QObject>

class TextMessage : public QObject
{
    QString m_type;
    QString m_data;

    Q_OBJECT
public:
    explicit TextMessage(QObject *parent = nullptr);
    TextMessage(QString type, QString data, QObject* parent = nullptr);

    QString type();
    int length();
    QString data();

    QString serialize();
    bool unserialize(QString s);

signals:

public slots:
};

#endif // TEXTMESSAGE_H
