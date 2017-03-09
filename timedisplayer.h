#ifndef TIMEDISPLAYER_H
#define TIMEDISPLAYER_H

#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QString>

class TimeDisplayer : public QLCDNumber
{
    Q_OBJECT

public:
    explicit TimeDisplayer(const QTime & time, QWidget *parent = 0);
    const QTime & getTime() const;
    bool isTiming() const;
    void setTime(const QTime & time) {* _nowTime = time; refresh();}
    void refresh();
    void checkTimeLimit();
private:
    QTime * _nowTime;
    QTimer * _timer;
    bool _isTimingOn;
signals:
    void timeUsedOut();
private slots:
    void updateTime();
public slots:
    void start();
    void stop();
};

#endif // TIMEDISPLAYER_H
