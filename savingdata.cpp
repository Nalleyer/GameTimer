#include "savingdata.h"

SavingData::SavingData(QDate date, QTime totalTime, QTime leftTime, QVector<QString> gameList, bool totalTimeChanged)
    :
    _date(date),
    _totalTime(totalTime),
    _leftTime(leftTime),
    _gameList(gameList),
    _totalTimeChanged(totalTimeChanged)
{
}

SavingData::SavingData(const SavingData &another)
    :
      _date(another._date),
      _totalTime(another._totalTime),
      _leftTime(another._leftTime),
      _gameList(another._gameList),
      _totalTimeChanged(another._totalTimeChanged)
{
}

SavingData & SavingData::operator =(const SavingData & another)
{
    if (this == & another)
        return *this;
    _date = another.getDate();
    _totalTime = another.getTotalTime();
    _leftTime = another.getLeftTime();
    _gameList = another.getGameList();
    _totalTimeChanged = another.getTotalTimeChanged();
    return *this;
}

SavingData::SavingData()
{
}
