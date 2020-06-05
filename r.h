#ifndef R_H
#define R_H

#include <QWidget>
#include "smallbug.h"

class R : public QWidget
{
    Q_OBJECT
public:
    explicit R(QWidget *parent = nullptr);
    R(int _x,int _y);
    void paintEvent(QPaintEvent *);
    void distanceattack(Smallbug &a);//距离攻击设为虚函数，可能具有一定的作用
    friend Smallbug;//将敌军作为友元，方便操作
    void setx(int x);
    void sety(int y);
    int getHP();
    void setHP(int _HP);
    int getx();
    int getsign();
protected:
    int sign;//标记防御塔种类，0为R防御塔，1为C++防御塔，2为C++防御塔射出的子弹，视为一个防御塔
    int HP = 100;//防御塔血量
    int x;int y; //坐标
    int level = 1; //防御塔等级
signals:

};

#endif // R_H