import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2

Rectangle {
    id: root

    signal saved(string name, string dob, string group, string image, var parents)
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
                    placeholderText: "Enter Name..."
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
                    placeholderText: "Select Date of Birth..."
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

                    font.pointSize: root.fontSize
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

        z: 1

        anchors.top: parent.top
        anchors.bottom: buttonArea.top
        anchors.left: lhs.right
        anchors.right: parent.right

        Item {
            id: addParentArea

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: root.rowHeight

            z: 1

            Item {
                id: searchBoxArea

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: addButtonArea.left

                Completer {
                    id: searchBox

                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width
                    rowHeight: parent.height * 0.75

                    model: parentsListModel.parentsNames

                    placeholderText: "Add Parent.."
                }
            }

            Item {
                id: addButtonArea

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: height

                Button {
                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width * 0.75

                    text: "Add"

                    enabled: searchBox.valid && !parentsList.model.contains(searchBox.text)
                    opacity: enabled ? 1.0 : 0.5

                    onClicked: {
                        parentsList.model.append({"name": searchBox.text})
                        parentsList.positionViewAtEnd()
                        searchBox.clear()
                    }
                }
            }
        }

        Rectangle {
            id: parentsListArea

            anchors.top: addParentArea.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            border.width: 1

            ListView {
                id: parentsList

                anchors.fill: parent

                clip: true

                model: ListModel {
                    function contains(name)
                    {
                        var found = false

                        for(var i=0; i<count; ++i)
                        {
                            if(get(i).name === name)
                            {
                                found = true
                            }
                        }

                        return found
                    }
                }

                delegate: Item {
                    height: root.rowHeight
                    width: parent.width

                    Text {
                        anchors.centerIn: parent
                        width: parent.width * 0.9
                        elide: Text.ElideRight

                        text: model.name
                        font.pointSize: root.fontSize
                    }

                    Item {
                        id: removeButtonArea

                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        width: height

                        Button {
                            anchors.centerIn: parent
                            height: parent.height * 0.75
                            width: parent.width * 0.75
                            text: "Remove"

                            onClicked: {
                                parentsList.model.remove(index)
                            }
                        }
                    }
                }
            }
        }
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

                onClicked: {
                    var parents = []

                    for(var i=0; i<parentsList.model.count; ++i)
                    {
                        parents.push(parentsList.model.get(i).name)
                    }

                    root.saved(enterName.text, enterDob.text, enterGroup.currentText, photo.source, parents)
                }
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
