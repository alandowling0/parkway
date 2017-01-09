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

private:
     int ChildId(std::string const& childName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

