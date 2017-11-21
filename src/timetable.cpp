#include "timetable.h"

Timetable::Timetable(const QString &child,
          const QString &term,
          bool monday,
          bool tuesday,
          bool wednesday,
          bool thursday,
          bool friday)
    :
      iChild(child),
      iTerm(term),
      iMon(monday),
      iTue(tuesday),
      iWed(wednesday),
      iThu(thursday),
      iFri(friday)
{

}

QString Timetable::Child() const
{
    return iChild;
}

QString Timetable::Term() const
{
    return iTerm;
}

bool Timetable::Mon() const
{
    return iMon;
}

bool Timetable::Tue() const
{
    return iTue;
}

bool Timetable::Wed() const
{
    return iWed;
}

bool Timetable::Thu() const
{
    return iThu;
}

bool Timetable::Fri() const
{
    return iFri;
}
