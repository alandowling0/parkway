import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Item {
    id: root

    property string selectedChildName: ""

    property real rowHeight: 50
    property real pointSize: root.rowHeight * 0.25

    ListView {
        id: childrenList

        anchors.fill: parent
        clip: true
        focus: true
        model: childrenListModel
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
                width: childrenList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Name"
                }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: childrenListModel.sortByName()
//                }
            }

            Item {
                id: groupHeaderArea

                height: parent.height
                width: childrenList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Group"
                }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: childrenListModel.sortByGroup()
//                }
            }

            Item {
                id: ageHeaderArea

                height: parent.height
                width: childrenList.width * 0.3

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    font.pointSize: root.pointSize
                    font.bold: true
                    text: "Age"
                }

//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: childrenListModel.sortByAge()
//                }
            }
        }
    }

    Component {
        id: delegate

        Item {
            id: rowArea

            height: root.rowHeight
            width: childrenList.width

            Row {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                Item {
                    id: imageArea

                    height: parent.height
                    width: rowArea.width * 0.1

                    Image {
                        id: image

                        anchors.centerIn: parent
                        height: parent.height * 0.9
                        width: parent.width * 0.9

                        fillMode: Image.PreserveAspectFit
                        source: model.imageUrl
                    }
                }

                Item {
                    id: nameArea

                    height: parent.height
                    width: rowArea.width * 0.3

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
                    id: groupArea

                    height: parent.height
                    width: rowArea.width * 0.3

                    Text {
                        id: group

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.pointSize: root.pointSize
                        text: model.group
                    }
                }

                Item {
                    id: ageArea

                    height: parent.height
                    width: rowArea.width * 0.3

                    Text {
                        id: age

                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        font.pointSize: root.pointSize
                        text: model.age
                    }
                }
            }

            MouseArea {
                anchors.fill: parent

                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {
                    childrenList.currentIndex = index
                    root.selectedChildName = model.name

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
                    onTriggered: {
                        childrenListModel.removeChild(root.selectedChildName)
                    }
                }
            }
        }
    }
}
