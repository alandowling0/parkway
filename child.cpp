#include "child.h"
#include <QString>

Child::Child(const QString &name, const QString &image, const QString &group)
    :iName(name), iImage(image), iGroup(group)
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

