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
    QColor skyblue(0,191,255);
    QColor springgreen(0,255,127);
    if(level==1)
    {
        painter.setPen(QPen(pink,4,Qt::SolidLine));
        painter.drawEllipse(x-150,y-150,300,300);
    }
    else if(level==2)
    {
        painter.setPen(QPen(skyblue,4,Qt::SolidLine));
        painter.drawEllipse(x-175,y-175,350,350);
    }
    else
    {
        painter.setPen(QPen(skyblue,4,Qt::SolidLine));
        painter.drawEllipse(x-200,y-200,400,400);
        painter.setPen(QPen(springgreen,4,Qt::SolidLine));
        painter.drawEllipse(x-125,y-125,250,250);
    }
    static const int HealthBarWidth = 60;
    static const int up = 40;
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

void R::distanceattack(Smallbug &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=125+25*level)
    {
        a.HP = a.HP - 1;
    }
    if(level>=2)
    {
        if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=125+25*level)
        {
            a.slow = 1;
        }
    }
}

void R::distanceheal(R &a)//三级专用技能：治疗
{
    if(a.getsign()<=1&&sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<=125&&a.HP<=a.MAXHP-1)//如果是防御塔，血量没满，回血
    {
        a.HP = a.HP + 1;
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

int R::getrow()
{
    return row;
}

void R::setrow(int _row)
{
    row = _row;
}

void R::levelup()
{
    level++;
    if(sign==0)//如果是R防御塔，提升血量和血量上限
    {
        MAXHP = MAXHP + 100;
        HP = HP + 100;
    }
}

int R::getlevel()
{
    return level;
}

int R::gety()
{
    return y;
}

void R::setlevel(int level)
{
    this->level=level;
}

void R::reset()
{
    level = 1;
    MAXHP = 100;
    HP = 100;
}
