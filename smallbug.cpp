#include "smallbug.h"
#include <QPainter>
#include "r.h"
#include <cmath>
#include <QDebug>
Smallbug::Smallbug(QWidget *parent) : QWidget(parent)
{

}

Smallbug::Smallbug(int _x,int _y,int _HP):HP(_HP),x(_x),y(_y)
{
    sign = 0;
    row = y/120;
    this->setGeometry(QRect(0,100,1280,620));
}


void Smallbug::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap Pixmap("./pictures/smallbug.png");
    painter.drawPixmap(x-65,y-147,131,94,Pixmap);
}

void Smallbug::move()
{
    x = x-2;
}

void Smallbug::distanceattack(R &a)
{
    if(sqrt((a.x-x)*(a.x-x)+(a.y-y)*(a.y-y))<5)
    {
        a.HP=a.HP-100;
        HP = HP - HP;
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
