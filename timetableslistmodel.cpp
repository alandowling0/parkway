#include "timetableslistmodel.h"
#include <cassert>


TimetablesListModel::TimetablesListModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

void TimetablesListModel::setChild(QString const& childName)
{
    ClearTimetables();

    auto timetables = iDatabase.GetTimetables(childName.toStdString());

    for(auto const& timetable : timetables)
    {
        AddTimetable(timetable);
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
            data = QVariant(timetable.Child());
            break;
        case TermRole:
            data = QVariant(timetable.Term());
            break;
        case MondayRole:
            data = QVariant(timetable.Mon());
            break;
        case TuesdayRole:
            data = QVariant(timetable.Tue());
            break;
        case WednesdayRole:
            data = QVariant(timetable.Wed());
            break;
        case ThursdayRole:
            data = QVariant(timetable.Thu());
            break;
        case FridayRole:
            data = QVariant(timetable.Fri());
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

void TimetablesListModel::AddTimetable(Timetable const& timetable)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iTimetables.push_back(timetable);
    endInsertRows();
}

void TimetablesListModel::ClearTimetables()
{
    if(!iTimetables.empty())
    {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);
        iTimetables.clear();
        endRemoveRows();
    }
}
