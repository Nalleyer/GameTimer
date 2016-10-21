#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMap>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QVector>

class GameList : public QListWidget
{
    Q_OBJECT
public:
    explicit GameList(QListWidget *parent = 0);
    //add a new game
    void addGame(QString filePath);
    //get list of game full path
    QVector<QString> getGameList() const;
    //build items from list of game full path
    void buildFromPathList(const QVector<QString> & pathList);
    //
    void runSelectedGame();
    void removeSelectedGame();
private:
    QMap<QListWidgetItem *, QFileInfo *>  _itemFileMap;
    void runGame(QListWidgetItem * pItem);

signals:
    void toRunGame(QString filePath);

public slots:
    void listItemDoubleClicked(QListWidgetItem * pItem);
};

#endif // GAMELIST_H
