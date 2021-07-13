#include "mainwin.h"

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
    //gl->addWidget(&logInOutBtn, 1, 3);
    gl->addWidget(&sendBtn, 1, 4);

    inputEditor.setFixedHeight(30);


    //logInOutBtn.setText("登陆");
    //logInOutBtn.setFixedHeight(30);
    //logInOutBtn.setFixedWidth(100);


    sendBtn.setText("发送");
    sendBtn.setFixedHeight(30);
    sendBtn.setFixedWidth(100);

    inputGrpBx.setLayout(gl);
    inputGrpBx.setTitle("用户名");
    inputGrpBx.setFixedHeight(100);



    statusLb1.setText("状态:已登陆");


}

void MainWin::initMember()
{
    m_Client.setHandler(this);
}

void MainWin::initUserList()
{
    listWidget.setFixedWidth(150);
    listWidget.setFocusPolicy(Qt::NoFocus);
}

void MainWin::initConnect()
{
    if (m_Client.connectTo("127.0.0.1",8080)) {

        TextMessage tm("LGIN", usr+'\r'+pwd );
        m_Client.send(tm);

    } else {
        QMessageBox::critical(this,"Error","无法连接服务器");
    }
}

MainWin::MainWin(QWidget *parent)
    : QWidget(parent)
{

        initMsgGrpBx();
        initInputBx();
        initMember();
        initUserList();

        //设置Mainwin布局
        vMainLayout.setSpacing(10);
        vMainLayout.addWidget(&msgGrpBx);
        vMainLayout.addWidget(&inputGrpBx);

        QHBoxLayout* hbl =new QHBoxLayout;
        hbl->addWidget(&listWidget);
        hbl->addLayout(&vMainLayout);

        setWindowTitle("Zeki's ChatRoom");
        setLayout(hbl);
        setMinimumSize(650,500);

        connect(&sendBtn, SIGNAL(clicked()), this, SLOT(sendBtnClicked()));
        //connect(&logInOutBtn, SIGNAL(clicked()), this, SLOT(logInOutBtnClicked()));

}

void MainWin::setUsername(QString username)
{
    this->usr = username;
    inputGrpBx.setTitle(username);
}

void MainWin::setPassword(QString password)
{
    this->pwd = password;
}

void MainWin::handle(QTcpSocket &obj, TextMessage &message)
{
    if (message.type() == "CONN" ) {

    } else if ( message.type() == "DSCN" ) {

    } else if (message.type() == "LIOK") {
        QMessageBox::critical(this,"OK","已连接服务器");
    } else if (message.type() == "LIER") {
        QMessageBox::critical(this,"ERROR","未连接服务器");
    } else if (message.type() == "MSGA") {
        msgEditor.appendPlainText(message.data());
    } else if (message.type() == "USER") {
        QStringList users = message.data().split("\r",QString::SkipEmptyParts);

        listWidget.clear();

        for (int i=0; i<users.length(); i++) {

            QListWidgetItem* item = new QListWidgetItem;

            if (item !=nullptr){
                item->setText(users[i]);
                item->setCheckState(Qt::Unchecked);
                listWidget.addItem(item);
            }

        }

    }

}

MainWin::~MainWin()
{

}

void MainWin::sendBtnClicked()
{

    QString text = inputGrpBx.title() + "  " + QTime::currentTime().toString("HH:mm:ss") + "\n" + "  " + inputEditor.text() + "\n" ;
    TextMessage tm("MSGA",text);

    if (m_Client.send(tm))
        inputEditor.clear();
}

