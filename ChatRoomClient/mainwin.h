#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

class MainWin : public QWidget
{
    Q_OBJECT

    QVBoxLayout vMainLayout;
    QGroupBox msgGrpBx;
    QGroupBox inputGrpBx;
    QPlainTextEdit msgEditor;
    QLineEdit inputEditor;
    QPushButton logInOutBtn;
    QPushButton sendBtn;
    QLabel statusLb1;

    void initMsgGrpBx();
    void initInputBx();
public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
};

#endif // MAINWIN_H
