#include "smallbug.h"
#include <QPainter>
#include "r.h"
#include <cmath>
#include <QDebug>
Smallbug::Smallbug(QWidget *parent) : QWidget(parent)
{

}

Smallbug::Smallbug(int _x,int _y,int _HP,int _num):HP(_HP),x(_x),y(_y),MAXHP(_HP),num(_num)
{
    sign = 0;
    row = y/120;
    this->setGeometry(QRect(0,100,1280,620));
}


void Smallbug::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    if(slow)
    {
        QPixmap Pixmap("./pictures/slowsmallbug.png");
        painter.drawPixmap(x-52,y-138,105,66,Pixmap);
        slow = 0;
    }
    else
    {
        QPixmap Pixmap("./pictures/smallbug.png");
        painter.drawPixmap(x-65,y-147,131,94,Pixmap);
    }
    static const int HealthBarWidth = 40;
    static const int up = 135;//向上偏移量
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

void Smallbug::move()
{
    if(slow)x--;
    else x = x-2;
}

void Smallbug::distanceattack(R &a)
{
    if(a.getsign()!=4)
    {
        if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<5)
        {
            a.HP=a.HP-100;
            HP = HP - HP;
        }
    }
}

int Smallbug::getHP()
{
    return HP;
}

int Smallbug::getx()
{
    return x;
}

int Smallbug::getsign()
{
    return sign;
}

int Smallbug::getrow()
{
    return row;
}

int Smallbug::gety()
{
    return y;
}
