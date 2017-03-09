#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "gamelist.h"
#include "datamanager.h"
#include "inputtimedialog.h"
#include "timedisplayer.h"
#include "datasaver.h"

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

    void timeInputed(QString time);

    void on_buttonRun_clicked();

    void runSelectedGame();

    void on_buttonDelete_clicked();

    void sysTrayAction(QSystemTrayIcon::ActivationReason reason);

    void reallyQuit();

    void on_buttonAdd_clicked();

    void on_timeUsedOut();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon * _sysTray;
    GameList * _gameList;
    TimeDisplayer * _timer;
    InputTimeDialog * _timeDialog;
    DataSaver * _dataSaver;
    /*
     * load when init, changed by input, save when exit
     */
    void closeEvent(QCloseEvent * event);
    SavingData _savingData;

    void save();

    bool dateDiffToSavedDate();

    //
    void initUI();
    void initSavingData();
    void initTimer();
    void initGameList();
    void initTimeDialog();
    void initSysTray();

};

#endif // MAINWINDOW_H
