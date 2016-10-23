#include "gamerunner.h"

#include <QFile>
#include <QMessageBox>

GameRunner::GameRunner(QObject *parent) : QObject(parent)
{

}

bool pathValid(QString gameFullPath)
{
    QFile f(gameFullPath);
    return f.exists();
}


QProcess * GameRunner::runGame(QString gameFullPath)
{
    if (pathValid(gameFullPath))
    {
        QProcess * newProc = new QProcess;
        newProc->start(gameFullPath);
        connect(newProc,SIGNAL(finished(int)),
                this,SLOT(onGameExited(int)));
        connect(newProc,SIGNAL(finished(int)),
                newProc,SLOT(deleteLater()));
        return newProc;
    }
    else
    {
        QMessageBox::information(nullptr,"",tr("file not exists!"));
        return nullptr;
    }
}

void GameRunner::onGameExited(int exitID)
{
    emit gameExited(exitID);
}

