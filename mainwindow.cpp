#include "mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "QPaintEvent"
#include "QPushButton"
#include <QDebug>
#include <fstream>
using namespace std;

Mainwindow::Mainwindow(QWidget *parent) : QMainWindow(parent)
{
    this->resize(1280, 720);
    this->setWindowTitle("Game");
    ifstream infile;
    infile.open("attackerdata.txt");
    if(infile)
    {
        infile>>dataMax;
        for(int i=1;i<=dataMax;i++)
        {
            infile>>Data[i][0]>>Data[i][1]>>Data[i][2]>>Data[i][3];
        }
        Data[dataMax+1][0]=-1;
        infile.close();
    }
    else
    {
        Data[datai][0]=-1;
        qDebug()<<"读取文件失败！";
    }
    label.setGeometry(670,30,451,31);
    label.setText("点击左边的按钮建立防御塔，抵挡bug大军的攻击吧！");
    label.setParent(this);
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
    blank.setGeometry(QRect(0,100,1280,620));//空白窗口的初始化
    blank.setParent(this);
    blank.show();
    playlist_main->addMedia(QUrl::fromLocalFile("music1.mp3"));
    playlist_main->addMedia(QUrl::fromLocalFile("music2.mp3"));
    playlist_main->setCurrentIndex(1);
    musicplayer_main->setPlaylist(playlist_main);
    musicplayer_main->setVolume(30) ;
    playlist_win->addMedia(QUrl::fromLocalFile("music3.mp3"));
    playlist_win->setCurrentIndex(1);
    musicplayer_win->setPlaylist(playlist_win);
    musicplayer_win->setVolume(30) ;
    playlist_lose->addMedia(QUrl::fromLocalFile("music4.mp3"));
    playlist_lose->setCurrentIndex(1);
    musicplayer_lose->setPlaylist(playlist_lose);
    musicplayer_lose->setVolume(30) ;
    finalbutton.setParent(this);
    finalbutton.setGeometry(QRect(538,575,120,45));
    finalbutton.setText(QString::fromUtf8("退出游戏"));
    finalbutton.close();
    connect(&finalbutton,&QPushButton::clicked,this,&QWidget::close);
    buildbutton_R.setParent(this);
    buildbutton_R.setGeometry(QRect(200,30,201,28));
    buildbutton_R.setText(QString::fromUtf8("建造“R”防御塔（$50）"));
    connect(&buildbutton_R,&QPushButton::clicked,this,[=](){
        if(mouseflag!=-1)
        {
            Buttons[mouseflag][0].close();//关闭升级窗口
            Buttons[mouseflag][1].close();//关闭拆除窗口
            Buttons[mouseflag][0].setEnabled(1);//无论如何，将升级按钮活性化
            mousestatus = 0;//鼠标状态设为初始状态
            mouseflag = -1;
        }
        if(Gold>=50)
        {
            label.setText("请点击空白区域的中心以建立防御塔");
            needGold = 50;
            mousestatus = 1;
        }
        else
        {
            label.setText("金币不足！修建R防御塔需要50金币");
        }
    });
    buildbutton_R.raise();
    buildbutton_C.setParent(this);
    buildbutton_C.setGeometry(QRect(430,30,211,28));
    buildbutton_C.setText(QString::fromUtf8("建造“C++”防御塔（$100）"));
    connect(&buildbutton_C,&QPushButton::clicked,this,[=](){
        if(mouseflag!=-1)
        {
            Buttons[mouseflag][0].close();//关闭升级窗口
            Buttons[mouseflag][1].close();//关闭拆除窗口
            Buttons[mouseflag][0].setEnabled(1);//无论如何，将升级按钮活性化
            mousestatus = 0;//鼠标状态设为初始状态
            mouseflag = -1;
        }
        if(Gold>=100)
        {
            label.setText("请点击空白区域的中心以建立防御塔");
            needGold = 100;
            mousestatus = 2;
        }
        else
        {
            label.setText("金币不足！修建C++防御塔需要100金币");
        }
    });
    buildbutton_C.raise();
    phasebutton.setParent(this);
    phasebutton.setGeometry(QRect(1130,25,121,41));
    phasebutton.setText(QString::fromUtf8("暂停/继续"));
    connect(&phasebutton,&QPushButton::clicked,this,[=](){
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
    });
    phasebutton.raise();
}

