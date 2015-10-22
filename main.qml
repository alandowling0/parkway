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
        height: parent.height / 4
        anchors.margins: 10
    }
}
