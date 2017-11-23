#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>
#include <algorithm>

namespace
{
    const QString ChildImageProvider = "image://childimageprovider/";
    const QString DefaultPhoto = ":/images/face.jpg";
}

ChildrenListModel::ChildrenListModel(QObject *parent)
    :QAbstractListModel(parent),
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
    iDatabase.AddChild(child);
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
        if(child.Name() == name)
        {
            image = child.Image();
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
            data = QVariant(child.Name());
            break;
        case GroupRole:
            data = QVariant(child.Group());
            break;
        case AgeRole:
            data = QVariant(QString::number(ChildUtils::Age(child), 'g', 3));
            break;
        case ImageRole:
            data = QVariant(ChildImageProvider + child.Name());
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
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::CompareName);
        break;
    case AgeRole:
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::CompareAge);
        break;
    case GroupRole:
        std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::CompareGroup);
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

    iChildren = iDatabase.GetAllChildren();

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
