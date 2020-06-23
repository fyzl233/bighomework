#include "explosion.h"
#include <cmath>
#include <QPainter>
#include <QDebug>
Explosion::Explosion()
{
    sign = 4;
}

Explosion::Explosion(int _x,int _y):Bullet(_x,_y)
{
    sign = 4;
}

void Explosion::paintEvent(QPaintEvent *)
{
    if(radius!=-15)
    {
        QPainter painter(this);
        QColor pink(241,158,194);
        painter.setPen(QPen(pink,30,Qt::SolidLine));
        painter.drawEllipse(x-radius,y-100-radius,2*radius,2*radius);
    }
    radius = radius + 30;
    if(radius>=195)
    {
        HP = 0;
    }
}

void Explosion::distanceattack(Smallbug &a)
{
    if(nums.contains(a.num)==0)
    {
        if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))>=radius-18
                &&sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=radius+18)
        {
            a.HP=a.HP-80;
            nums.push_back(a.num);
        }
    }
}
