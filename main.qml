import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 600


    color: "lightgray"

    Component
    {
        id: childrenDelegate

        MouseArea
        {

            height: 100
            width: parent.width

            onClicked: childrenList.currentIndex = index

            Image
            {
                id:image
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                fillMode: Image.PreserveAspectFit
                source: "./images/child.jpg"
            }

            Text
            {
                id:name
                anchors.left: image.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 16
                text: "Name"
            }

            Text
            {
                id:group
                anchors.left: name.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 16
                text: "Group"
            }

        }
    }

    Rectangle
    {
        width: 800
        height: 500
        anchors.centerIn: parent

        border.color: "red"
        border.width: 10

        ListView
        {
            id: childrenList
            anchors.fill: parent
            anchors.margins: 10
            clip: true
            focus: true
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            model: 20
            delegate: childrenDelegate
        }
    }
}
