#ifndef PURPLEBUG_H
#define PURPLEBUG_H

#include <midbug.h>
#include <QPainter>

class R;
class Purplebug:public Midbug//尝试实现弱AI
{
public:
    Purplebug();
    Purplebug(int _x,int _y,int _HP,int _num);
    void distanceattack(R &a);
    void move();
    int getCD();//得到换行的CD
    void up();
    void down();
protected:
    void paintEvent(QPaintEvent *);
    int changerowCD = 50;//换行的冷却时间，不让它一直换行
    int remain = 0;//标记还要走的步数
    int direction = 0;//标记行走方向
};

#endif // PURPLEBUG_H