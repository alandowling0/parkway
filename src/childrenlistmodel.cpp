#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>
#include <algorithm>

namespace
{
    const QString ChildImageProvider = "image://childimageprovider/";
    const QString DefaultPhoto = ":/images/face.jpg";
}

ChildrenListModel::ChildrenListModel(Database& database, QObject *parent) :
    QAbstractListModel(parent),
    iDatabase(database),
    iSortRole(NameRole),
    iSortOrder(Qt::AscendingOrder)
{
    refresh();

    connect(&iDatabase, &Database::updated, this, &ChildrenListModel::onDatabaseUpdated);
}

void ChildrenListModel::addChild(QString const& name, QString const& dateOfBirth, QString const& group, QUrl const& imageFilePath)
{
    auto image = imageFilePath.isLocalFile() ? QImage(imageFilePath.toLocalFile()) : QImage(DefaultPhoto);
    auto child = Child(name, dateOfBirth, group, image);
    iDatabase.addChild(child);
}

void ChildrenListModel::removeChild(QString const& name)
{
    iDatabase.removeChild(name);
}

void ChildrenListModel::sortByName()
{    
    if(iSortRole != NameRole)
    {
        iSortRole = NameRole;
    }
    else
    {
        toggleSortOrder();
    }

    sort();
}

void ChildrenListModel::sortByAge()
{
    if(iSortRole != AgeRole)
    {
        iSortRole = AgeRole;
    }
    else
    {
        toggleSortOrder();
    }

    sort();
}

void ChildrenListModel::sortByGroup()
{
    if(iSortRole != GroupRole)
    {
        iSortRole = GroupRole;
    }
    else
    {
        toggleSortOrder();
    }

    sort();
}

QImage ChildrenListModel::getImage(QString const& name) const
{
    QImage image;

    for(auto const& child : iChildren)
    {
        if(child.name() == name)
        {
            image = child.image();
			break;
        }
    }

    return image;
}

QHash<int, QByteArray> ChildrenListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[GroupRole] = "group";
    roles[AgeRole] = "age";
    roles[ImageRole] = "imageUrl";
    return roles;
}

QVariant ChildrenListModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    size_t row = index.row();

    if(row < iChildren.size())
    {
        auto child = iChildren.at(row);

        switch (role)
        {
        case NameRole:
            data = QVariant(child.name());
            break;
        case GroupRole:
            data = QVariant(child.group());
            break;
        case AgeRole:
            data = QVariant(QString::number(ChildUtils::age(child), 'g', 3));
            break;
        case ImageRole:
            data = QVariant(ChildImageProvider + child.name());
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

void ChildrenListModel::onDatabaseUpdated()
{
    refresh();
}

void ChildrenListModel::sort()
{
    layoutAboutToBeChanged();

    switch(iSortRole)
    {
    case NameRole:
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::compareName);
        break;
    case AgeRole:
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::compareAge);
        break;
    case GroupRole:
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::compareGroup);
        break;
    default:
        assert(false);
    }

    if(iSortOrder == Qt::DescendingOrder)
    {
        std::reverse(iChildren.begin(), iChildren.end());
    }

    layoutChanged();
}

void ChildrenListModel::refresh()
{
    beginResetModel();

    iChildren = iDatabase.children();

    sort();

    endResetModel();
}

void ChildrenListModel::toggleSortOrder()
{
    if(iSortOrder == Qt::AscendingOrder)
    {
        iSortOrder = Qt::DescendingOrder;
    }
    else
    {
        iSortOrder = Qt::AscendingOrder;
    }
}
