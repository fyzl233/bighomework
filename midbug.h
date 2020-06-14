#ifndef MIDBUG_H
#define MIDBUG_H

#include <smallbug.h>

class R;
class Midbug:public Smallbug
{
public:
    Midbug();
    Midbug(int _x,int _y,int _HP,int _num);
    void distanceattack(R &a);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // MIDBUG_H
