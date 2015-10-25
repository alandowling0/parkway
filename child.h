#pragma once

#include <QString>

class Child
{
public:
    Child(const QString &name, const QString &image, const QString &group);

    QString Name() const;
    QString Image() const;
    QString Group() const;

private:
    QString iName;
    QString iImage;
    QString iGroup;
};
