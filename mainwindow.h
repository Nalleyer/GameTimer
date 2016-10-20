#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gamelist.h>
#include <datamanager.h>
#include <QLCDNumber>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAdd_New_Game_triggered();

    void on_actionSet_Total_Time_triggered();

private:
    Ui::MainWindow *ui;
    GameList * _gameList;
    QLCDNumber * _lcdTime;
    DataManager * _dataManager;
};

#endif // MAINWINDOW_H
