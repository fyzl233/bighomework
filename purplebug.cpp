#include "purplebug.h"
#include <QPainter>
#include <r.h>
#include <cmath>
#include <QDebug>

Purplebug::Purplebug()
{

}

Purplebug::Purplebug(int _x,int _y,int _HP,int _num):Midbug(_x,_y,_HP,_num)
{
    sign = 3;
}

void Purplebug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(slow)
    {
        QPixmap Pixmap("./pictures/slowmidbug.png");
        painter.drawPixmap(x-75,y-157,150,95,Pixmap);
        slow = 0;
    }
    else
    {
        QPixmap Pixmap("./pictures/purplebug.png");
        painter.drawPixmap(x-103,y-174,207,148,Pixmap);
    }
    QColor purple(128,0,128);//RGB的值
    painter.setPen(QPen(purple,4,Qt::SolidLine));
    painter.drawEllipse(x-150,y-250,300,300);
    static const int HealthBarWidth = 60;
    static const int up = 150;
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

void Purplebug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<150)
    {
        a.HP= a.HP- 2;
    }
}

int Purplebug::getCD()
{
    return changerowCD;
}

void Purplebug::up()
{
    row = row-1;
    remain = 60;//向上移动60次
    direction = -1;
    changerowCD = 90;//设置换行冷却时间
}

void Purplebug::down()
{
    row = row+1;
    remain = 60;//向下移动60次
    direction = 1;
    changerowCD = 90;//设置换行冷却时间
}

void Purplebug::move()
{
    if(slow)x--;
    else x = x - 2;
    if(direction!=0)
    {
        y = y + direction*2;
        remain--;
        if(remain==0)
        {
            direction = 0;
        }
    }
    if(changerowCD)
    {
        changerowCD--;
    }
}
