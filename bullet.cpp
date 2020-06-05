#include "bullet.h"
#include <QPainter>
#include <smallbug.h>
#include <cmath>
#include <QDebug>

Bullet::Bullet()
{

    sign = 2;
}

Bullet::Bullet(int _x,int _y):R(_x,_y)
{
    sign = 2;
    this->setGeometry(QRect(0,100,1280,620));
}

void Bullet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/bullet.png");
    painter.setClipRect(0,0,1280,720);
    painter.drawPixmap(x-32,y-121,65,42,Pixmap);
}

void Bullet::move()
{
    x = x + 10;
}

void Bullet::distanceattack(Smallbug &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=20)
    {
        qDebug()<<x;
        a.HP = a.HP - 50;
        HP = HP - HP;
    }
}
