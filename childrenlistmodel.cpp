#include "childrenlistmodel.h"
#include <QDebug>
#include <cassert>

Child::Child(const QString &name, const QString &image, const QString &group)
    :iName(name), iImage(image), iGroup(group)
{
}

QString Child::Name() const
{
    return iName;
}

QString Child::Image() const
{
    return iImage;
}

QString Child::Group() const
{
    return iGroup;
}

/////////////////////////////////////////////////////////////////////////////

ChildrenListModel::ChildrenListModel(QObject *parent)
    :QAbstractListModel(parent)
{
    iSqliteDatabase = QSqlDatabase::addDatabase("QSQLITE");
    iSqliteDatabase.setDatabaseName("..\\parkway\\database\\parkway.db");

    bool open = iSqliteDatabase.open();
    if(!open)
    {
       qDebug() << iSqliteDatabase.lastError().text();
       assert(open);
    }

    QSqlQuery pragma("PRAGMA foreign_keys = ON;");
    if(!pragma.exec())
        qDebug() << pragma.lastError().text();

    QSqlQuery query;

    query.prepare("SELECT Children.name, Children.image, Groups.name "
                  "FROM Children "
                  "INNER JOIN Groups "
                  "ON Children.\"group\"=Groups.id");

    if(!query.exec())
        qDebug() << query.lastError().text();

    if(query.first())
    {
        do
        {
            auto name = query.value(0).toString();
            auto image = query.value(1).toString();
            auto group = query.value(2).toString();

            AddChild(Child(name, image, group));

        }while(query.next());
    }
}

ChildrenListModel::~ChildrenListModel()
{
    iSqliteDatabase.close();
}

void ChildrenListModel::doSomething()
{
    qDebug() << "doSomething";
    AddChild(Child("Alan", "child.jpg", "Giraffes"));
}

QHash<int, QByteArray> ChildrenListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ImageRole] = "image";
    roles[GroupRole] = "group";
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

void ChildrenListModel::AddChild(Child const& child)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    iChildren.push_back(child);
    endInsertRows();
}
