#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QGridLayout>
#include "clientdemo.h"
#include "serverdemo.h"
#include "txtmsghandler.h"

class MainWin : public QWidget, public TxtMsgHandler
{
    Q_OBJECT

    QVBoxLayout vMainLayout;
    QGroupBox msgGrpBx;
    QGroupBox inputGrpBx;
    QPlainTextEdit msgEditor;
    QListWidget listWidget;
    QLineEdit inputEditor;
    //QPushButton logInOutBtn;
    QPushButton sendBtn;
    QLabel statusLb1;
    QString usr;
    QString pwd;

    ClientDemo m_Client;
    ServerDemo m_Server;

    void initMsgGrpBx();
    void initInputBx();
    void initMember();
    void initUserList();


public:
    MainWin(QWidget *parent = nullptr);
    void setUsername(QString username);
    void setPassword(QString password);
    void handle(QTcpSocket& obj, TextMessage& message);
    void initConnect();
    ~MainWin();
private slots:
    void sendBtnClicked();
    //void logInOutBtnClicked();
};

#endif // MAINWIN_H
