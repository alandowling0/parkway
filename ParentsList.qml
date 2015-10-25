import QtQuick 2.0

import com.panchito.parkway 1.0

Rectangle {
    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    ParentsListModel { id: parentsListModel }

    ListView
    {
        id: parentsList
        anchors.fill: parent
        anchors.margins: 10
        clip: true
        model: parentsListModel
        delegate: delegate
    }

    ListModel
    {
        id: parentsModel

        ListElement
        {
            name: "Mum"
            email: "mummy@example.com"
            phone: "07654 123456"
        }

        ListElement
        {
            name: "Dad"
            email: "daddy@example.com"
            phone: "07654 654321"
        }
    }

    Component
    {
        id: delegate

        MouseArea
        {
            height: 50
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
                text: model.name
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
                text: model.email
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
                text: model.phone
                wrapMode: Text.Wrap
            }
        }
    }
}

