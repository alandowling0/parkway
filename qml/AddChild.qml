import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2

Rectangle {
    id: root

    signal saved(string name, string dob, string group, string image)
    signal canceled

    property var stackView: StackView.view
    property real rowHeight: Math.min(height * 0.2, 100)
    property real fontSize: Math.max(8, rowHeight * 0.2)

    Item {
        id: lhs

        anchors.top: parent.top
        anchors.bottom: buttonArea.top
        anchors.left: parent.left
        width: parent.width * 0.6

        Column {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.9

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                TextField {
                    id: enterName

                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width

                    selectByMouse: true
                    placeholderText: "Name"
                    font.pointSize: root.fontSize
                }
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                TextField {
                    id: enterDob

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    height: parent.height * 0.75
                    width: parent.width - (parent.height * 1.1)

                    font.pointSize: root.fontSize
                    selectByMouse: true
                    placeholderText: "Date of Birth"
                    readOnly: true
                }

                Item {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: parent.height

                    Button {
                        anchors.centerIn: parent
                        height: parent.height * 0.75
                        width: parent.width * 0.75

                        onClicked: root.stackView.push(dobPicker)

                        Image {
                            anchors.fill: parent
                            fillMode: Image.PreserveAspectFit
                            source: "../images/calendar.png"
                        }
                    }
                }
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                ComboBox {
                    id: enterGroup

                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width

                    model: groupsListModel.groupNames
                }
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                Image {
                    id: photo

                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    width: height

                    source: "../images/face.jpg"
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        anchors.fill: parent
                        onClicked: fileDialog.open()
                    }
                }
            }
        }
    }

    Item {
        id: rhs

        anchors.top: parent.top
        anchors.bottom: buttonArea.top
        anchors.left: lhs.right
        anchors.right: parent.right
    }

    Item {
        id: buttonArea

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: root.rowHeight

        Row {
            anchors.centerIn: parent
            height: parent.height * 0.5

            spacing: height * 0.25

            Button {
                height: parent.height
                width: height * 2.5
                text: "Save"

                onClicked: root.saved(enterName.text, enterDob.text, enterGroup.currentText, photo.source)
            }

            Button {
                height: parent.height
                width: height * 2.5
                text: "Cancel"

                onClicked: root.canceled()
            }
        }
    }

    FileDialog {
        id: fileDialog

        title: "Please choose a photo"
        nameFilters: [ "Image files (*.jpg *.png)" ]
        folder: shortcuts.pictures
        onAccepted: photo.source = fileDialog.fileUrl
    }

    Component {
        id: dobPicker

        DatePicker {
            onDateNotPicked: root.stackView.pop()
            onDatePicked: {
                enterDob.text = date
                root.stackView.pop()
            }
        }
    }
}
