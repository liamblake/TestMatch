/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_tb;
    QPushButton *pushButton_ms;
    QPushButton *pushButton_ss;
    QPushButton *pushButton_sv;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(673, 371);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_tb = new QPushButton(centralwidget);
        pushButton_tb->setObjectName(QString::fromUtf8("pushButton_tb"));
        pushButton_tb->setGeometry(QRect(140, 70, 391, 23));
        pushButton_ms = new QPushButton(centralwidget);
        pushButton_ms->setObjectName(QString::fromUtf8("pushButton_ms"));
        pushButton_ms->setGeometry(QRect(140, 130, 391, 23));
        pushButton_ss = new QPushButton(centralwidget);
        pushButton_ss->setObjectName(QString::fromUtf8("pushButton_ss"));
        pushButton_ss->setGeometry(QRect(140, 250, 391, 23));
        pushButton_sv = new QPushButton(centralwidget);
        pushButton_sv->setObjectName(QString::fromUtf8("pushButton_sv"));
        pushButton_sv->setGeometry(QRect(140, 190, 391, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 673, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TestMatch", nullptr));
        pushButton_tb->setText(QCoreApplication::translate("MainWindow", "Team Builder", nullptr));
        pushButton_ms->setText(QCoreApplication::translate("MainWindow", "Match Simulator", nullptr));
        pushButton_ss->setText(QCoreApplication::translate("MainWindow", "Scenario Simulator", nullptr));
        pushButton_sv->setText(QCoreApplication::translate("MainWindow", "Scorecard Viewer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
