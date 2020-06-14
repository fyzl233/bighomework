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

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
    int timerId;
    static int getdelay();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void timerEvent(QTimerEvent *e);
private:
    static const int DELAY = 40;//25帧的游戏
    Ui::Mainwindow *ui;//ui设计指针
    QPushButton Buttons[28][2];//升级防御塔、拆除防御塔的控件存储
    int space[28][2];//防御塔中心点的存储
    int mousestatus = 0;//鼠标状态的存储
    R rs[28];//R防御塔的存储
    Cplusplus cs[28];//C++防御塔的存储
    int spacestatus[28]={0};//空间状态的存储
    QVector <R*> defenders;//管理所有防御方的物件
    QVector <Smallbug*> attackers;//管理所有攻击方的物件
    int mouseflag;//记录哪一个空格的升级/拆除防御塔空间被打开
    int round = 1;//游戏轮数
    int time = 0;//用来记录一下时间，现实时间过去一秒，time就增加25
    int HP = 100;//玩家的血量，玩家的血量小于等于0时，判负（还未实现）
    int whichmap = 1;//标记目前处于哪一张地图
    bool test = 1;//用于测试
    int totalatnum = 0;//已经出现的敌人总数量
    QWidget blank;//空白窗口，用于搞一些事情
    bool pause = 0;//是否处于暂停状态
    int begin = 2;//迭代初值，第一张地图为2，第二张地图为0
    int end = 25;//迭代结束值，第一张地图为25，第二张地图为27
signals:


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