Mainwindow::~Mainwindow()
{
    delete musicplayer_main;
    delete musicplayer_win;
    delete musicplayer_lose;
    delete playlist_main;
    delete playlist_win;
    delete playlist_lose;
}

int Mainwindow::getdelay()
{
    return DELAY;
}

void Mainwindow::paintEvent(QPaintEvent *)
{
    if(Gamestatus==0)
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
        Painter.setPen(Qt::black);
        Painter.drawText(QRect(30,30,200,50),QString("HP: %1  Gold: %2").arg(HP).arg(Gold));
        Painter.drawText(QRect(30,50,200,50),QString("Round: %1/10").arg(round));
    }
    else if(Gamestatus==1)
    {
        raise();
        musicplayer_main->stop();
        musicplayer_lose->play();
        QPainter Painter(this);
        QPixmap Pixmap("./pictures/game_over.jpg");
        Painter.drawPixmap(0,0,1280,720,Pixmap);
        finalbutton.raise();
        finalbutton.show();
    }
    else
    {
        raise();
        musicplayer_main->stop();
        musicplayer_win->play();
        QPainter Painter(this);
        QPixmap Pixmap("./pictures/victory.jpg");
        Painter.drawPixmap(0,0,1280,720,Pixmap);
        finalbutton.raise();
        finalbutton.show();
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
                            if(defenders[j]->getsign()==0)
                            {
                                if(defenders[j]->getlevel()==1)
                                {
                                    label.setText("升级该R防御塔需要100金币");
                                    needGold = 100;
                                }
                                if(defenders[j]->getlevel()==2)
                                {
                                    label.setText("升级该R防御塔需要200金币");
                                    needGold = 200;
                                }
                            }
                            if(defenders[j]->getsign()==1)
                            {
                                if(defenders[j]->getlevel()==1)
                                {
                                    label.setText("升级该C++防御塔需要150金币");
                                    needGold = 150;
                                }
                                if(defenders[j]->getlevel()==2)
                                {
                                    label.setText("升级该C++防御塔需要300金币");
                                    needGold = 300;
                                }
                            }
                            break;
                        }
                    }
                    if(sign==0)
                    {
                        label.setText("该防御塔已达满级，无法继续升级");
                        Buttons[i][0].setEnabled(0);//如果sign为0，将按钮无效化，记得还原！
                    }
                    Buttons[i][0].show();
                    Buttons[i][0].stackUnder(&blank);//将升级控件依附在空白窗口之下，可以覆盖血条
                    Buttons[i][1].show();
                    Buttons[i][1].stackUnder(&blank);
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
            if(Gold>=needGold)//如果钱够的话
            {
                for(int j=0;j<=defenders.length()-1;j++)//通过迭代找到防御塔列表中对应的防御塔
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
                        Gold = Gold - needGold;
                        label.setText("防御塔升级成功!");
                        break;
                    }
                }
            }
            else
            {
                label.setText("金币不足!");
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
                    defenders[j]->reset();//重置防御塔血量
                    defenders[j]->close();//暂时关闭防御塔窗口
                    defenders.remove(j);//把它从防御塔列表中去掉
                    spacestatus[mouseflag]=0;//空间状态设为没有防御塔
                    label.setText("拆除防御塔成功!");
                    break;
                }
            }
        }
        Buttons[mouseflag][0].close();//关闭升级窗口
        Buttons[mouseflag][1].close();//关闭拆除窗口
        Buttons[mouseflag][0].setEnabled(1);//无论如何，将升级按钮活性化
        mousestatus = 0;//鼠标状态设为初始状态
        mouseflag = -1;
    }
    else//如果鼠标状态处于建设防御塔状态
    {
        bool success = 0;
        for(i=begin;i<=end;i++)
        {
            if(x>=space[i][0]-55&&x<=space[i][0]+55&&y>=space[i][1]-55&&y<=space[i][1]+55)
            {
                if(mousestatus==1&&spacestatus[i]==0)//如果鼠标为建设R防御塔状态
                {
                    rs[i].show();
                    defenders.push_back(rs+i);
                    spacestatus[i]=1;
                    Gold = Gold - needGold;
                    label.setText("建造防御塔成功！您可以点击防御塔来进行升级与拆除的操作");
                    success = true;
                    break;
                }
                if(mousestatus==2&&spacestatus[i]==0)//如果鼠标为建设C++防御塔状态
                {
                    cs[i].show();
                    defenders.push_back(cs+i);
                    spacestatus[i]=1;
                    Gold = Gold - needGold;
                    label.setText("建造防御塔成功！您可以点击防御塔来进行升级与拆除的操作");
                    success = true;
                    break;
                }
            }
        }
        mousestatus = 0;//鼠标状态设为初始状态
        if(!success)label.setText("无效区域！请重新点击左边的按钮以建造防御塔");
    }
    if(pause)update();//如果处于暂停状态，重绘
}

void Mainwindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    time = time + 1;
    if(round==6)//转换地图！！！！
    {
        whichmap = 2;
        begin = 0;
        end = 27;
    }
    while(time==Data[datai][0])
    {
        if(Data[datai][1]==0)
        {
            attackers.push_back(new Smallbug(Data[datai][2],Data[datai][3],100+round*10,totalatnum));
        }
        else if(Data[datai][1]==1)
        {
            attackers.push_back(new Midbug(Data[datai][2],Data[datai][3],150+round*15,totalatnum));
        }
        else if(Data[datai][1]==2)
        {
            attackers.push_back(new Bigbug(Data[datai][2],Data[datai][3],300+round*25,totalatnum));
        }
        else
        {
            attackers.push_back(new Purplebug(Data[datai][2],Data[datai][3],200+round*20,totalatnum));
        }
        attackers[attackers.length()-1]->setParent(this);
        attackers[attackers.length()-1]->show();
        attackers[attackers.length()-1]->setAttribute(Qt::WA_DeleteOnClose);
        totalatnum++;
        datai++;
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
            if(time%(70/((defenders[i]->getlevel()-1)%2+1))==0)
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
                defenders[i]->reset();//重置防御塔
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
            Gold = Gold + 15*(attackers[i]->getsign()+1);
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
            HP = HP - 5*(attackers[i]->getsign()+1);
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            i = i - 1;
        }
    }
    atnum = attackers.length();//重新获取进攻方的人数
    if(time>500&&atnum==0)
    {
        round++;
        time = 0;
    }
    if(HP<=0)
    {
        Gamestatus = 1;
        killTimer(timerId);
    }
    else if(round==11)
    {
        Gamestatus = 2;
        killTimer(timerId);
    }
    if(Gamestatus!=0)
    {
        buildbutton_R.close();
        buildbutton_C.close();
        phasebutton.close();
        label.close();
        int i,atnum = attackers.length();
        for(i=0;i<atnum;i++)
        {
            attackers[i]->close();
            attackers.remove(i);
            atnum = atnum -1;
            i = i -1;
        }
        int dfnum = defenders.length();
        for(i=0;i<dfnum;i++)
        {
            defenders[i]->close();
            defenders.remove(i);
            dfnum = dfnum -1;
            i = i -1;
        }
    }
    update();
    if(Gamestatus==0)
        blank.raise();//将空白窗口置于顶端
}
