#include "midbug.h"
#include <QPainter>
#include <r.h>
#include <cmath>

Midbug::Midbug()
{

}

Midbug::Midbug(int _x,int _y,int _HP,int _num):Smallbug(_x,_y,_HP,_num)
{
    sign = 1;
}

void Midbug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(slow)
    {
        QPixmap Pixmap("./pictures/slowmidbug.png");
        painter.drawPixmap(x-75,y-147,150,95,Pixmap);
        slow = 0;
    }
    else
    {
        QPixmap Pixmap("./pictures/midbug.png");
        painter.drawPixmap(x-75,y-147,150,95,Pixmap);
    }
    painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter.drawEllipse(x-150,y-250,300,300);
    static const int HealthBarWidth = 60;
    static const int up = 140;
    float ratio = 1.0*HP/MAXHP;
    if(ratio>0.6-1e-4)
    {

        painter.setPen(QPen(Qt::green,2,Qt::SolidLine));
        painter.setBrush(Qt::green);
    }
    else if(ratio>0.2-1e-4)
    {
        QColor earthyellow(244,208,0);
        painter.setPen(QPen(earthyellow,2,Qt::SolidLine));
        painter.setBrush(earthyellow);
    }
    else
    {
        QColor lightred(254,67,101);
        painter.setPen(QPen(lightred,2,Qt::SolidLine));
        painter.setBrush(lightred);
    }
    painter.drawRect(x-HealthBarWidth/2,y-up,HealthBarWidth,6);
    painter.setBrush(Qt::white);
    painter.drawRect(x-HealthBarWidth/2+ratio*HealthBarWidth,y-up,HealthBarWidth-ratio*HealthBarWidth,6);
}

void Midbug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<150)
    {
        a.HP= a.HP- 1;
    }
}
