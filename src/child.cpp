#include "child.h"
#include <sstream>
#include <iomanip>
#include <QString>
#include <QDate>

Child::Child(QString const& name, QString const& dateOfBirth, QString const& group, QImage const& image)
    :iName(name), iDateOfBirth(dateOfBirth), iGroup(group), iImage(image)
{
}

QString Child::Name() const
{
    return iName;
}

QString Child::DateOfBirth() const
{
    return iDateOfBirth;
}

QString Child::Group() const
{
    return iGroup;
}

QImage Child::Image() const
{
    return iImage;
}


bool ChildUtils::CompareName(Child const& child, Child const& other)
{
    return QString::localeAwareCompare(child.Name(), other.Name()) < 0;
}

bool ChildUtils::CompareAge(Child const& child, Child const& other)
{
    return ChildUtils::Age(child) < ChildUtils::Age(other);
}

bool ChildUtils::CompareGroup(Child const& child, Child const& other)
{
    return QString::localeAwareCompare(child.Group(), other.Group()) < 0;
}

double ChildUtils::Age(Child const& child)
{
    auto dob = QDate::fromString(child.DateOfBirth(), "dd/MM/yyyy");
    auto today = QDate::currentDate();

    auto days = dob.daysTo(today);

    return days / 365.0;
}
