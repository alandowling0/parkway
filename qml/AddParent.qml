import QtQuick 2.5
import QtQuick.Controls 2.0

Item {
    id: root

    signal saved(string name, string image, string email, string phone)
    signal canceled

    property var stackView: StackView.view
    property real rowHeight: Math.min(height * 0.125, 100)
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
                    placeholderText: "Name..."
                    font.pointSize: root.fontSize
                }
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                TextField {
                    id: enterEmail

                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width

                    selectByMouse: true
                    placeholderText: "Email..."
                    font.pointSize: root.fontSize
                }
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: root.rowHeight

                TextField {
                    id: enterPhone

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    height: parent.height * 0.75
                    width: parent.width

                    font.pointSize: root.fontSize
                    selectByMouse: true
                    placeholderText: "Phone..."
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
                       // onClicked: fileDialog.open()
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

        Item {
            id: addChildArea

            anchors.centerIn: parent
            height: parent.height
            width: parent.width * 0.9

            Item {
                id: searchBoxArea

                anchors.top: parent.top
                anchors.left:parent.left
                anchors.right: parent.right
                height: root.rowHeight

                Completer {
                    id: searchBox

                    anchors.centerIn: parent
                    height: parent.height * 0.75
                    width: parent.width

                    model: childrenListModel.childrenNames

                    placeholderText: "Add Child.."

                    onSelected: {
                        if(!childrenList.model.contains(selectedText))
                        {
                            childrenList.model.append({"name": selectedText})
                            childrenList.positionViewAtEnd()
                        }
                    }
                }
            }

            Rectangle {
                id: childrenListArea

                anchors.top: searchBoxArea.bottom
                anchors.bottom: parent.bottom
                anchors.left:parent.left
                anchors.right: parent.right

                ListView {
                    id: childrenList

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
                                    childrenList.model.remove(index)
                                }
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
        anchors.left:parent.left
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
                    root.saved(enterName.text, "../images/face.jpg", enterEmail.text, enterPhone.text)
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
}
