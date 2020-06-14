#include "bigbug.h"
#include "midbug.h"
#include <QPainter>
#include "r.h"
#include <cmath>
Bigbug::Bigbug()
{

}

Bigbug::Bigbug(int _x,int _y,int _HP,int _num):Midbug(_x,_y,_HP,_num)
{
    sign = 2;
}

void Bigbug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(slow)
    {
        QPixmap Pixmap("./pictures/slowbigbug.png");
        painter.drawPixmap(x-100,y-163,199,126,Pixmap);
        slow = 0;
    }
    else
    {
        QPixmap Pixmap("./pictures/bigbug.png");
        painter.drawPixmap(x-100,y-163,199,126,Pixmap);
    }
    painter.setPen(QPen(Qt::yellow,10,Qt::SolidLine));
    painter.drawEllipse(x-225,y-325,450,450);
    static const int HealthBarWidth = 100;
    static const int up = 160;
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

void Bigbug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<225)
    {
        a.HP= a.HP- 2;
    }
}
