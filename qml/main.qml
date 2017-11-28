import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 1000
    height: 600

    color: "gray"

    Rectangle {
        id: header

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40

        color: "lightgray"

        Row {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            ToolButton {
                height: parent.height
                width: height
                enabled: stackView.depth > 1
                opacity: enabled ? 1.0 : 0.5
                onClicked: stackView.pop()
                contentItem: Image {
                    source: "../images/back.png"
                }
            }

            ToolButton {
                height: parent.height
                width: height
                onClicked: stackView.pop(null)
                contentItem: Image {
                    source: "../images/home.png"
                }
            }
        }
    }

    StackView {
        id: stackView

        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        pushEnter: fadeIn
        popEnter: fadeIn
        replaceEnter: fadeIn
        pushExit: null
        popExit: null
        replaceExit: null

        Transition {
            id: fadeIn

            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 250
            }
        }

        initialItem: Home {}
    }
}
