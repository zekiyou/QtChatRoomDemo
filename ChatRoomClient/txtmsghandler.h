#ifndef TXTMSGHANDLER_H
#define TXTMSGHANDLER_H

#include <QTcpSocket>
#include "textmessage.h"

class TxtMsgHandler
{

public:
    virtual void handle(QTcpSocket&, TextMessage&) = 0;
};

#endif // TXTMSGHANDLER_H

