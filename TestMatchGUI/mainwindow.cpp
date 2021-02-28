#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "scorecardviewer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
   //, sv(new Ui::ScorecardViewer)
{
    sv = new ScorecardViewer(nullptr, this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui, sv;
}


void MainWindow::on_pushButton_sv_clicked()
{
    // Open ScorecardViewer window and hide current
    sv->show();
    this->hide();
}
