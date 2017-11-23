#include "parent.h"

#include <QString>

Parent::Parent(const QString &name, const QString &email, const QString &phone)
    :iName(name), iEmail(email), iPhone(phone)
{
}

QString Parent::name() const
{
    return iName;
}

QString Parent::email() const
{
    return iEmail;
}

QString Parent::phone() const
{
    return iPhone;
}

