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
    void distanceattack(R &a);
    void paintEvent(QPaintEvent *);
    Smallbug(int _x,int _y,int _HP);
    friend R;
    friend Bullet;
    int getHP();
    int getx();
    int getsign();
    int getrow();
protected:
    int sign;//标记bug的种类,0代表小bug，1代表中bug，2代表大bug
    int HP;//血量
    int row;//bug所处的行数
    int x;//bug所处的横坐标
    int y;//bug所处的纵坐标
signals:

};

#endif // SMALLBUG_H
