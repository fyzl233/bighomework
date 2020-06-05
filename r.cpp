#include "r.h"
#include <QPainter>
#include "QPixmap"
#include "cmath"
R::R(QWidget *parent) : QWidget(parent)
{
    sign = 0;
}

R::R(int _x,int _y):x(_x),y(_y)
{
    sign = 0;
}

void R::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/R.png");
    painter.setClipRect(0,0,1280,720);
    painter.drawPixmap(x-38,y-53,77,106,Pixmap);
    QColor pink(241,158,194);//RGB的值
    painter.setPen(QPen(pink,4,Qt::SolidLine));
    painter.drawEllipse(x-125-25*level,y-125-25*level,250+50*level,250+50*level);
}

void R::distanceattack(Smallbug &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<125+25*level)
    {
        a.HP = a.HP - 0.5*level;
    }
}

void R::setx(int x)
{
    this->x = x;
}

void R::sety(int y)
{
    this->y = y;
}

int R::getHP()
{
    return HP;
}

void R::setHP(int _HP)
{
    HP = _HP;
}

int R::getx()
{
    return x;
}

int R::getsign()
{
    return sign;
}
