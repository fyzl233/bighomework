#ifndef R_H
#define R_H
#include <QWidget>
#include "smallbug.h"
#include "midbug.h"
#include "bigbug.h"
#include "purplebug.h"
class R : public QWidget
{
    Q_OBJECT
public:
    explicit R(QWidget *parent = nullptr);
    R(int _x,int _y);
    void paintEvent(QPaintEvent *);
    void distanceattack(Smallbug &a);//距离攻击设为虚函数，可能具有一定的作用
    void distanceheal(R &a);
    friend Smallbug;//将敌军作为友元，方便操作
    friend Midbug;
    friend Bigbug;
    friend Purplebug;
    void setx(int x);
    void sety(int y);
    void setrow(int _row);
    void setHP(int _HP);
    void setlevel(int level);
    void levelup();
    void reset();
    int getHP();
    int getx();
    int gety();
    int getsign();
    int getrow();
    int getlevel();
    int num = 0;//防御塔所处的标号
protected:
    int row;
    int sign;/*标记防御塔种类，0为R防御塔，1为C++防御塔，2为C++防御塔射出的子弹，视为一个防御塔，3代表C++射出的紫色子弹，
    视为一个防御塔,4代表爆炸区域，视为一个防御塔*/
    int HP = 100;//防御塔血量
    int x;int y; //坐标
    int level = 1; //防御塔等级
    int MAXHP = 100;
    bool active = 1;
};

#endif // R_H
