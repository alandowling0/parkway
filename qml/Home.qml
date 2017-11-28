import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: root

    property var stackView: StackView.view

    Item {
        anchors.centerIn: parent
        height: parent.height * 0.8
        width: parent.width * 0.8

        GridView {
            id: gridView

            anchors.fill: parent
            clip: true

            cellHeight: parent.height * 0.5
            cellWidth: parent.width * 0.333

            delegate: Item {
                height: gridView.cellHeight
                width: gridView.cellWidth

                Button {
                    anchors.centerIn: parent
                    height: parent.height * 0.8
                    width: parent.width * 0.8
                    text: modelData.buttonText

                    enabled: modelData.pageName !== undefined
                    opacity: enabled ? 1.0 : 0.75

                    onClicked: root.stackView.push(modelData.pageName)
                }
            }

            model: [
                {"buttonText" : "Kids", "pageName" : kids},
                {"buttonText" : "Parents", "pageName" : parents},
                {"buttonText" : "Groups"},
                {"buttonText" : "Registers"},
                {"buttonText" : "Money"},
                {"buttonText" : "Settings"}
            ]
        }
    }

    Component {
        id: kids

        Children {}
    }

    Component {
        id: parents

        Parents {}
    }
}
