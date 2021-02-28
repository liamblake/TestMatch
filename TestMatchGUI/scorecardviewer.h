#ifndef SCORECARDVIEWER_H
#define SCORECARDVIEWER_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class ScorecardViewer;
}

class ScorecardViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScorecardViewer(QWidget *parent = nullptr, QWidget* c_menu = nullptr);
    ~ScorecardViewer();

    void closeEvent (QCloseEvent *event);

private:
    Ui::ScorecardViewer *ui;
    QWidget *menu;
};

#endif // SCORECARDVIEWER_H
