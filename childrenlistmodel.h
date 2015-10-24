#pragma once

#include <QAbstractListModel>
#include <QList>

class Child
{
public:
    Child(const QString &name, const QString &image, const QString &group);

    QString Name() const;
    QString Image() const;
    QString Group() const;

private:
    QString iName;
    QString iImage;
    QString iGroup;
};

class ChildrenListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ChildRoles {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        GroupRole
    };

    Q_INVOKABLE void doSomething();

    ChildrenListModel(QObject *parent = 0);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    void AddChild(Child const& child);

private:
    QList<Child> iChildren;
};
