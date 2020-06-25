#include "welcome.h"
#include "ui_welcome.h"
#include "mainwindow.h"


Welcome::Welcome(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Welcome)
{
    Game = new Mainwindow;
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
    delete Game;
}

void Welcome::on_Startbutton_clicked()
{
    Game->show();//ui文件中实现了Welcome窗口的关闭
    Game->timerId = Game->startTimer(Game->getdelay());
    Game->musicplayer_main->play();
}
