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
    _timingOn(false),
    _gameRunningCount(0)
{
    _timer = new QTimer(this);
    _timer->setInterval(1000);
    _leftTime = new QTime();
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
    //connect
    connect(_timer,SIGNAL(timeout()),
            this,SLOT(updateLeftTime())
            );
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

QVector<QString> DataManager::getGameFullPathList() const
{
    QVector<QString> gameList;
    QJsonArray jA = _saveJson->value(tr("games")).toArray();
    qDebug() << "building path vector: ";
    foreach (const QJsonValue & value, jA)
    {
        qDebug() << value.toString() << " ";
        gameList.append(value.toString());
    }
    return gameList;
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

void DataManager::saveToFile(const QVector<QString> & gameList) const
//void DataManager::saveToFile(const QDate *nowDate, const QTime *leftTime, const QVector<QString> *gameList, const QString totalTime) const
{
    QJsonObject jO;
    jO.insert(tr("date"),_nowDate->toString());
    jO.insert(tr("leftTime"),_leftTime->toString());
    jO.insert(tr("totalTime"),_totalTime);
    QJsonArray jaGames;
    for (int i = 0; i < gameList.size(); ++ i)
    {
        jaGames.insert(i,gameList[i]);
    }
    jO.insert(tr("games"),jaGames);
    //document
    QJsonDocument jD(jO);
    QDir dir(_savePath);
    if (! dir.exists())
    {
        dir.mkpath(".");
    }
    QFile targetFile(dir.absoluteFilePath(_saveName));
    if (! targetFile.open(QFile::WriteOnly | QFile::Text) )
    {
        qDebug() << "save file open failed!";
    }
    targetFile.write(jD.toJson());
    targetFile.close();

}
