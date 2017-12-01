import QtQuick 2.0

Item {
    id: root

    property var parentsModel: parentsOfChildListModel
    property real rowHeight: 50
    property real pointSize: rowHeight * 0.25

    ListView {
        id: parentsList

        anchors.fill: parent
        clip: true
        model: root.parentsModel
        delegate: delegate
        header: header
    }

    Component {
        id: header

        Item {
            height: root.rowHeight
            width: parentsList.width

            Text {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width * 0.9
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: root.pointSize
                font.bold: true
                text: "Parents"
            }
        }
    }

    Component {
        id: delegate

        Row {
            height: root.rowHeight
            anchors.left: parent.left

            Item {
                id: imageArea

                height: parent.height
                width: parentsList.width * 0.2

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
                width: parentsList.width * 0.8

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
        }
    }
}

