#include "serverhandler.h"

ServerHandler::ServerHandler()
{

}

void ServerHandler::handle(QTcpSocket &obj, TextMessage &message)
{

    qDebug() << &obj;
    qDebug() << message.type();
    qDebug() << message.data();

    if (message.type() == "MSGA") {

        const QByteArray& ba = message.serialize().toLatin1();

        for (int i=0; i<m_nodeList.length(); i++) {
            Node* n = (m_nodeList.at(i));

            if( n->socket != nullptr){
                n->socket->write(ba);
            }

        }
    }

    if ( message.type() == "CONN") {

    }

    if ( message.type() == "DSCN") {

        for (int i=0; i<m_nodeList.length(); i++) {
            Node* n = (m_nodeList.at(i));

            if( n->socket == &obj ){
                n->socket = nullptr;
                break;
            }

        }

    }

    if ( message.type() == "LGIN") {

        QString data = message.data();
        int index = data.indexOf('\r');
        QString id = data.mid(0,index);
        QString pwd = data.mid(index+1);
        QString result = "";

        index = -1;

        for (int i=0;i<m_nodeList.length();i++) {

            if(id == m_nodeList.at(i)->id){
                index = i;
                break;
            }

        }

        if (index == -1){

            Node* newNode = new Node();

            if (newNode != nullptr){
                newNode->id = id;
                newNode->pwd = pwd;
                newNode->socket = &obj;

                m_nodeList.append(newNode);
                result = "LIOK";

            }

            else {
                result = "LIER";
            }


        }

        else {
            Node* n = m_nodeList.at(index);

            if( pwd == n->pwd){
                n->socket = &obj;
                result = "LGOK";
            }

            else {
                result = "LGER";
            }

        }

        obj.write(TextMessage(result,id).serialize().toLatin1());

    }



}
