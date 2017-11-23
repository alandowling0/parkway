#include "parentslistmodel.h"
#include <QDebug>
#include <cassert>


ParentsListModel::ParentsListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(&iDatabase, &Database::updated, this, &ParentsListModel::onDatabaseUpdated);
}

void ParentsListModel::setChild(QString const& childName)
{
    if(childName != iChildName)
    {
        iChildName = childName;

        refresh();
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

    size_t row = index.row();

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

void ParentsListModel::onDatabaseUpdated()
{
    refresh();
}

void ParentsListModel::refresh()
{
    beginResetModel();

    iParents.clear();

    if(!iChildName.isEmpty())
    {
        iParents = iDatabase.parents(iChildName);
    }

    endResetModel();
}

