#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
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

    void on_buttonDelete_clicked();

private:
    Ui::MainWindow *ui;
    GameList * _gameList;
    TimeDisplayer * _timer;
    InputTimeDialog * _timeDialog;
    DataSaver * _dataSaver;
    /*
     * load when init, changed by input, save when exit
     */
    SavingData _savingData;

    bool dateDiffToSavedDate();

    void closeEvent(QCloseEvent * event);
};

#endif // MAINWINDOW_H
