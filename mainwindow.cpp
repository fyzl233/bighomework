#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "QPaintEvent"
#include "QPushButton"
#include <QDebug>

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::Mainwindow)
{
    int i,j;
    space[0][0]=220;space[0][1]=160;space[1][0]=340;space[1][1]=160;
    for(i=0;i<=2;i++)
    {
        for(j=1;j<=8;j++)
        {
            space[1+8*i+j][0]=120*j+100;
            space[1+8*i+j][1]=280+120*i;
        }
    }
    space[26][0]=220;space[26][1]=640;space[27][0]=340;space[27][1]=640;//防御塔中心点初始化
    for(i=0;i<=27;i++)
    {
        Buttons[i][0].setGeometry(space[i][0]+5,space[i][1]-40,50,25);
        Buttons[i][1].setGeometry(space[i][0]+5,space[i][1]+15,50,25);
        Buttons[i][0].setText(QString::fromUtf8("升级"));
        Buttons[i][1].setText(QString::fromUtf8("拆除"));
        Buttons[i][0].setParent(this);
        Buttons[i][1].setParent(this);
        Buttons[i][0].close();
        Buttons[i][1].close();
    }//升级按钮与拆除按钮的初始化
    for(i=0;i<=27;i++)
    {
        rs[i].setx(space[i][0]);
        rs[i].sety(space[i][1]);
        rs[i].setParent(this);
        rs[i].setGeometry(QRect(0,0,1280,720));
        rs[i].close();
    }//R防御塔的初始化
    for(i=0;i<=27;i++)
    {
        cs[i].setx(space[i][0]);
        cs[i].sety(space[i][1]);
        cs[i].setrow(space[i][1]/120);
        cs[i].setParent(this);
        cs[i].setGeometry(QRect(0,0,1280,720));
        cs[i].close();
    }//C++防御塔的初始化
    ui->setupUi(this);
    timerId = startTimer(DELAY);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::paintEvent(QPaintEvent *)
{
    QPainter Painter(this);
    QPixmap Pixmap("./pictures/map1.jpg");
    Painter.drawPixmap(0,0,1280,720,Pixmap);
}

void Mainwindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event ->y();
    if(x>=100)
    {
        int i;
        if(mousestatus==0)
        {
            for(i=2;i<=25;i++)
            {
                if(x>=space[i][0]-55&&x<=space[i][0]+55&&y>=space[i][1]-55&&y<=space[i][1]+55)
                {
                    if(spacestatus[i])
                    {
                        Buttons[i][0].show();
                        Buttons[i][1].show();
                        mousestatus = 3;
                        mouseflag = i;
                        break;
                    }
                }
            }
        }
        else if(mousestatus==3)
        {
            Buttons[mouseflag][0].close();
            Buttons[mouseflag][1].close();
            mousestatus = 0;
        }
        else
        {
            for(i=2;i<=25;i++)
            {
                if(x>=space[i][0]-55&&x<=space[i][0]+55&&y>=space[i][1]-55&&y<=space[i][1]+55)
                {
                    if(mousestatus==1)
                    {
                        rs[i].show();
                        defenders.push_back(rs+i);
                        spacestatus[i]=1;
                        break;
                    }
                    if(mousestatus==2)
                    {
                        cs[i].show();
                        defenders.push_back(cs+i);
                        spacestatus[i]=1;
                        break;
                    }
                }
            }
            mousestatus = 0;
        }
    }
}

void Mainwindow::on_pushButton_2_clicked()
{
    mousestatus = 1;
}

void Mainwindow::timerEvent(QTimerEvent *e)
{

    Q_UNUSED(e);
    time = time + 1;

    if(time%40==0)//创造小bug
    {
        attackers.push_back(new Smallbug(1200,(time%3+2)*120+40,100+round*20));
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->stackUnder(this);
    }
    if(time%1500==0)//改变轮数
    {
        round = round + 1;
    }
    int dfnum;
    if(defenders.empty())
    {
        dfnum = -1;
    }
    else dfnum = defenders.length()-1;
    int atnum;
    if(attackers.empty())
    {
        atnum = -1;
    }
    else atnum = attackers.length()-1;
    int i,j;
    for(i=0;i<=dfnum;i++)
    {
        if(defenders[i]->getsign()==0)//如果是R防御塔，进行距离攻击
        {
            for(j=0;j<=atnum;j++)
            {
                defenders[i]->distanceattack(*attackers[j]);
            }
        }
        if(defenders[i]->getsign()==1)//如果是C++防御塔，进行判断是否发射出子弹
        {
            if(time%80==0)
            {
                Cplusplus* p;
                p = dynamic_cast<Cplusplus*>(defenders[i]);//创建临时指针，强行转换派生类赋值
                for(j=0;j<=atnum;j++)
                {
                    if(p->getrow()==attackers[j]->getrow()&&p->getx()+60<=attackers[j]->getx())
                    {
                        defenders.push_back(p->firebullet());
                        Bullet* temp = dynamic_cast<Bullet*>(defenders[defenders.length()-1]);
                        temp->setParent(this);
                        temp->show();
                    }
                }
            }
        }
        if(defenders[i]->getsign()==2)//如果是防御塔射出的子弹，进行判断
        {
            Bullet* p;
            p = dynamic_cast <Bullet*> (defenders[i]);
            for(j=0;j<=atnum;j++)
            {
                p->distanceattack(*attackers[j]);
            }
            p -> move();
        }
    }
    for(i=0;i<=atnum;i++)
    {
        for(j=0;j<=dfnum;j++)
        {
            if(defenders[j]->getsign()==0||defenders[j]->getsign()==1)
                attackers[i]->distanceattack(*defenders[j]);
        }
    }
    for(i=0;i<=dfnum;i++)
    {
        if(defenders[i]->getHP()<=0||defenders[i]->getx()>1300)
        {
            defenders[i]->setHP(100);
            defenders[i]->close();
            defenders.remove(i);
            dfnum = dfnum - 1;
            spacestatus[i]=0;
            i = i - 1;
        }
    }
    for(i=0;i<=atnum;i++)
    {
        attackers[i]->move();
        if(attackers[i]->getHP()<=0)
        {
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            i = i - 1;
        }
    }
    for(i=0;i<=atnum;i++)
    {
        if(attackers[i]->getx()<100)
        {
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            HP = HP - 5 ;
        }
    }
    repaint();
}

void Mainwindow::on_pushButton_clicked()
{
    mousestatus = 2;
}
