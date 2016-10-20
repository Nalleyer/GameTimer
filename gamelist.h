#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMap>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileInfo>

class GameList : public QListWidget
{
    Q_OBJECT
public:
    explicit GameList(QListWidget *parent = 0);
    //add a new game
    void addGame(QString filePath);

private:
    QMap<QListWidgetItem *, QFileInfo *>  _itemFileMap;

signals:
    void toRumGame(QString filePath);

public slots:
    void listItemDoubleClicked(QListWidgetItem * pItem);
};

#endif // GAMELIST_H
