#pragma once

#include <QString>
#include <QtSql>
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

private:
     void Open();
     void Close();

     int ChildId(std::string const& childName) const;

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

