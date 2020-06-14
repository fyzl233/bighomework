#include "cplusplus.h"
#include <QPainter>
#include <QDebug>
#include "pinkbullet.h"

Cplusplus::Cplusplus()
{
    sign = 1;
}

Cplusplus::Cplusplus(int _x,int _y):R(_x,_y)
{
    sign = 1;
}

void Cplusplus::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(level==1)
    {
        QPixmap Pixmap("./pictures/C++.png");
        painter.setClipRect(0,0,1280,720);
        painter.drawPixmap(x-58,y-36,115,72,Pixmap);
    }
    else if(level==2)
    {
        QPixmap Pixmap("./pictures/Cplusplus2.png");
        painter.setClipRect(0,0,1280,720);
        painter.drawPixmap(x-67,y-40,135,99,Pixmap);
    }
    else
    {
        QPixmap Pixmap("./pictures/Cplusplus3.png");
        painter.setClipRect(0,0,1280,720);
        painter.drawPixmap(x-67,y-40,135,99,Pixmap);
    }
    static const int HealthBarWidth = 60;
    static const int up = 35;
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

Bullet* Cplusplus::firebullet()
{
    if(level<=2)
    {
        return new Bullet(x+60,y);
    }
    else
    {
        return new Pinkbullet(x+60,y);
    }

}





