#include "parentslistmodel.h"
#include <QDebug>
#include <cassert>


ParentsListModel::ParentsListModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void ParentsListModel::setChild(QString const& childName)
{
    clearParents();

    auto parents = iDatabase.parents(childName);

    for(auto const& parent : parents)
    {
        addParent(parent);
    }
}

QHash<int, QByteArray> ParentsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[EmailRole] = "email";
    roles[PhoneRole] = "phone";
    return roles;
}

QVariant ParentsListModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    auto row = index.row();

    if(row < iParents.size())
    {
        auto parent = iParents.at(row);

        switch (role)
        {
        case NameRole:
            data = QVariant(parent.name());
            break;
        case EmailRole:
            data = QVariant(parent.email());
            break;
        case PhoneRole:
            data = QVariant(parent.phone());
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int ParentsListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return iParents.size();
}

void ParentsListModel::addParent(Parent const& parent)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iParents.push_back(parent);
    endInsertRows();
}

void ParentsListModel::clearParents()
{
    if(!iParents.empty())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);
        iParents.clear();
        endRemoveRows();
    }
}
