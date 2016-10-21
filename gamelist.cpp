#include "gamelist.h"

#include <QDebug>

GameList::GameList(QListWidget *parent) : QListWidget(parent)
{
    setFixedWidth(180);
    connect(
                this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this,SLOT(listItemDoubleClicked(QListWidgetItem*))
                );
}

void GameList::addGame(QString filePath)
{
    qDebug() << filePath;
    //
    QFileInfo * pFi = new QFileInfo(filePath);
    QListWidgetItem * newItem = new QListWidgetItem(pFi->fileName());
    addItem(newItem);
    _itemFileMap[newItem] = pFi;
    //set selected
    newItem->setSelected(true);
}

void GameList::runGame(QListWidgetItem *pItem)
{
    QFileInfo * fI = _itemFileMap.value(pItem);
    //emit
    emit toRunGame(fI->filePath());
}

void GameList::runSelectedGame()
{
    foreach( const auto & i , this->selectedItems() )
    {
        runGame(i);
    }
}

void GameList::removeSelectedGame()
{
    foreach(auto & i, this->selectedItems())
    {
        auto itToErase = _itemFileMap.find(i);
        _itemFileMap.erase(itToErase);
        this->removeItemWidget(i);
        delete i;
    }
}

void GameList::listItemDoubleClicked(QListWidgetItem *pItem)
{
    qDebug() << "double clicked";
    runGame(pItem);
}

void GameList::buildFromPathList(const QVector<QString> &pathList)
{
    qDebug() << "building game List: ";
    for (int i = 0; i < pathList.size(); ++ i)
    {
        addGame(pathList[i]);
    }
    //set selected item
    if (pathList.size() != 0)
    {
        this->item(0)->setSelected(true);
    }
}

QVector<QString> GameList::getGameList() const
{
    QVector<QString> newList;
    QMapIterator<QListWidgetItem *, QFileInfo *> i(_itemFileMap);
    while (i.hasNext())
    {
        i.next();
        newList.append(i.value()->filePath());
    }
    return newList;
}
