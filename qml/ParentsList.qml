import QtQuick 2.0

Rectangle {
    id: root

    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    property var parentsModel: parentsListModel

    ListView
    {
        id: parentsList

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        model: root.parentsModel
        delegate: delegate
    }

    Component
    {
        id: delegate

        Item
        {
            height: 50
            width: parent.width

            Text
            {
                id: name

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                text: model.name
                wrapMode: Text.Wrap
            }

            Text
            {
                id: email

                anchors.left: name.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                text: model.email
                wrapMode: Text.Wrap
            }

            Text
            {
                id: phone

                anchors.left: email.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                text: model.phone
                wrapMode: Text.Wrap
            }
        }
    }
}

