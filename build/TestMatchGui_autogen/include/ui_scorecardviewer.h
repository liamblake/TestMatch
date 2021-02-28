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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScorecardViewer
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QTabWidget *tab_sv;
    QWidget *tab_sv_sc;
    QToolBox *toolBox_8;
    QWidget *page_15;
    QWidget *page_16;
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
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 981, 651));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignLeft);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1, Qt::AlignLeft);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tab_sv = new QTabWidget(verticalLayoutWidget);
        tab_sv->setObjectName(QString::fromUtf8("tab_sv"));
        tab_sv_sc = new QWidget();
        tab_sv_sc->setObjectName(QString::fromUtf8("tab_sv_sc"));
        toolBox_8 = new QToolBox(tab_sv_sc);
        toolBox_8->setObjectName(QString::fromUtf8("toolBox_8"));
        toolBox_8->setGeometry(QRect(0, 0, 801, 481));
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        page_15->setGeometry(QRect(0, 0, 801, 427));
        toolBox_8->addItem(page_15, QString::fromUtf8("Page 1"));
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        page_16->setGeometry(QRect(0, 0, 801, 427));
        toolBox_8->addItem(page_16, QString::fromUtf8("Page 2"));
        tab_sv->addTab(tab_sv_sc, QString());
        tab_sv_comm = new QWidget();
        tab_sv_comm->setObjectName(QString::fromUtf8("tab_sv_comm"));
        tab_sv->addTab(tab_sv_comm, QString());
        tab_sv_stats = new QWidget();
        tab_sv_stats->setObjectName(QString::fromUtf8("tab_sv_stats"));
        tab_sv->addTab(tab_sv_stats, QString());

        verticalLayout->addWidget(tab_sv);

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

        tab_sv->setCurrentIndex(0);
        toolBox_8->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ScorecardViewer);
    } // setupUi

    void retranslateUi(QMainWindow *ScorecardViewer)
    {
        ScorecardViewer->setWindowTitle(QCoreApplication::translate("ScorecardViewer", "TestMatch : Scorecard Viewer", nullptr));
        actionOpen->setText(QCoreApplication::translate("ScorecardViewer", "Open", nullptr));
        label->setText(QCoreApplication::translate("ScorecardViewer", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("ScorecardViewer", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("ScorecardViewer", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("ScorecardViewer", "TextLabel", nullptr));
        toolBox_8->setItemText(toolBox_8->indexOf(page_15), QCoreApplication::translate("ScorecardViewer", "Page 1", nullptr));
        toolBox_8->setItemText(toolBox_8->indexOf(page_16), QCoreApplication::translate("ScorecardViewer", "Page 2", nullptr));
        tab_sv->setTabText(tab_sv->indexOf(tab_sv_sc), QCoreApplication::translate("ScorecardViewer", "Scorecard", nullptr));
        tab_sv->setTabText(tab_sv->indexOf(tab_sv_comm), QCoreApplication::translate("ScorecardViewer", "Commentary", nullptr));
        tab_sv->setTabText(tab_sv->indexOf(tab_sv_stats), QCoreApplication::translate("ScorecardViewer", "Statistics", nullptr));
        menuFile->setTitle(QCoreApplication::translate("ScorecardViewer", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScorecardViewer: public Ui_ScorecardViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCORECARDVIEWER_H
