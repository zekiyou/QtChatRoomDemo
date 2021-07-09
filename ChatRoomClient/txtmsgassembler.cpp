#include "txtmsgassembler.h"

TxtMsgAssembler::TxtMsgAssembler(QObject* parent) : QObject(parent)
{

}

void TxtMsgAssembler::clear()
{
    m_type = "";
    m_length = 0;
    m_data = "";
}

QString TxtMsgAssembler::fetch(int n)
{
    QString ret = "";

    for(int i=0; i<n; i++)
    {
        ret += m_queue.dequeue();
    }

    return ret;
}

void TxtMsgAssembler::prepare(const char* data, int len)
{
    if( data != nullptr )
    {
        for(int i=0; i<len; i++)
        {
            m_queue.enqueue(data[i]);
        }
    }
}

QSharedPointer<TextMessage> TxtMsgAssembler::assemble()
{
    TextMessage* ret = nullptr;
    bool tryMakeMsg = false;

    if( m_type == "" )
    {
        tryMakeMsg = makeTypeAndLength();
    }
    else
    {
        tryMakeMsg = true;
    }

    if( tryMakeMsg )
    {
        ret = makeMessage();
    }

    if( ret != nullptr )
    {
        clear();
    }

    return QSharedPointer<TextMessage>(ret);
}

QSharedPointer<TextMessage> TxtMsgAssembler::assemble(const char* data, int len)
{
    prepare(data, len);

    return assemble();
}

bool TxtMsgAssembler::makeTypeAndLength()
{
    bool ret = (m_queue.length() >= 8);

    if( ret )
    {
        QString len = "";

        m_type = fetch(4);

        len = fetch(4);

        m_length = len.trimmed().toInt(&ret, 16);

        if( !ret )
        {
            clear();
        }
    }

    return ret;
}

TextMessage* TxtMsgAssembler::makeMessage()
{
    TextMessage* ret = nullptr;

    if( m_type != "" )
    {
        int needed = m_length - m_data.length();
        int n = (needed <= m_queue.length()) ? needed : m_queue.length();

        m_data += fetch(n);

        if( m_length == m_data.length() )
        {
            ret = new TextMessage(m_type, m_data);
        }
    }

    return ret;
}

void TxtMsgAssembler::reset()
{
    clear();
    m_queue.clear();
}
