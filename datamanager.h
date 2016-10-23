#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QString>
#include <QVector>
//#include <QJsonDocument>

class DataManager : public QObject
{
    Q_OBJECT
private:
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
    bool _dateChanged;
    /*	file path
     */
    /*	read file to json
     */
    bool readFileOnStart();
    // call when first use this app
    void defaultSetting();
    //a json
    QJsonObject * _saveJson;
public:
    explicit DataManager(QObject *parent = 0);
    QString getLeftTime() const ;
    QVector<QString> getGameFullPathList() const;
    //set totalTime
    void setTotalTime(QString time);
    /* save date of today, leftTime, list of Game; filename and path is hardCoded
     * today:		for reset leftTime
     * leftTime: 	for using in same day
     * list of Game:save for anytime
     * total time:	..
     */
    bool dateChanged() {return _dateChanged;}
public slots:
    void runGame(QString filePath);
    void onGameExited(int ExitID);
};

#endif // DATAMANAGER_H
