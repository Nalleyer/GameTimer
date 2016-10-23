#ifndef DATASAVER_H
#define DATASAVER_H

#include <QObject>
#include <QString>

#include "savingdata.h"

class DataSaver : public QObject
{
    Q_OBJECT
private:
    QString _savePath;
    QString _saveName;
public:
    explicit DataSaver(QObject *parent = 0);

signals:

public:
    void save(const SavingData & aData);
    SavingData load();
    bool savingFileValid();

    void setSavePath(QString path){_savePath = path;}
    void setSaveName(QString name){_saveName = name;}
};

#endif // DATASAVER_H
