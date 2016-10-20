#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //game list
    _gameList = new GameList();
    _gameList->setParent(this);
    ui -> layoutMain -> addWidget(_gameList);
    //datamanager
    _dataManager = new DataManager();
    _dataManager->setParent(this);
    //add LCD
    _lcdTime = new QLCDNumber(this);
    _lcdTime->setDigitCount(8);
    _lcdTime->display(_dataManager->getLeftTime());
    ui -> layoutMain -> addWidget(_lcdTime);
    //connection
    connect(_dataManager,SIGNAL(timeChanged(QString)),
            _lcdTime,SLOT(display(QString))
            );

    connect(_gameList,SIGNAL(toRumGame(QString)),
            _dataManager,SLOT(runGame(QString))
            );
    //this
    setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_New_Game_triggered()
{
    //for debug
    QString filePath = QFileDialog::getOpenFileName(this,tr("select a game"),"/home/nalleyer_inoru/tmp");
    _gameList -> addGame(filePath);
}

void MainWindow::on_actionSet_Total_Time_triggered()
{

}
