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
        rs[i].num = i;
        rs[i].setx(space[i][0]);
        rs[i].sety(space[i][1]);
        rs[i].setrow(space[i][1]/120);
        rs[i].setParent(this);
        rs[i].setGeometry(QRect(0,0,1280,720));
        rs[i].close();
    }//R防御塔的初始化
    for(i=0;i<=27;i++)
    {
        cs[i].num = i;
        cs[i].setx(space[i][0]);
        cs[i].sety(space[i][1]);
        cs[i].setrow(space[i][1]/120);
        cs[i].setParent(this);
        cs[i].setGeometry(QRect(0,0,1280,720));
        cs[i].close();
    }//C++防御塔的初始化
    ui->setupUi(this);
    blank.setGeometry(QRect(0,100,1280,620));//空白窗口的初始化
    blank.setParent(this);
    blank.show();
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

int Mainwindow::getdelay()
{
    return DELAY;
}

void Mainwindow::paintEvent(QPaintEvent *)
{
    QPainter Painter(this);
    if(whichmap==1)
    {
        QPixmap Pixmap("./pictures/map1.jpg");
        Painter.drawPixmap(0,0,1280,720,Pixmap);
    }
    else
    {
        QPixmap Pixmap("./pictures/map2.jpg");
        Painter.drawPixmap(0,0,1280,720,Pixmap);
    }
}

void Mainwindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event ->y();
    int i;
    if(mousestatus==0)//鼠标状态为0，未打开升级拆除窗口，且没有点建设防御塔按钮
    {
        for(i=begin;i<=end;i++)
        {
            if(x>=space[i][0]-55&&x<=space[i][0]+55&&y>=space[i][1]-55&&y<=space[i][1]+55)
            {
                if(spacestatus[i])//如果所点击的位置上面有防御塔
                {
                    int j;//迭代用
                    bool sign = 0;
                    for(j=0;j<=defenders.length()-1;j++)
                    {
                        if(i==defenders[j]->num)
                        {
                            if(defenders[j]->getlevel()<=2)sign = 1;//如果允许升级，sign记为1
                            break;
                        }
                    }
                    if(sign==0)Buttons[i][0].setEnabled(0);//如果sign为0，将按钮无效化，记得还原！
                    Buttons[i][0].show();
                    Buttons[i][0].stackUnder(&blank);//将升级控件依附在空白窗口之下，可以覆盖血条
                    Buttons[i][1].show();
                    mousestatus = 3;
                    mouseflag = i;//记录好哪一个升级、拆除窗口被打开
                    break;
                }
            }
        }
    }
    else if(mousestatus==3)//如果升级拆除窗口被打开了
    {
        if(x>=Buttons[mouseflag][0].x()&&x<=Buttons[mouseflag][0].x()+Buttons[mouseflag][0].width()
                &&y>=Buttons[mouseflag][0].y()&&y<=Buttons[mouseflag][0].y()+Buttons[mouseflag][0].height())
        {//如果点击的是升级按钮
            int j;
            for(j=0;j<=defenders.length()-1;j++)//通过迭代找到防御塔列表中对应的防御塔
            {
                if(mouseflag==defenders[j]->num)
                {
                    if(defenders[j]->getlevel()==1)//如果防御塔为1级
                    {
                        defenders[j]->levelup();
                    }
                    else if(defenders[j]->getlevel()==2)//如果防御塔为2级
                    {
                        defenders[j]->levelup();
                    }
                    break;
                }
            }
        }
        if(x>=Buttons[mouseflag][1].x()&&x<=Buttons[mouseflag][1].x()+Buttons[mouseflag][1].width()
                &&y>=Buttons[mouseflag][1].y()&&y<=Buttons[mouseflag][1].y()+Buttons[mouseflag][1].height())
        {//如果点击的是拆除按钮
            int j;
            for(j=0;j<=defenders.length()-1;j++)
            {
                if(mouseflag==defenders[j]->num)//通过迭代找到防御塔向量中对应的防御塔
                {
                    defenders[j]->setHP(100);//血量设为100
                    defenders[j]->setlevel(1);//等级归为1级
                    defenders[j]->close();//暂时关闭防御塔窗口
                    defenders.remove(j);//把它从防御塔列表中去掉
                    spacestatus[mouseflag]=0;//空间状态设为没有防御塔
                    Buttons[mouseflag][0].setEnabled(1);//无论如何，将升级按钮活性化
                    break;
                }
            }
        }
        Buttons[mouseflag][0].close();//关闭升级窗口
        Buttons[mouseflag][1].close();//关闭拆除窗口
        mousestatus = 0;//鼠标状态设为初始状态
    }
    else//如果鼠标状态处于建设防御塔状态
    {
        for(i=begin;i<=end;i++)
        {
            if(x>=space[i][0]-55&&x<=space[i][0]+55&&y>=space[i][1]-55&&y<=space[i][1]+55)
            {
                if(mousestatus==1&&spacestatus[i]==0)//如果鼠标为建设R防御塔状态
                {
                    rs[i].show();
                    defenders.push_back(rs+i);
                    spacestatus[i]=1;
                    break;
                }
                if(mousestatus==2&&spacestatus[i]==0)//如果鼠标为建设C++防御塔状态
                {
                    cs[i].show();
                    defenders.push_back(cs+i);
                    spacestatus[i]=1;
                    break;
                }
            }
        }
        mousestatus = 0;//鼠标状态设为初始状态
    }
    if(pause)update();//如果处于暂停状态，重绘
}

