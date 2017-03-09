#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMap>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QVector>
#include "gamerunner.h"

class GameList : public QListWidget
{
    Q_OBJECT
public:
    explicit GameList(const QVector<QString> & pathList, QWidget *parent = 0);
    void addGame(QString filePath);
    /* [ full path ] */
    QVector<QString> getGameList() const;
    void quitAllGames();
private:
    int _numRunningGames;
    GameRunner * _gameRunner;
    QMap<QListWidgetItem *, QFileInfo *>  _itemFileMap;
    void runGame(QListWidgetItem * pItem);
    //build items from list of game full path
    void buildFromPathList(const QVector<QString> & pathList);
    /* all process stared from GameTImer */
    QVector<QProcess *> _runningGames;

private slots:
    void onGameExit(int exitID);

signals:
    void allGameExited();
    void firstGameStarted();
public slots:
    void runSelectedGame();
    void removeSelectedGame();
};

#endif // GAMELIST_H
