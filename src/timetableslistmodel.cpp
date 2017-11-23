#include "timetableslistmodel.h"
#include <cassert>


TimetablesListModel::TimetablesListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

void TimetablesListModel::setChild(QString const& childName)
{
    clearTimetables();

    auto timetables = iDatabase.timetables(childName);

    for(auto const& timetable : timetables)
    {
        addTimetable(timetable);
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

    auto row = index.row();

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

void TimetablesListModel::addTimetable(Timetable const& timetable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iTimetables.push_back(timetable);
    endInsertRows();
}

void TimetablesListModel::clearTimetables()
{
    if(!iTimetables.empty())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);
        iTimetables.clear();
        endRemoveRows();
    }
}
