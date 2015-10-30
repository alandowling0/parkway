#pragma once

#include <QString>

class Timetable
{
public:
    Timetable(const QString &child,
              const QString &term,
              bool monday,
              bool tuesday,
              bool wednesday,
              bool thursday,
              bool friday);

    QString Child() const;
    QString Term() const;
    bool Mon() const;
    bool Tue() const;
    bool Wed() const;
    bool Thu() const;
    bool Fri() const;

private:
    QString iChild;
    QString iTerm;
    bool iMon;
    bool iTue;
    bool iWed;
    bool iThu;
    bool iFri;
};
