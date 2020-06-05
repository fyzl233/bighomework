#include "midbug.h"
#include <QPainter>
#include <r.h>
#include <cmath>

Midbug::Midbug()
{

}

Midbug::Midbug(int _x,int _y,int _HP):Smallbug(_x,_y,_HP)
{
    sign = 1;
}

void Midbug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/midbug.png");
    painter.drawPixmap(x-75,y-147,150,95,Pixmap);
    painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter.drawEllipse(x-150,y-250,300,300);
}

void Midbug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<150)
    {
        a.HP= a.HP- 1;
    }
}
