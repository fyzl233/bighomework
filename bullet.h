#ifndef BULLET_H
#define BULLET_H

#include <r.h>
#include <smallbug.h>


class Bullet:public R
{
public:
    Bullet();
    Bullet(int _x,int _y);
    void move();
    virtual void distanceattack(Smallbug &a);

    friend Smallbug;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // BULLET_H
