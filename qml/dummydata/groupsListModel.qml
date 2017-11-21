import QtQuick 2.0

ListModel
{
    function setChild(childName)
    {

    }

    ListElement
    {
        child: "Name1"
        term: "Term name"
        mon: true
        tue: false
        wed: true
        thu: false
        fri: true
    }

    ListElement
    {
        child: "Name2"
        term: "Term name"
        mon: true
        tue: true
        wed: true
        thu: true
        fri: true
    }
}

