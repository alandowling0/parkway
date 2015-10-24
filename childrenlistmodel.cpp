#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>

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

/////////////////////////////////////////////////////////////////////////////

ChildrenListModel::ChildrenListModel(QObject *parent)
    :QAbstractListModel(parent)
{
    AddChild(Child("Sara", "child.jpg", "Pandas"));
    AddChild(Child("Robert", "child.jpg", "Koalas"));
}

void ChildrenListModel::doSomething()
{
    qDebug() << "doSomething";
    AddChild(Child("Alan", "child.jpg", "Giraffes"));
}

QHash<int, QByteArray> ChildrenListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ImageRole] = "image";
    roles[GroupRole] = "group";
    return roles;
}

QVariant ChildrenListModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    auto row = index.row();

    if(row < iChildren.size())
    {
        auto child = iChildren.at(row);

        switch (role)
        {
        case NameRole:
            data = QVariant(child.Name());
            break;
        case ImageRole:
            data = QVariant(child.Image());
            break;
        case GroupRole:
            data = QVariant(child.Group());
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int ChildrenListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return iChildren.size();
}

void ChildrenListModel::AddChild(Child const& child)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iChildren.push_back(child);
    endInsertRows();
}
