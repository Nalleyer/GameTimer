#ifndef SAVINGDATA_H
#define SAVINGDATA_H

#include <QDate>
#include <QTime>
#include <QString>
#include <QVector>

class SavingData
{
private:
    QDate _date;
    QTime _totalTime;
    QTime _leftTime;
    QVector<QString> _gameList;
    bool _totalTimeChanged;
public:
    SavingData();
    SavingData(QDate date, QTime totalTime, QTime leftTime,QVector<QString> gameList, bool totalTimeChanged);
    SavingData(const SavingData & another);

    SavingData & operator =(const SavingData & another);

    const QDate & getDate() const {return _date;}
    const QTime & getTotalTime() const {return _totalTime;}
    const QTime & getLeftTime() const {return _leftTime;}
    const QVector<QString> & getGameList() const {return _gameList;}
    bool getTotalTimeChanged() const {return _totalTimeChanged;}

    void setDate(const QDate & date) {_date = date;}
    void setLeftTime(const QTime & leftTIme) {_leftTime = leftTIme;}
    void setTotalTime(const QTime & totalTIme) {_totalTime = totalTIme;}
    void addToGameList(QString gameFullPath){_gameList.append(gameFullPath);}
    void setTotalTimeChanged(bool totalTimeChanged){_totalTimeChanged = totalTimeChanged;}
};

#endif // SAVINGDATA_H
