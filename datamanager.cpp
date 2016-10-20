#include "datamanager.h"

#include <QDebug>
#include <QVectorIterator>

DataManager::DataManager(QObject * parent)
    : QObject(parent),
    _timingOn(false),
    _gameRunningCount(0)
{
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    _leftTime = new QTime();
    setLeftTime();
    connect(_timer,SIGNAL(timeout()),
            this,SLOT(updateLeftTime())
            );
}


void DataManager::setLeftTime()
{
    //tmp set to specific value
    * _leftTime = QTime(3,2,11);
}

void DataManager::startTiming()
{
    _timingOn = true;
    _timer->start();
}

void DataManager::stopTiming()
{
    _timingOn = false;
}

QString DataManager::getLeftTime()
{
    return _leftTime->toString();
}

void DataManager::updateLeftTime()
{
    //update time
    if (_timingOn)
    {
        * _leftTime = _leftTime->addSecs(-1);
        //emit signal
        qDebug() << _leftTime -> toString();
        emit timeChanged(_leftTime->toString());
    }
}

void DataManager::runGame(QString filePath)
{
    startTiming();
    QProcess * newProcess = new QProcess;
    newProcess->start(filePath);
    _runningGames.append(newProcess);
    qDebug() << "timing started,  vector size: :" << _runningGames.size() ;
    connect(newProcess,SIGNAL(finished(int)),
            this,SLOT(onGameExited(int)));
    connect(newProcess,SIGNAL(finished(int)),
            newProcess,SLOT(deleteLater()));
//    system(filePath.toStdString().c_str());
}

void DataManager::removeEndedGames()
{
//    QVector<QProcess *>::iterator it = _runningGames.begin();
    auto it = _runningGames.begin();
    auto itEnd = _runningGames.end();
    while(it != itEnd)
    {
        qDebug() << "looping";
        if ((*it)->state() == QProcess::NotRunning)
        {
            qDebug() << "quited a game";
            -- itEnd;
            * it = std::move(*itEnd);
            //delete pointer,
            _runningGames.erase(itEnd);
        }
        else
        {
            qDebug() << "state other";
            ++ it;
        }
    }
}

void DataManager::onGameExited(int ExitID)
{
    qDebug() << "onGameExited:  vector size:  " << _runningGames.size();
    //remove ended games
    removeEndedGames();
    //check timer
    qDebug() << "check timer";
    if (_runningGames.size() == 0)
    {
        stopTiming();
    }
    qDebug() << "end ofonGameExited:  vector size:  " << _runningGames.size();
}

