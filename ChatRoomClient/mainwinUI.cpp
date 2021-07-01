#include "mainwin.h"
#include "logindialog.h"

void MainWin::initMsgGrpBx()
{
    //设置msgGrpBx的垂直布局
    QHBoxLayout* hbl =new QHBoxLayout;
    hbl->setContentsMargins(2,5,2,5);
    hbl->addWidget(&msgEditor);

    //QPlainTextEdit 设置为只读模式
    msgEditor.setReadOnly(true);

    msgGrpBx.setLayout(hbl);
    msgGrpBx.setTitle("聊天消息");
}

void MainWin::initInputBx()
{
    //设置inputGrpBx的垂直布局
    QGridLayout* gl = new QGridLayout;
    gl->setSpacing(10);
    gl->addWidget(&inputEditor, 0, 0, 1, 5);
    gl->addWidget(&statusLb1, 1, 0, 1, 3);
    gl->addWidget(&logInOutBtn, 1, 3);
    gl->addWidget(&sendBtn, 1, 4);

    //未登陆之前 LineEdit不可用
    inputEditor.setFixedHeight(30);
    inputEditor.setEnabled(false);

    //未登陆之前 status1为未登录
    statusLb1.setText("状态：未登录");

    logInOutBtn.setText("登陆");
    logInOutBtn.setFixedHeight(30);
    logInOutBtn.setFixedWidth(100);

    //未登陆之前 sendBtn不可用
    sendBtn.setText("发送");
    sendBtn.setFixedHeight(30);
    sendBtn.setFixedWidth(100);
    sendBtn.setEnabled(false);

    inputGrpBx.setLayout(gl);
    inputGrpBx.setTitle("用户名");
    inputGrpBx.setFixedHeight(100);

}

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{
        initMsgGrpBx();
        initInputBx();

        //设置Mainwin布局
        vMainLayout.setSpacing(10);
        vMainLayout.addWidget(&msgGrpBx);
        vMainLayout.addWidget(&inputGrpBx);

        setWindowTitle("Zeki's ChatRoom");
        setLayout(&vMainLayout);
        setMinimumSize(550,400);

        connect(&sendBtn, SIGNAL(clicked()), this, SLOT(sendBtnClicked()));
        connect(&logInOutBtn, SIGNAL(clicked()), this, SLOT(logInOutBtnClicked()));
}

MainWin::~MainWin()
{

}

void MainWin::sendBtnClicked()
{
    inputEditor.clear();
}

void MainWin::logInOutBtnClicked()
{
    LoginDialog ld(this);
    if ( ld.exec() == QDialog::Accepted ) {
        sendBtn.setEnabled(true);
        inputEditor.setEnabled(true);
        inputGrpBx.setTitle(ld.getUser());
        statusLb1.setText("状态:已登陆");
    }
}
