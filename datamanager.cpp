#include "datamanager.h"

#include <QDebug>
#include <QVectorIterator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>

DataManager::DataManager(QObject * parent)
    : QObject(parent),
    _gameRunningCount(0)
{
    _nowDate = new QDate();
    _saveJson = new QJsonObject();
    (*_nowDate) = QDate::currentDate();
    qDebug() << _nowDate->toString();
    //check and read save file
    if (readFileOnStart())
    {
        setTotalTime(_saveJson->value(tr("totalTime")).toString());
        QDate savedDate = QDate::fromString(_saveJson->value(tr("date")).toString());
        if (savedDate == *_nowDate)
        {
            //today
            setLeftTimeFromJson();
            _dateChanged = false;
        }
        else
        {
            _dateChanged = true;
            //leftT <- total t
            //even if a user could back to yesterday
            *_leftTime = QTime::fromString(_totalTime);
        }
    }
    else
    {
        defaultSetting();
    }
}

void DataManager::defaultSetting()
{
    _dateChanged = true;
    _leftTime->setHMS(3,0,0);
    _totalTime = _leftTime->toString();
}

bool DataManager::readFileOnStart()
{
    QDir dir(_savePath);
    if (dir.exists())
    {
        if (QFileInfo::exists(dir.absoluteFilePath(_saveName)))
        {
            qDebug() << "file exists";
            //read file to json object
            QFile file(dir.absoluteFilePath(_saveName));
            if ( ! file.open(QFile::ReadOnly | QFile::Text) )
            {
                qDebug() << "open file failed!";
            }
            QJsonParseError jPE;
            QJsonDocument jD = QJsonDocument::fromJson(file.readAll(),&jPE);
            file.close();
            *(_saveJson) = jD.object();
            return true;
        }
    }
    //file not exists
    return false;
}

void DataManager::setLeftTimeFromJson()
{
    * _leftTime = QTime::fromString(_saveJson->value(tr("leftTime")).toString());
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

QString DataManager::getLeftTime() const
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
    //offset 1 sec if first game started
//    * _leftTime = _leftTime->addSecs(-1);
    emit timeChanged(_leftTime->toString());
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

void DataManager::setTotalTime(QString time)
{
    _totalTime = time;
    qDebug() << "total Time changed to: " << time;
}

void DataManager::resetLeftTime()
{
    _leftTime->fromString(_totalTime);
}
