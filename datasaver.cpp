#include "datasaver.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>

DataSaver::DataSaver(QObject *parent)
    : QObject(parent),
      _savePath("./data"),
      _saveName(".save")
{
}

QJsonArray buildGamesJsonArray(const QVector<QString> gameList)
{
    QJsonArray jAGames;
    for (int i = 0; i < gameList.size(); ++ i)
    {
        jAGames.insert(i,gameList[i]);
    }
    return jAGames;
}

QJsonObject buildSavingJson(const SavingData & aData)
{
    QJsonObject jO;
    jO.insert(QObject::tr("date"),aData.getDate().toString());
    jO.insert(QObject::tr("leftTime"),aData.getLeftTime().toString());
    jO.insert(QObject::tr("totalTimeChanged"),aData.getTotalTimeChanged());
    jO.insert(QObject::tr("totalTime"),aData.getTotalTime().toString());
    jO.insert(QObject::tr("games"),buildGamesJsonArray(aData.getGameList()));
    return jO;
}

QDir buildSavingDir(QString path)
{
    QDir dir(path);
    if (! dir.exists())
    {
        dir.mkpath(".");
    }
    return dir;
}

void DataSaver::save(const SavingData &aData)
{
    QFile targetFile(buildSavingDir(_savePath).absoluteFilePath(_saveName));
    targetFile.open(QFile::WriteOnly | QFile::Text);
    QJsonDocument jD(buildSavingJson(aData));
    targetFile.write(jD.toJson());
    targetFile.close();
}

/*for now, just check file exists
 * check file format in the future
 */
bool DataSaver::savingFileValid()
{
    QDir dir(_savePath);
    if (! dir.exists())
        return false;
    if (! QFileInfo::exists(dir.absoluteFilePath(_saveName)))
        return false;
    return true;
}

QVector<QString> getGameFullPathList(const QJsonObject & jOb)
{
    QVector<QString> gameList;
    QJsonArray jA = jOb.value(QObject::tr("games")).toArray();
    foreach (const QJsonValue & value, jA)
    {
        gameList.append(value.toString());
    }
    return gameList;
}


SavingData buildFromJson(const QJsonObject & jOb)
{
    auto date = QDate::fromString(jOb.value(QObject::tr("date")).toString());
    auto totalTime = QTime::fromString(jOb.value(QObject::tr("totalTime")).toString());
    auto leftTime = QTime::fromString(jOb.value(QObject::tr("leftTime")).toString());
    auto games = getGameFullPathList(jOb);
    auto totalTimeChanged = jOb.value(QObject::tr("totalTimeChanged")).toBool();
    return SavingData(date,totalTime,leftTime,games,totalTimeChanged);
}

SavingData DataSaver::load()
{
    QDir dir(_savePath);
    QFile file(dir.absoluteFilePath(_saveName));
    file.open(QFile::ReadOnly | QFile::Text);
    QJsonParseError jPE;
    QJsonDocument jD = QJsonDocument::fromJson(file.readAll(),&jPE);
    file.close();
    auto jOb = jD.object();
    return buildFromJson(jOb);
}
