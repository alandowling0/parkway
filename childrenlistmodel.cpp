#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>
#include <algorithm>

ChildrenListModel::ChildrenListModel(QObject *parent)
    :QAbstractListModel(parent)
{
   auto children = iDatabase.GetAllChildren();

   for(auto const& child : children)
   {
       AddChild(child);
   }
}

QString ChildrenListModel::getChildName(int index) const
{
    auto modelIndex =  QAbstractItemModel::createIndex(index, 0);
    QVariant name = data(modelIndex, NameRole);

    return name.toString();
}

void ChildrenListModel::sortBy(int column)
{
    sort(Qt::UserRole + column);
}

QHash<int, QByteArray> ChildrenListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ImageRole] = "image";
    roles[GroupRole] = "group";
    roles[AgeRole] = "age";
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
        case AgeRole:
            data = QVariant(child.Age());
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

void ChildrenListModel::sort(int column, Qt::SortOrder order)
{
    layoutAboutToBeChanged();

    switch(column)
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

    if(order == Qt::SortOrder::DescendingOrder)
    {
        std::reverse(iChildren.begin(), iChildren.end());
    }

    layoutChanged();
}

void ChildrenListModel::AddChild(Child const& child)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iChildren.push_back(child);
    endInsertRows();
}
