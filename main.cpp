#include "welcome.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Welcome w;
    w.show();
    return a.exec();
}
