import QtQuick 2.5
import QtQuick.Controls 2.0

Item {
    id: root

    property var stackView: StackView.view

    ChildrenList {
        id: childrenList

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.6

        Component.onCompleted: parentsOfChildListModel.setChildFilter(selectedChildName)
        onSelectedChildNameChanged: parentsOfChildListModel.setChildFilter(selectedChildName)

        onAddClicked: {
            root.stackView.push(addOrEditChild)
        }
    }

    ParentsList {
        id: parentsOfChild

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: childrenList.right
        anchors.right: parent.right

        parentsModel: parentsOfChildListModel
    }

    Component {
        id: addOrEditChild

        AddChild{
            onSaved: {
                console.log(name, dob, group, image)

                childrenListModel.addChild(name, dob, group, image)

                root.stackView.pop()
            }
        }
    }

}
