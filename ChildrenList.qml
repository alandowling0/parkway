import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.panchito.parkway 1.0

Rectangle
{
    id: root
    ChildrenListModel{id:childrenListModel}

    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    property string imageRoot: "./images/"

    signal childSelected(string childName)

    Component
    {
        id: header

        Item
        {
            height: 50
            width: childrenList.width

            Text
            {
                id: headerImage
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width / 4

            }
            Text
            {
                id: headerName
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: headerImage.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width / 4
                text: "Name"
                font.pointSize: 16
                font.bold: true
            }
            Text
            {
                id: headerGroup
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: headerName.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width / 4
                text: "Group"
                font.pointSize: 16
                font.bold: true
            }
            Text
            {
                id: headerAge
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: headerGroup.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width / 4
                text: "Age"
                font.pointSize: 16
                font.bold: true
            }
        }
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
        header: header
        footer: footer
        footerPositioning: ListView.OverlayFooter
        onCurrentIndexChanged:
        {
            root.childSelected(childrenListModel.getChildName(currentIndex))
        }
    }

    Component
    {
        id: delegate
        MouseArea
        {
            height: 100
            width: parent.width
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressAndHold:
            {
                childrenList.currentIndex = index
                contextMenu.popup();
            }
            onClicked:
            {
                if (mouse.button == Qt.LeftButton)
                {
                    childrenList.currentIndex = index
                }
                else if (mouse.button == Qt.RightButton)
                {
                    childrenList.currentIndex = index
                    contextMenu.popup();
                }
            }

            Image
            {
                id:image
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 4
                fillMode: Image.PreserveAspectFit
                source: imageRoot + model.image
            }

            Text
            {
                id:name
                anchors.left: image.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 4
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
                width: parent.width / 4
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 16
                text: model.group
                wrapMode: Text.Wrap
            }

            Text
            {
                id:age
                anchors.left: group.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.width / 4
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 16
                text: model.age
                wrapMode: Text.Wrap
            }
        }
    }

    Component
    {
        id: footer
        Rectangle
        {
            height: 75
            width: childrenList.width
            z: 2

            Button
            {
                anchors.fill: parent
                anchors.margins: 10

                Image{
                    anchors.fill: parent
                    source: imageRoot + "add.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    Menu
    {
        id: contextMenu

        style: MenuStyle
        {
            frame: Rectangle{border.color: "blue"}
            itemDelegate.label: Text{text: styleData.text; font.pointSize: 30;}
        }
        MenuItem {
            text: "Edit";
        }
        MenuItem {
            text: "Delete";
        }
    }
}
