import QtQuick 2.0

Item {
    id: root

    ChildrenList {
        id: childrenList

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.6

        Component.onCompleted: parentsOfChildListModel.setChildFilter(selectedChildName)
        onSelectedChildNameChanged: parentsOfChildListModel.setChildFilter(selectedChildName)
    }

    ParentsList {
        id: parentsOfChild

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: childrenList.right
        anchors.right: parent.right

        parentsModel: parentsOfChildListModel
    }

}
