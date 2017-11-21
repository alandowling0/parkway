#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>
#include <algorithm>

ChildrenListModel::ChildrenListModel(QObject *parent)
    :QAbstractListModel(parent), iSortRole(NameRole), iSortOrder(Qt::AscendingOrder)
{
   auto children = iDatabase.GetAllChildren();

   for(auto const& child : children)
   {
       addChild(child);
   }

   std::stable_sort(iChildren.begin(), iChildren.end(), ChildUtils::CompareName);
}

void ChildrenListModel::addChild(QString const& name, QString const& dateOfBirth, QString const& group)
{
    auto child = Child(name, dateOfBirth, group);
    addChild(child);
    iDatabase.AddChild(child);
}

QString ChildrenListModel::getChildName(int index) const
{
    auto modelIndex =  QAbstractItemModel::createIndex(index, 0);
    QVariant name = data(modelIndex, NameRole);

    return name.toString();
}

void ChildrenListModel::sortByName()
{
    sort(NameRole);
}

void ChildrenListModel::sortByAge()
{
    sort(AgeRole);
}

void ChildrenListModel::sortByGroup()
{
    sort(GroupRole);
}

QHash<int, QByteArray> ChildrenListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
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
        case GroupRole:
            data = QVariant(child.Group());
            break;
        case AgeRole:
            data = QVariant(ChildUtils::Age(child));
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

void ChildrenListModel::sort(ChildRole sortRole)
{
    layoutAboutToBeChanged();

    switch(sortRole)
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

    //Ordinarily sort ascending
    //if already sorted ascending by this column then sort descending
    //hence the sort order will toggle
    if(iSortRole == sortRole && iSortOrder == Qt::AscendingOrder)
    {
        std::reverse(iChildren.begin(), iChildren.end());
        iSortOrder = Qt::DescendingOrder;
    }
    else
    {
        iSortOrder = Qt::AscendingOrder;
    }

    iSortRole = sortRole;

    layoutChanged();
}

void ChildrenListModel::addChild(Child const& child)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iChildren.push_back(child);
    endInsertRows();
}
