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

    QString child() const;
    QString term() const;
    bool mon() const;
    bool tue() const;
    bool wed() const;
    bool thu() const;
    bool fri() const;

private:
    QString iChild;
    QString iTerm;
    bool iMon;
    bool iTue;
    bool iWed;
    bool iThu;
    bool iFri;
};
