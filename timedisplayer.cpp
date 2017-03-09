#include "timedisplayer.h"
#include <QDebug>

TimeDisplayer::TimeDisplayer(const QTime &time, QWidget *parent) :
    QLCDNumber(parent)
{
    setDigitCount(8);
    _nowTime = new QTime;
    * _nowTime = time;

    _timer = new QTimer;
    _timer->setInterval(100);
    refresh();

    connect(_timer,SIGNAL(timeout()),
            this,SLOT(updateTime()));
}

void TimeDisplayer::refresh()
{
    display(_nowTime->toString());
}

const QTime & TimeDisplayer::getTime() const
{
    return * _nowTime;
}

bool TimeDisplayer::isTiming() const
{
    return _isTimingOn;
}

void TimeDisplayer::checkTimeLimit()
{
    if (* _nowTime == QTime::fromString("00:00:00"))
    {
        emit timeUsedOut();
    }
}

void TimeDisplayer::updateTime()
{
    * _nowTime = _nowTime -> addMSecs(-100);
    this->display(_nowTime->toString());
    checkTimeLimit();
}

void TimeDisplayer::start()
{
    _timer->start();
    _isTimingOn = true;
}

void TimeDisplayer::stop()
{
    _timer->stop();
    _isTimingOn = false;
}
