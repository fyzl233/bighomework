#ifndef PINKBULLET_H
#define PINKBULLET_H

#include <bullet.h>

class Pinkbullet: public Bullet
{
public:
    Pinkbullet();
    Pinkbullet(int _x,int _y);
    void distanceattack(Smallbug &a);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PINKBULLET_H
