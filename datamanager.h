#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QProcess>
#include <QVector>

class DataManager : public QObject
{
    Q_OBJECT
private:
    QTime * _leftTime;
    QTimer * _timer;
    bool _timingOn;
    //read lefttime from file
    void setLeftTime();
    int _gameRunningCount;
    QVector<QProcess*> _runningGames;
    void removeEndedGames();
public:
    explicit DataManager(QObject *parent = 0);
    QString getLeftTime();
    //start timing
    void startTiming();
    //stop timing
    void stopTiming();
signals:
    void timeChanged(QString time);
public slots:
    void updateLeftTime();
    void runGame(QString filePath);
    void onGameExited(int ExitID);
};

#endif // DATAMANAGER_H
