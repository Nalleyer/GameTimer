#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QString>
#include <QProcess>
#include <QVector>
//#include <QJsonDocument>

class DataManager : public QObject
{
    Q_OBJECT
private:
    QTime * _leftTime;
    QString _totalTime;
    QTimer * _timer;
    bool _timingOn;
    /* set lefttime from json
     */
    void setLeftTimeFromJson();
    int _gameRunningCount;
    QVector<QProcess*> _runningGames;
    void removeEndedGames();
    //set leftTime to totalTime
    void resetLeftTime();
    //now date when constructed
    QDate * _nowDate;

    /*	file path
     */
    const QString _savePath = "./data";
    const QString _saveName = ".save";
    /*	read file to json
     */
    bool readFileOnStart();
    // call when first use this app
    void defaultSetting();
    //a json
    QJsonObject * _saveJson;
    bool _dateChanged;
public:
    explicit DataManager(QObject *parent = 0);
    QString getLeftTime() const ;
    QVector<QString> getGameFullPathList() const;
    //start timing
    void startTiming();
    //stop timing
    void stopTiming();
    //set totalTime
    void setTotalTime(QString time);
    /* save date of today, leftTime, list of Game; filename and path is hardCoded
     * today:		for reset leftTime
     * leftTime: 	for using in same day
     * list of Game:save for anytime
     * total time:	..
     */
    void saveToFile(const QVector<QString> & gameList) const;
    bool dateChanged() {return _dateChanged;}
signals:
    void timeChanged(QString time);
public slots:
    void updateLeftTime();
    void runGame(QString filePath);
    void onGameExited(int ExitID);
};

#endif // DATAMANAGER_H
