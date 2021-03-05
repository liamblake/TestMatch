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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
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
    QWidget *inns1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QLabel *label_5;
    QTableWidget *tableWidget_2;
    QWidget *inns2;
    QWidget *tab_sv_comm;
    QWidget *tab_sv_stats;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScorecardViewer)
    {
        if (ScorecardViewer->objectName().isEmpty())
            ScorecardViewer->setObjectName(QString::fromUtf8("ScorecardViewer"));
        ScorecardViewer->resize(800, 546);
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
        inns1 = new QWidget();
        inns1->setObjectName(QString::fromUtf8("inns1"));
        inns1->setGeometry(QRect(0, 0, 801, 427));
        verticalLayoutWidget_2 = new QWidget(inns1);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 0, 801, 431));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(verticalLayoutWidget_2);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        tableWidget_2 = new QTableWidget(verticalLayoutWidget_2);
        if (tableWidget_2->columnCount() < 8)
            tableWidget_2->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(7, __qtablewidgetitem17);
        if (tableWidget_2->rowCount() < 1)
            tableWidget_2->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem18);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));

        verticalLayout_2->addWidget(tableWidget_2);

        toolBox_8->addItem(inns1, QString::fromUtf8("Page 1"));
        inns2 = new QWidget();
        inns2->setObjectName(QString::fromUtf8("inns2"));
        inns2->setGeometry(QRect(0, 0, 801, 427));
        toolBox_8->addItem(inns2, QString::fromUtf8("Page 2"));
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
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ScorecardViewer", "Batters", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ScorecardViewer", "R", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ScorecardViewer", "B", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ScorecardViewer", "4s", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ScorecardViewer", "6s", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ScorecardViewer", "SR", nullptr));
        label_5->setText(QCoreApplication::translate("ScorecardViewer", "Fall of Wickets:", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ScorecardViewer", "Bowling", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ScorecardViewer", "O", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ScorecardViewer", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ScorecardViewer", "R", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ScorecardViewer", "W", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ScorecardViewer", "Econ", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ScorecardViewer", "Wd", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->horizontalHeaderItem(7);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ScorecardViewer", "NB", nullptr));
        toolBox_8->setItemText(toolBox_8->indexOf(inns1), QCoreApplication::translate("ScorecardViewer", "Page 1", nullptr));
        toolBox_8->setItemText(toolBox_8->indexOf(inns2), QCoreApplication::translate("ScorecardViewer", "Page 2", nullptr));
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
