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

    std::vector<Child> GetAllChildren();
    std::vector<Parent> GetAllParents();

    std::vector<Parent> GetParents(std::string const& childName);
    std::vector<Timetable> GetTimetables(std::string const& childName);

private:
     void Open();
     void Close();

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

