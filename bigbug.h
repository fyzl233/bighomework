#ifndef BIGBUG_H
#define BIGBUG_H
#include <midbug.h>

class R;
class Bigbug:public Midbug
{
public:
    Bigbug();
    Bigbug(int _x,int _y,int _HP,int _num);
    void distanceattack(R &a);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // BIGBUG_H
