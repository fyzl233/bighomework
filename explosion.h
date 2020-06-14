#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <bullet.h>

class Explosion:public Bullet
{
public:
    Explosion();
    Explosion(int _x,int _y);
    void distanceattack(Smallbug &a);
protected:
    QVector<int>nums;//记录已被造成伤害的敌军
    void paintEvent(QPaintEvent *);
    int radius = -15;
};

#endif // EXPLOSION_H