void Mainwindow::on_pushButton_2_clicked()
{
    mousestatus = 1;
}

void Mainwindow::timerEvent(QTimerEvent *e)
{

    Q_UNUSED(e);
    time = time + 1;
    if(time==500)//转换地图！！！！
    {
        whichmap=2;
        begin = 0;
        end = 27;
    }
    if(time%361==0)
    {
        attackers.push_back(new Purplebug(1200,((time+1)%3+2)*120+40,150+round*35,totalatnum));
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
        totalatnum++;
    }
    if(time%550==0)//创造大bug
    {
        attackers.push_back(new Bigbug(1200,((time+1)%3+2)*120+40,200+round*50,totalatnum));
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
        totalatnum++;
    }
    if(time%100==0)//创造中bug
    {
        attackers.push_back(new Midbug(1200,((time+1)%3+2)*120+40,150+round*35,totalatnum));
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
        totalatnum++;
    }
    if(time%40==0)//创造小bug
    {
        attackers.push_back(new Smallbug(1200,(time%3+2)*120+40,100+round*20,totalatnum));
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
        totalatnum++;
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
    for(i=0;i<=dfnum;i++)//防守方操作
    {
        if(defenders[i]->getsign()==0)//如果是R防御塔，进行距离攻击
        {
            for(j=0;j<=atnum;j++)
            {
                defenders[i]->distanceattack(*attackers[j]);
            }
            if(defenders[i]->getlevel()==3&&time%3==0)//如果是R防御塔且等级为3，对防御方进行距离治疗
            {
                for(j=0;j<=dfnum;j++)
                {
                    defenders[i]->distanceheal(*defenders[j]);
                }
            }
        }
        if(defenders[i]->getsign()==1)//如果是C++防御塔，进行判断是否发射出子弹
        {
            Cplusplus* p;
            p = dynamic_cast<Cplusplus*>(defenders[i]);//创建临时指针，强行转换派生类赋值
            if(time%(80/((defenders[i]->getlevel()-1)%2+1))==0)
            {
                for(j=0;j<=atnum;j++)//如果在同一行有发现敌军，发射子弹
                {
                    if(p->getrow()==attackers[j]->getrow()&&p->getx()+60<=attackers[j]->getx())
                    {
                        defenders.push_back(p->firebullet());
                        Bullet* temp = dynamic_cast<Bullet*>(defenders[defenders.length()-1]);
                        temp->setParent(this);
                        temp->show();
                        break;
                    }
                }
             }
        }
        if(defenders[i]->getsign()==2||defenders[i]->getsign()==3)//如果是防御塔射出的子弹，进行判断
        {
            Bullet* p;
            p = dynamic_cast <Bullet*> (defenders[i]);
            for(j=0;j<=atnum;j++)
            {
                p->distanceattack(*attackers[j]);
            }
            p -> move();
        }
        if(defenders[i]->getsign()==4)//如果是爆炸物，进行判断
        {
            Explosion* p;
            p = dynamic_cast <Explosion*> (defenders[i]);
            for(j=0;j<=atnum;j++)
            {
                p->distanceattack(*attackers[j]);
            }
        }
    }
    for(i=0;i<=atnum;i++)//进攻方操作
    {
        for(j=0;j<=dfnum;j++)//所有进攻方对防御方的R防御塔和C++防御塔进行距离攻击
        {
            if(defenders[j]->getsign()==0||defenders[j]->getsign()==1)
                attackers[i]->distanceattack(*defenders[j]);
        }
        if(attackers[i]->getsign()==3)//如果是purplebug
        {
            Purplebug* p;
            p = dynamic_cast<Purplebug*>(attackers[i]);
            if(p->getCD()==0)//如果purplebug的换行技能没在冷却中
            {
                int uprow = p->getrow()-1;
                int midrow = p->getrow();
                int downrow = p->getrow()+1;
                int num[3]={0};/*创建一个数组，num[0]为处于midrow中有威胁的目标的数量，
                num[1]为处与uprow中有威胁的目标的数量,num[2]为处于downrow中有威胁的目标数量*/
                if(whichmap==1)//若处于第一张地图，代表第一行和第五行暂未开放，不让purplebug走过去
                {
                    if(midrow==2)
                    {
                        num[1]=23333;
                    }
                    else if(midrow==4)
                    {
                        num[2]=23333;
                    }
                }
                else if(whichmap==2)//若处于第二张地图，没有第零行和第六行，不让purplebug走过去
                {
                    if(midrow==1)
                    {
                        num[1]=23333;
                    }
                    else if(midrow==5)
                    {
                        num[2]=23333;
                    }
                }
                int j;
                for(j=0;j<=dfnum;j++)
                {
                    if(defenders[j]->getrow()==midrow)
                    {
                        num[0]++;
                    }
                    if(defenders[j]->getrow()==uprow)
                    {
                        num[1]++;
                    }
                    if(defenders[j]->getrow()==downrow)
                    {
                        num[2]++;
                    }
                }
                int min = 2333;
                for(j=0;j<=2;j++)
                {
                    if(min>=num[j])
                    {
                        min = num[j];
                    }
                }//找到三个num里面的最小值（可能不唯一）
                for(j=0;j<=2;j++)
                {

                    if(min==num[j])
                        break;
                }
                if(j==1)p->up();//如果上方的防御方目标更少，往上走
                if(j==2)p->down();//如果下方的防御目标更少，往下走
            }
        }
    }
    for(i=0;i<=dfnum;i++)//防御方阵亡的处理
    {
        if(defenders[i]->getHP()<=0||defenders[i]->getx()>1500)
        {
            if(defenders[i]->getsign()==0||defenders[i]->getsign()==1)//如果是防御塔HP归0
            {
                defenders[i]->setHP(100);
                defenders[i]->setlevel(1);
                spacestatus[defenders[i]->num] = 0;//将地区状态设为没有防御塔
                Buttons[defenders[i]->num][0].setEnabled(1);//无论如何，将对应的升级按钮活性化
            }
            if(defenders[i]->getsign()==3)//如果是粉色子弹，创造爆炸物
            {
                defenders.push_back(new Explosion(defenders[i]->getx(),defenders[i]->gety()));
                Explosion* temp = dynamic_cast<Explosion*>(defenders[defenders.length()-1]);
                temp->setParent(this);
                temp->show();
            }
            defenders[i]->close();
            defenders.remove(i);
            dfnum = dfnum - 1;
            i = i - 1;
        }
    }
    for(i=0;i<=atnum;i++)//进攻方阵亡的处理
    {
        attackers[i]->move();//进攻方全体进行移动（这是一个虚函数）
        if(attackers[i]->getHP()<=0)
        {
            if(attackers[i]->getsign()==2)//如果是大bug，则创建三个小bug
            {
                int m;
                for(m=-1;m<=1;m++)
                {
                    attackers.push_back(new Smallbug(attackers[i]->getx(),attackers[i]->gety()+120*m,100+round*20,totalatnum));
                    attackers[attackers.length()-1]->setParent(this);
                    attackers[attackers.length()-1]->show();
                    attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
                    totalatnum++;
                }
            }
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            i = i - 1;
        }
    }
    for(i=0;i<=atnum;i++)//如果进攻方成功达到了入侵点
    {
        if(attackers[i]->getx()<100)
        {
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            HP = HP - 5 ;
        }
    }
    update();
    blank.raise();//将空白窗口置于顶端
}

void Mainwindow::on_pushButton_clicked()
{
    mousestatus = 2;
}

void Mainwindow::on_pushButton_3_clicked()
{
    if(pause==0)
    {
        pause = 1;
        killTimer(timerId);
    }
    else
    {
        timerId = startTimer(DELAY);
        pause = 0;
    }
}
