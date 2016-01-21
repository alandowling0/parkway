#include "child.h"
#include <sstream>
#include <iomanip>
#include <QString>
#include <QDate>

Child::Child(const QString &name, const QString &image, const QString &group, const QString &dateOfBirth)
    :iName(name), iImage(image), iGroup(group), iDateOfBirth(dateOfBirth)
{
}

QString Child::Name() const
{
    return iName;
}

QString Child::Image() const
{
    return iImage;
}

QString Child::Group() const
{
    return iGroup;
}

QString Child::Age() const
{
    auto dob = QDate::fromString(iDateOfBirth, "dd/MM/yyyy");
    auto today = QDate::currentDate();

    //seems wrong way around but it works
    auto days = dob.daysTo(today);

    auto years = days / 365.0;

    std::stringstream ss;
    ss << std::setprecision(3) << years;

    return QString(ss.str().c_str());
}

bool ChildUtils::CompareName(Child const& child, Child const& other)
{
    return child.Name() < other.Name();
}

bool ChildUtils::CompareAge(Child const& child, Child const& other)
{
    return child.Age() < other.Age();
}

bool ChildUtils::CompareGroup(Child const& child, Child const& other)
{
    return child.Group() < other.Group();
}

