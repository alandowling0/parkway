#pragma once

#include <QAbstractListModel>
#include <vector>
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

    TimetablesListModel(Database& database, QObject *parent = 0);

    Q_INVOKABLE void setChild(QString const& childName);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

public slots:
    void onDatabaseUpdated();

private:
    void refresh();

    std::vector<Timetable> iTimetables;
    QString iChildName;
    Database& iDatabase;
};
