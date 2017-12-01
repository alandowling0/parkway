import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Item {
    id: root

    property real rowHeight: 50
    property real pointSize: root.rowHeight * 0.25

    ListView {
        id: parentsList

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        focus: true
        model: parentsListModel
        onModelChanged: currentIndex = -1
        delegate: delegate
        header: header
        currentIndex: -1
        highlight: Rectangle {color: "lightgray"; radius: 5}
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 250
    }

    Component {
        id: header

        Row {
            height: root.rowHeight
            anchors.right: parent.right

            Item {
                id: nameHeaderArea

                height: parent.height
                width: parentsList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Name"
                }
            }

            Item {
                id: emailHeaderArea

                height: parent.height
                width: parentsList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Email"
                }
            }

            Item {
                id: phoneHeaderArea

                height: parent.height
                width: parentsList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Phone"
                }
            }
        }
    }

    Component {
        id: delegate

        Item {
            height: root.rowHeight
            width: parentsList.width

            Row {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                Item {
                    id: imageArea

                    height: parent.height
                    width: parentsList.width * 0.1

                    Image {
                        id: image

                        anchors.centerIn: parent
                        height: parent.height * 0.9
                        width: parent.width * 0.9

                        fillMode: Image.PreserveAspectFit
                        source: "../images/face.jpg"
                    }
                }

                Item {
                    id: nameArea

                    height: parent.height
                    width: parentsList.width * 0.3

                    Text {
                        id: name

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.pointSize: root.pointSize
                        text: model.name
                    }
                }

                Item {
                    id: emailArea

                    height: parent.height
                    width: parentsList.width * 0.3

                    Text {
                        id: email

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.pointSize: root.pointSize
                        text: model.email
                    }
                }

                Item {
                    id: phoneArea

                    height: parent.height
                    width: parentsList.width * 0.3

                    Text {
                        id: phone

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.pointSize: root.pointSize
                        text: model.phone
                    }
                }
            }

            MouseArea {
                anchors.fill: parent

                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {
                    parentsList.currentIndex = index

                    if (mouse.button === Qt.RightButton)
                    {
                        contextMenu.open();
                    }
                }
            }

            Menu {
                id: contextMenu

                y: parent.height
                width: parent.width

                MenuItem {
                    text: "Edit";
                }

                MenuItem {
                    text: "Delete";
                }
            }
        }
    }
}
