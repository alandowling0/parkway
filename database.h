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
    std::vector<std::string> GetAllGroups() const;
    std::vector<Parent> GetParents(std::string const& childName) const;
    std::vector<Timetable> GetTimetables(std::string const& childName) const;
    QByteArray GetImageData(std::string const& childName) const;

    void AddChild(Child const& child);

    static const QString DATABASE_NAME;

private:
     int ChildId(std::string const& childName) const;
     int GroupId(std::string const& groupName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

