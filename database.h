#pragma once

#include <QString>
#include <QtSql>
#include "child.h"
#include "parent.h"

class Database
{
public:
    Database();
    ~Database();

    std::vector<Child> GetAllChildren();
    std::vector<Parent> GetAllParents();

private:
     void Open();
     void Close();

private:
     QSqlDatabase iSqliteDatabase;
     QString iConnectionName;
};

