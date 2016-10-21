#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //datamanager
    _dataManager = new DataManager();
    _dataManager->setParent(this);
    //game list
    _gameList = new GameList();
    _gameList->setParent(this);
    //from datamanager
    _gameList->buildFromPathList(_dataManager->getGameFullPathList());
    ui -> layoutList -> insertWidget(0,_gameList);
    //add LCD
    _lcdTime = new QLCDNumber(this);
    _lcdTime->setDigitCount(8);
    _lcdTime->display(_dataManager->getLeftTime());
    ui -> layoutMain -> addWidget(_lcdTime);
    //add input dialog
    _timeDialog = new InputTimeDialog();
    //connection
    connect(_dataManager,SIGNAL(timeChanged(QString)),
            _lcdTime,SLOT(display(QString))
            );

    connect(_gameList,SIGNAL(toRunGame(QString)),
            _dataManager,SLOT(runGame(QString))
            );
    connect(_timeDialog,SIGNAL(inputedTime(QString)),
            this,SLOT(timeInputed(QString)));
    //this
    setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeInputed(QString time)
{
    _dataManager->setTotalTime(time);
    QMessageBox mB;
    //show adialog
    mB.setText(tr("total time changed, will goes in to effect tomorrow."));
    mB.exec();
}

void MainWindow::on_actionAdd_New_Game_triggered()
{
    //for debug
    QString filePath = QFileDialog::getOpenFileName(this,tr("select a game"),"/home/nalleyer_inoru/tmp");
    _gameList -> addGame(filePath);
}

void MainWindow::on_actionSet_Total_Time_triggered()
{
    if ( _dataManager->dateChanged())
    {
        _timeDialog->show();
    }
    else
    {
        QMessageBox mB;
        mB.setText(tr("You can only set total time 1 time for 1 day."));
        mB.exec();
    }
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    _dataManager->saveToFile(_gameList->getGameList());
}

void MainWindow::on_buttonRun_clicked()
{
    _gameList->runSelectedGame();
}

void MainWindow::on_buttonDelete_clicked()
{
    _gameList->removeSelectedGame();
}
