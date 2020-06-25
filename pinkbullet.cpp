#include "pinkbullet.h"
#include <cmath>

Pinkbullet::Pinkbullet()
{
    sign = 3;
}

Pinkbullet::Pinkbullet(int _x,int _y):Bullet(_x,_y)
{
    sign = 3;
}

void Pinkbullet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/pinkbullet.png");
    painter.setClipRect(0,0,1280,720);
    painter.drawPixmap(x-37,y-136,75,73,Pixmap);
}


void Pinkbullet::distanceattack(Smallbug &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=20)
    {
        HP = HP - HP;
    }
}
