#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QAction>

void initWithDefaultSetting(SavingData & sD);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initSavingData();
    initGameList();
    initTimer();
    initSysTray();
    initUI();
    connect(_gameList,SIGNAL(firstGameStarted()),
            _timer,SLOT(start()));
    connect(_gameList,SIGNAL(allGameExited()),
            _timer,SLOT(stop()));
    setFixedSize(this->size());
}

void MainWindow::initSavingData()
{
    _dataSaver = new DataSaver(this);
    if (_dataSaver->savingFileValid())
        _savingData = _dataSaver->load();
    else
        initWithDefaultSetting(_savingData);
}

void MainWindow::initTimer()
{
    _timer = new TimeDisplayer(_savingData.getLeftTime(),this);
    if (dateDiffToSavedDate())
    {
        _timer->setTime(_savingData.getTotalTime());
        _savingData.setTotalTimeChanged(false);
    }
}

void MainWindow::initTimeDialog()
{
    _timeDialog = new InputTimeDialog();
    connect(_timeDialog,SIGNAL(inputedTime(QString)),
            this,SLOT(timeInputed(QString)));
}

void MainWindow::initGameList()
{
    _gameList = new GameList(_savingData.getGameList(),this);
}


void MainWindow::initUI()
{
    ui->setupUi(this);
    ui -> layoutList -> insertWidget(0,_gameList);
    ui -> layoutMain -> addWidget(_timer);
}


void MainWindow::initSysTray()
{
    _sysTray = new QSystemTrayIcon(this);
    _sysTray->setIcon(QIcon(QPixmap(":/icon/icon.png")));
    connect(_sysTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(sysTrayAction(QSystemTrayIcon::ActivationReason)));
    //menu
    auto trayMenu = new QMenu(this);
    auto resetAction = new QAction(this);
    resetAction->setText(tr("show Window"));
    connect(resetAction,SIGNAL(triggered(bool)),
            this,SLOT(showNormal()));

    auto quitAction = new QAction(this);
    quitAction->setText(tr("quit"));
    connect(quitAction,SIGNAL(triggered(bool)),
            this,SLOT(reallyQuit()));

    trayMenu->addAction(resetAction);
    trayMenu->addAction(quitAction);
    _sysTray->setContextMenu(trayMenu);
    _sysTray->show();
}


void initWithDefaultSetting(SavingData & sD)
{
    qDebug() << "default setting";
    sD.setDate(QDate::currentDate());
    sD.setLeftTime(QTime(3,0,0));
    sD.setTotalTime(QTime(3,0,0));
    sD.setTotalTimeChanged(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeInputed(QString time)
{
    _savingData.setTotalTime(QTime::fromString(time));
    QMessageBox::information(nullptr,"",tr("total time changed, will goes in to effect tomorrow."));
    _savingData.setTotalTimeChanged(true);
}

bool MainWindow::dateDiffToSavedDate()
{
    QDate nowDate = QDate::currentDate();
    return nowDate != _savingData.getDate();
}

void MainWindow::on_actionAdd_New_Game_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("select a game"),"",tr("games(*.exe)"));
    _gameList -> addGame(filePath);
}

void MainWindow::on_actionSet_Total_Time_triggered()
{
    if (! _savingData.getTotalTimeChanged())
    {
        _timeDialog->show();
    }
    else
    {
        QMessageBox::information(nullptr,"",tr("You can only set total time 1 time for 1 day."));
    }
}

void MainWindow::sysTrayAction(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << reason;
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        showNormal();
    }
}

void MainWindow::save()
{
    _savingData = SavingData(QDate::currentDate(),_savingData.getTotalTime(),_timer->getTime(),_gameList->getGameList(),_savingData.getTotalTimeChanged());
    _dataSaver->save(_savingData);
}

void MainWindow::reallyQuit()
{
    save();
    qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    hide();
    _sysTray->show();
    _sysTray->showMessage("",tr("now in taskBar."));
    event->ignore();
}

void MainWindow::on_buttonRun_clicked()
{
    _gameList->runSelectedGame();
}

void MainWindow::on_buttonDelete_clicked()
{
    _gameList->removeSelectedGame();
}

void MainWindow::on_buttonAdd_clicked()
{
    on_actionAdd_New_Game_triggered();
}
