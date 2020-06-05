#include "bigbug.h"
#include "midbug.h"
#include <QPainter>
#include "r.h"
#include <cmath>
Bigbug::Bigbug()
{

}

Bigbug::Bigbug(int _x,int _y,int _HP):Midbug(_x,_y,_HP)
{
    sign = 2;
}

void Bigbug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/bigbug.png");
    painter.drawPixmap(x-100,y-163,199,126,Pixmap);
    painter.setPen(QPen(Qt::yellow,10,Qt::SolidLine));
    painter.drawEllipse(x-225,y-325,450,450);
}

void Bigbug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<225)
    {
        a.HP= a.HP- 2;
    }
}
