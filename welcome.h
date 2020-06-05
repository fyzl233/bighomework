#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <mainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    Welcome(QWidget *parent = nullptr);
    ~Welcome();


private slots:
    void on_Startbutton_clicked();

private:
    Ui::Welcome *ui;
    Mainwindow *Game;
};
#endif // WELCOME_H
