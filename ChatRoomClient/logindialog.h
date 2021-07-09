#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QCloseEvent>
#include "databasedemo.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel userLabel;
    QLabel pwdLabel;
    QLabel captLabel;

    QLineEdit userEdit;
    QLineEdit pwdEdit;
    QLineEdit captEdit;

    QPushButton loginBtn;
    QPushButton cancelBtn;

    QString m_User;
    QString m_Pwd;
    QString m_Captcha;
    Qt::GlobalColor* m_Color;
    QTimer m_Timer;

    DataBaseDemo db;

public:
    LoginDialog(QWidget *parent = nullptr);

    ~LoginDialog();

    QString getUser();
    QString getPwd();
    QString getCaptcha();
    Qt::GlobalColor* getColor();
protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
private slots:
    void loginBtn_Clicked();
    void cancelBtn_Clicked();
    void timer_Timerout();
};

#endif // DIALOG_H
