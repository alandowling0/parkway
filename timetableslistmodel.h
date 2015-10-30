#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtSql>
#include "timetable.h"
#include "database.h"


class TimetablesListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum TimetableRoles {
        ChildRole = Qt::UserRole + 1,
        TermRole,
        MondayRole,
        TuesdayRole,
        WednesdayRole,
        ThursdayRole,
        FridayRole
    };

    Q_INVOKABLE void setChild(QString const& childName);

    TimetablesListModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
    void AddTimetable(Timetable const& timetable);
    void ClearTimetables();

private:
    QList<Timetable> iTimetables;

    Database iDatabase;
};
