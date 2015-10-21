import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    height: 600

    color: "lightgray"

    Component
    {
        id: parentsDelegate

        MouseArea
        {
            height: 100
            width: parent.width

            Text
            {
                id:name
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 12
                text: "Mum"
                wrapMode: Text.Wrap
            }

            Text
            {
                id:email
                anchors.left: name.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 12
                text: "email@example.com"
                wrapMode: Text.Wrap
            }

            Text
            {
                id:phone
                anchors.left: email.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 12
                text: "07654 123456"
                wrapMode: Text.Wrap
            }
        }
    }

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
                wrapMode: Text.Wrap
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
                wrapMode: Text.Wrap
            }

        }
    }

    Rectangle
    {
        id: children

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width / 2
        anchors.margins: 10

        border.color: "red"
        border.width: 2

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

    Rectangle
    {
        id: parents

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: children.right
        height: parent.height / 2
        anchors.margins: 10

        border.color: "red"
        border.width: 2

        ListView
        {
            id: parentsList
            anchors.fill: parent
            anchors.margins: 10
            clip: true
            model: 2
            delegate: parentsDelegate
        }
    }
}
