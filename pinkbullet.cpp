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
    QPixmap Pixmap("./pictures/bullet.png");
    painter.setClipRect(0,0,1280,720);
    painter.drawPixmap(x-32,y-121,65,42,Pixmap);
    QColor pink(241,158,194);
    painter.setPen(QPen(pink,8,Qt::SolidLine));
    painter.drawEllipse(x-150,y-250,300,300);
}


void Pinkbullet::distanceattack(Smallbug &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=20)
    {
        HP = HP - HP;
    }
}
