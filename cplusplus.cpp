#include "cplusplus.h"
#include <QPainter>
#include <QDebug>

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
    QPixmap Pixmap("./pictures/C++.png");
    painter.setClipRect(0,0,1280,720);
    painter.drawPixmap(x-58,y-36,115,72,Pixmap);
}

Bullet* Cplusplus::firebullet()
{
    return new Bullet(x+60,y);
}

int Cplusplus::getrow()
{
    return row;
}

void Cplusplus::setrow(int _row)
{
    row = _row;
}

