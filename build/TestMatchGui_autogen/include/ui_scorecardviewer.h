/********************************************************************************
** Form generated from reading UI file 'scorecardviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCORECARDVIEWER_H
#define UI_SCORECARDVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScorecardViewer
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QTabWidget *tabs_sv;
    QWidget *tab_sv_score;
    QWidget *tab_sv_comm;
    QWidget *tab_sv_stats;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScorecardViewer)
    {
        if (ScorecardViewer->objectName().isEmpty())
            ScorecardViewer->setObjectName(QString::fromUtf8("ScorecardViewer"));
        ScorecardViewer->resize(800, 600);
        actionOpen = new QAction(ScorecardViewer);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralwidget = new QWidget(ScorecardViewer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabs_sv = new QTabWidget(centralwidget);
        tabs_sv->setObjectName(QString::fromUtf8("tabs_sv"));
        tabs_sv->setGeometry(QRect(0, 0, 821, 611));
        tab_sv_score = new QWidget();
        tab_sv_score->setObjectName(QString::fromUtf8("tab_sv_score"));
        tabs_sv->addTab(tab_sv_score, QString());
        tab_sv_comm = new QWidget();
        tab_sv_comm->setObjectName(QString::fromUtf8("tab_sv_comm"));
        tabs_sv->addTab(tab_sv_comm, QString());
        tab_sv_stats = new QWidget();
        tab_sv_stats->setObjectName(QString::fromUtf8("tab_sv_stats"));
        tabs_sv->addTab(tab_sv_stats, QString());
        ScorecardViewer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScorecardViewer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        ScorecardViewer->setMenuBar(menubar);
        statusbar = new QStatusBar(ScorecardViewer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ScorecardViewer->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();

        retranslateUi(ScorecardViewer);

        tabs_sv->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ScorecardViewer);
    } // setupUi

    void retranslateUi(QMainWindow *ScorecardViewer)
    {
        ScorecardViewer->setWindowTitle(QCoreApplication::translate("ScorecardViewer", "TestMatch : Scorecard Viewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("ScorecardViewer", "Open", nullptr));
        tabs_sv->setTabText(tabs_sv->indexOf(tab_sv_score), QCoreApplication::translate("ScorecardViewer", "Scorecard", nullptr));
        tabs_sv->setTabText(tabs_sv->indexOf(tab_sv_comm), QCoreApplication::translate("ScorecardViewer", "Commentary", nullptr));
        tabs_sv->setTabText(tabs_sv->indexOf(tab_sv_stats), QCoreApplication::translate("ScorecardViewer", "Statistics", nullptr));
        menuFile->setTitle(QCoreApplication::translate("ScorecardViewer", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScorecardViewer: public Ui_ScorecardViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCORECARDVIEWER_H
