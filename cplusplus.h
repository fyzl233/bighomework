#ifndef CPLUSPLUS_H
#define CPLUSPLUS_H

#include <r.h>
#include <bullet.h>


class Cplusplus:public R
{
public:
    Cplusplus();
    Cplusplus(int _x,int _y);
    void paintEvent(QPaintEvent *);
    Bullet* firebullet();
    int getrow();
    void setrow(int _row);
protected:
    int row;
};

#endif // CPLUSPLUS_H
