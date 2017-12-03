import QtQuick 2.5
import QtQuick.Controls 2.0

Item {
    ParentsList {
        id: parentList

        anchors.top: parent.top
        anchors.bottom: buttonArea.top
        anchors.left: parent.left
        width: parent.width * 0.7
    }

    Item {
        id: buttonArea

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parentList.right
        height: parentList.rowHeight

        Button {
            anchors.centerIn: parent

            height: parent.height * 0.75
            width: height * 3

            text: "Add Parent"
            onClicked: root.stackView.push(addOrEditParent)
        }
    }

    Component {
        id: addOrEditParent

        AddParent{
            onSaved: {
                console.log(name, image, email, phone, children)

                parentsListModel.addParent(name, email, phone, image, children)

                root.stackView.pop()
            }

            onCanceled: root.stackView.pop()
        }
    }
}
