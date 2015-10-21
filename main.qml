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
                anchors.fill:parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 12
                text: "Name"
            }
        }
    }

    Rectangle
    {
        width: 500
        height: 400
        anchors.centerIn: parent

        border.color: "red"
        border.width: 10

        ListView
        {
            id: childrenList
            anchors.fill: parent
            clip: true
            model: 20
            delegate: childrenDelegate
        }
    }
}
