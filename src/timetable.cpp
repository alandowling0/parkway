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

QString Timetable::child() const
{
    return iChild;
}

QString Timetable::term() const
{
    return iTerm;
}

bool Timetable::mon() const
{
    return iMon;
}

bool Timetable::tue() const
{
    return iTue;
}

bool Timetable::wed() const
{
    return iWed;
}

bool Timetable::thu() const
{
    return iThu;
}

bool Timetable::fri() const
{
    return iFri;
}
