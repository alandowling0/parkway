import QtQuick 2.0

import com.panchito.parkway 1.0

Rectangle
{
    ChildrenListModel{id:childrenListModel}

    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    MouseArea{
        anchors.fill: parent
        onClicked: {console.log("onClicked");childrenListModel.doSomething()}
        z: 100
    }

    ListView
    {
        id: childrenList
        anchors.fill: parent
        anchors.margins: 10
        clip: true
        focus: true
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        model: childrenListModel
        delegate: delegate
    }

    Component
    {
        id: delegate
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
                text: model.name
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
                text: model.group
                wrapMode: Text.Wrap
            }
        }
    }
}
