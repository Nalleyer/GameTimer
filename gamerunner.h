#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include <QObject>
#include <QProcess>
#include <QString>

class GameRunner : public QObject
{
    Q_OBJECT
public:
    explicit GameRunner(QObject *parent = 0);
    QProcess * runGame(QString gameFullPath);

signals:
    void gameExited(int);
private slots:
    void onGameExited(int exitID);

public slots:
};

#endif // GAMERUNNER_H
