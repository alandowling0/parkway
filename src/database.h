#pragma once

#include <QString>
#include <QtSql>
#include <QByteArray>
#include "child.h"
#include "parent.h"
#include "timetable.h"

class Database
{
public:
    Database();
    ~Database();

    std::vector<Child> GetAllChildren() const;
    std::vector<Parent> GetAllParents() const;
    std::vector<QString> GetAllGroups() const;
    std::vector<Parent> GetParents(QString const& childName) const;
    std::vector<Timetable> GetTimetables(QString const& childName) const;
    QByteArray GetImageData(QString const& childName) const;

    void AddChild(Child const& child);

    static const QString DATABASE_NAME;

private:
     int ChildId(QString const& childName) const;
     int GroupId(QString const& groupName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

