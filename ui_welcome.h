/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QWidget *centralwidget;
    QPushButton *Startbutton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QString::fromUtf8("Welcome"));
        Welcome->resize(1280, 720);
        centralwidget = new QWidget(Welcome);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Startbutton = new QPushButton(centralwidget);
        Startbutton->setObjectName(QString::fromUtf8("Startbutton"));
        Startbutton->setGeometry(QRect(570, 470, 120, 45));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 1280, 720));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pictures/pictures/welcome.jpg")));
        Welcome->setCentralWidget(centralwidget);
        label->raise();
        Startbutton->raise();
        menubar = new QMenuBar(Welcome);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 26));
        Welcome->setMenuBar(menubar);
        statusbar = new QStatusBar(Welcome);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Welcome->setStatusBar(statusbar);

        retranslateUi(Welcome);
        QObject::connect(Startbutton, SIGNAL(clicked()), Welcome, SLOT(close()));

        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QMainWindow *Welcome)
    {
        Welcome->setWindowTitle(QCoreApplication::translate("Welcome", "Welcome", nullptr));
        Startbutton->setText(QCoreApplication::translate("Welcome", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
