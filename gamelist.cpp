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
}


void GameList::listItemDoubleClicked(QListWidgetItem *pItem)
{
    QFileInfo * fI = _itemFileMap[pItem];
    qDebug() << "double clicked";
    //emit
    emit toRumGame(fI->filePath());
}
