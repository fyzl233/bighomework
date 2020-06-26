#ifndef CPLUSPLUS_H
#define CPLUSPLUS_H

#include <r.h>
#include <bullet.h>


class Cplusplus:public R
{
public:
    Cplusplus();
    Cplusplus(int _x,int _y);
    Bullet* firebullet();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CPLUSPLUS_H
