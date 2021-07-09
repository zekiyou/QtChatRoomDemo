#ifndef TXTMSGASSEMBLER_H
#define TXTMSGASSEMBLER_H

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include "textmessage.h"

class TxtMsgAssembler : public QObject
{
    QQueue<char> m_queue;
    QString m_type;
    int m_length;
    QString m_data;

    void clear();
    QString fetch(int n);
    bool makeTypeAndLength();
    TextMessage* makeMessage();
public:
    TxtMsgAssembler(QObject* parent = nullptr);
    void prepare(const char* data, int len);
    QSharedPointer<TextMessage> assemble(const char* data, int len);
    QSharedPointer<TextMessage> assemble();
    void reset();
};

#endif // TXTMSGASSEMBLER_H
