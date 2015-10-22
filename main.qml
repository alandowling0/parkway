import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 600

    color: "lightgray"    

    ChildrenList
    {
        id: children
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width / 2
        anchors.margins: 10
    }

    ParentsList
    {
        id: parents
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: children.right
        height: parent.height / 5
        anchors.margins: 10
    }

    AttendedDays
    {
        id: attendedDays
        anchors.top: parents.bottom
        anchors.right: parent.right
        anchors.left: children.right
        anchors.margins: 10
        height: parent.height / 5
    }
}
