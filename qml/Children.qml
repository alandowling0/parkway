import QtQuick 2.0

Item {
    id: root

    ChildrenList {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.6
    }

}
