import QtQuick 2.5
import QtQuick.Controls 2.0

Item {
    id: root

    property var stackView: StackView.view

    ChildrenList {
        id: childrenList

        anchors.top: parent.top
        anchors.bottom: buttonArea.top
        anchors.left: parent.left
        anchors.margins: 10
        width: parent.width * 0.7

        Component.onCompleted: parentsOfChildListModel.setChildFilter(selectedChildName)
        onSelectedChildNameChanged: parentsOfChildListModel.setChildFilter(selectedChildName)
    }

    ParentsOfChild {
        id: parentsOfChild

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: childrenList.right
        anchors.right: parent.right
        anchors.margins: 10

        parentsModel: parentsOfChildListModel
    }

    Item {
        id: buttonArea

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: childrenList.right
        height: childrenList.rowHeight

        Button {
            anchors.centerIn: parent

            height: parent.height * 0.75
            width: height * 3

            text: "Add Child"

            onClicked: root.stackView.push(addOrEditChild)
        }
    }

    Component {
        id: addOrEditChild

        AddChild{
            onSaved: {
                console.log(name, dob, group, image, parents)

                childrenListModel.addChild(name, dob, group, image, parents)

                root.stackView.pop()
            }

            onCanceled: root.stackView.pop()
        }
    }
}
