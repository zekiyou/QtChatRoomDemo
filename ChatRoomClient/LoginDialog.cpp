#include "LoginDialog.h"
#include <QTime>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , userLabel(this)
    , pwdLabel(this)
    , captLabel(this)
    , userEdit(this)
    , pwdEdit(this)
    , captEdit(this)
    , loginBtn(this)
    , cancelBtn(this)
    , m_Timer(this)
{
    userLabel.setText("用户名");
    pwdLabel.setText("密码");
    loginBtn.setText("登陆");
    cancelBtn.setText("取消");

    userLabel.move(20,30);
    userLabel.resize(60,25);

    userEdit.move(85,30);
    userEdit.resize(180,25);

    pwdLabel.move(20,65);
    pwdLabel.resize(60,25);

    pwdEdit.move(85,65);
    pwdEdit.resize(180,25);
    pwdEdit.setEchoMode(QLineEdit::Password);

    loginBtn.move(180,145);
    loginBtn.resize(85,30);

    cancelBtn.move(85,145);
    cancelBtn.resize(85,30);

    setWindowTitle("Login");

    captLabel.setText("验证码");
    captLabel.move(20,100);
    captLabel.resize(60,25);
    captEdit.move(85,100);
    captEdit.resize(85,25);

    setFixedSize(285,205);

    connect(&loginBtn,SIGNAL(clicked()),this,SLOT(loginBtn_Clicked()));
    connect(&cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_Clicked()));
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(timer_Timerout()));

    qsrand(static_cast<uint>(QTime::currentTime().msec()));

    m_Captcha = getCaptcha();
    m_Color = getColor();

    m_Timer.start(100);
}

LoginDialog::~LoginDialog()
{

}

QString LoginDialog::getUser()
{
    return m_User;
}

QString LoginDialog::getPwd()
{
    return m_Pwd;
}

QString LoginDialog::getCaptcha()
{
    QString ret = "";

    for (int i = 0; i < 4; i++ ) {
            int c = (qrand() % 2)? 'a' : 'A';
            //随机大小写
            ret += static_cast<QChar>(c + qrand() % 26);
           //随机产生a-Z字符
    }
    return ret;
}

Qt::GlobalColor* LoginDialog::getColor()
{
    static Qt::GlobalColor colors[4];

    for (int i =0; i < 4; i++) {
        colors[i] = static_cast<Qt::GlobalColor>( 2 + qrand() % 16 );
    }
    return colors;
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(180,100,84,24,Qt::white);
    painter.setFont(QFont("Comic Sans MS" , 12));

    //绘制噪点
    for (int i=0; i<150; i++) {
        painter.setPen(m_Color[i%4]);
        painter.drawPoint(180+ qrand() % 84, 100 + qrand()% 24);
    }

    //绘制验证码字符
    for (int i=0; i<4; i++) {
        painter.setPen(m_Color[i]);
        painter.drawText(180 + 20 * i, 100, 20, 24, Qt::AlignCenter, QString(m_Captcha[i]));
    }

}

void LoginDialog::loginBtn_Clicked()
{

    //去除空格,统一大小写后进行验证码比较
    QString captcha = captEdit.text().replace(" ","");
    if ( captcha.toLower() == m_Captcha.toLower() ) {

        m_User = userEdit.text().trimmed();
        m_Pwd = pwdEdit.text();

        //用户名密码输入检查
        if(m_User == ""){
            QMessageBox::critical(this,"提示","用户名为空");
            m_Captcha = getCaptcha();
        }

        else if(m_Pwd == ""){
            QMessageBox::critical(this,"提示","密码为空");
            m_Captcha = getCaptcha();
        }

        else {

            done(Accepted);

        }

    }
    else{
        QMessageBox::critical(this,"错误","验证码错误");
        m_Captcha = getCaptcha();
    }

}

void LoginDialog::cancelBtn_Clicked()
{
    done(Rejected);
}

void LoginDialog::timer_Timerout()
{
    m_Color = getColor();
    update();
}
