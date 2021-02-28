#include "scorecardviewer.h"
#include "ui_scorecardviewer.h"

#include <QCloseEvent>

ScorecardViewer::ScorecardViewer(QWidget *parent, QWidget* c_menu) :
    QMainWindow(parent),
    ui(new Ui::ScorecardViewer),
    menu(c_menu)
{
    ui->setupUi(this);
}

ScorecardViewer::~ScorecardViewer()
{
    delete ui;
}

void ScorecardViewer::closeEvent (QCloseEvent *event) {
    menu->show();
    event->accept();
}
