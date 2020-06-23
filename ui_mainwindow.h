/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainwindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Mainwindow)
    {
        if (Mainwindow->objectName().isEmpty())
            Mainwindow->setObjectName(QString::fromUtf8("Mainwindow"));
        Mainwindow->resize(1280, 720);
        Mainwindow->setAutoFillBackground(false);
        centralwidget = new QWidget(Mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Mainwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 26));
        Mainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(Mainwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Mainwindow->setStatusBar(statusbar);

        retranslateUi(Mainwindow);

        QMetaObject::connectSlotsByName(Mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *Mainwindow)
    {
        Mainwindow->setWindowTitle(QCoreApplication::translate("Mainwindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mainwindow: public Ui_Mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
