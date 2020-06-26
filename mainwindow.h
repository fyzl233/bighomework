#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <r.h>
#include <QPushButton>
#include <QVector>
#include <cplusplus.h>
#include <pinkbullet.h>
#include <explosion.h>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
    static int getdelay();
    int timerId;
    QMediaPlayer * musicplayer_main = new QMediaPlayer;
    QMediaPlayer * musicplayer_win = new QMediaPlayer;
    QMediaPlayer * musicplayer_lose = new QMediaPlayer;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *e);
private:
    static const int DELAY = 40;//25帧的游戏
    int space[28][2];//防御塔中心点的存储
    int mousestatus = 0;//鼠标状态的存储
    int spacestatus[28]={0};//空间状态的存储
    int mouseflag = -1;//记录哪一个空格的升级/拆除防御塔空间被打开,为-1时代表没有空格被打开
    int round = 1;//游戏轮数
    int time = 0;//用来记录一下时间，现实时间过去一秒，time就增加25
    int HP = 100;//玩家的血量，玩家的血量小于等于0时，判负
    int whichmap = 1;//标记目前处于哪一张地图
    int totalatnum = 0;//已经出现的敌人总数量
    int begin = 2;//迭代初值，第一张地图为2，第二张地图为0
    int end = 25;//迭代结束值，第一张地图为25，第二张地图为27
    int Gold = 1000;//初始送玩家1000块钱
    int needGold = 0;//执行操作所需要的金币
    int dataMax = 0;//attackerdata中存有多少敌人
    int datai = 1;//已经到了data中的第几个敌人
    int Data[233][4];//存储敌人信息的数组
    int Gamestatus = 0;
    bool pause = 0;//是否处于暂停状态
    R rs[28];//R防御塔的存储
    Cplusplus cs[28];//C++防御塔的存储
    QVector <R*> defenders;//管理所有防御方的物件
    QVector <Smallbug*> attackers;//管理所有攻击方的物件
    QLabel label;//文本框
    QWidget blank;//空白窗口，用于搞一些事情
    QMediaPlaylist * playlist_main = new QMediaPlaylist;
    QMediaPlaylist * playlist_win = new QMediaPlaylist;
    QMediaPlaylist * playlist_lose = new QMediaPlaylist;
    QPushButton Buttons[28][2];//升级防御塔、拆除防御塔的控件存储
    QPushButton finalbutton;
    QPushButton buildbutton_R;
    QPushButton buildbutton_C;
    QPushButton phasebutton;
};

#endif // MAINWINDOW_H
