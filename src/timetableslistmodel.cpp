#include "timetableslistmodel.h"
#include <cassert>


TimetablesListModel::TimetablesListModel(Database& database, QObject *parent) :
    QAbstractListModel(parent),
    iDatabase(database)
{
    connect(&iDatabase, &Database::updated, this, &TimetablesListModel::onDatabaseUpdated);
}

void TimetablesListModel::setChild(QString const& childName)
{
    if(childName != iChildName)
    {
        iChildName = childName;

        refresh();
    }
}

QHash<int, QByteArray> TimetablesListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ChildRole] = "child";
    roles[TermRole] = "term";
    roles[MondayRole] = "mon";
    roles[TuesdayRole] = "tue";
    roles[WednesdayRole] = "wed";
    roles[ThursdayRole] = "thu";
    roles[FridayRole] = "fri";

    return roles;
}

QVariant TimetablesListModel::data(const QModelIndex & index, int role) const
{
    QVariant data;

    size_t row = index.row();

    if(row < iTimetables.size())
    {
        auto timetable = iTimetables[row];

        switch (role)
        {
        case ChildRole:
            data = QVariant(timetable.child());
            break;
        case TermRole:
            data = QVariant(timetable.term());
            break;
        case MondayRole:
            data = QVariant(timetable.mon());
            break;
        case TuesdayRole:
            data = QVariant(timetable.tue());
            break;
        case WednesdayRole:
            data = QVariant(timetable.wed());
            break;
        case ThursdayRole:
            data = QVariant(timetable.thu());
            break;
        case FridayRole:
            data = QVariant(timetable.fri());
            break;
        default:
            assert(false);
        }
    }

    return data;
}

int TimetablesListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return iTimetables.size();
}

void TimetablesListModel::onDatabaseUpdated()
{
    refresh();
}

void TimetablesListModel::refresh()
{
    beginResetModel();

    iTimetables.clear();

    if(!iChildName.isEmpty())
    {
        iTimetables = iDatabase.timetables(iChildName);
    }

    endResetModel();
}
