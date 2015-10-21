import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 600

    Component
    {
        id: childrenDelegate
        Item
        {
            height: 50
            width: parent.width

            Text
            {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 2
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 16
                text: "Name"
            }
            Image
            {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 2
                fillMode: Image.PreserveAspectFit
                source: "./images/child.jpg"
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
            model: 20
            delegate: childrenDelegate
        }
    }
}
