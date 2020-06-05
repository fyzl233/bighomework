#ifndef SMALLBUG_H
#define SMALLBUG_H
#include <QWidget>
class Bullet;
class R;
class Smallbug : public QWidget
{
    Q_OBJECT
public:
    explicit Smallbug(QWidget *parent = nullptr);
    void move();
    virtual void distanceattack(R &a);//虚函数
    Smallbug(int _x,int _y,int _HP);
    friend R;
    friend Bullet;
    int getHP();
    int getx();
    int gety();
    int getsign();
    int getrow();
protected:
    void paintEvent(QPaintEvent *);
    int sign;//标记bug的种类,0代表小bug，1代表中bug，2代表大bug
    int HP;//血量
    int row;//bug所处的行数
    int x;//bug所处的横坐标
    int y;//bug所处的纵坐标
signals:

};

#endif // SMALLBUG_H
