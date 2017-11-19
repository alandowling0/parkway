import QtQuick 2.0

Rectangle
{
    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    function setChild(childName)
    {
        timetablesListModel.setChild(childName)
    }

    ListView
    {
        id: daysList
        anchors.fill: parent
        anchors.margins: 10
        clip: true
        model: timetablesListModel
        delegate: daysDelegate
        interactive: false
    }

    Component
    {
        id: daysDelegate

        Item
        {
            width: daysList.width
            height: daysList.height

            Text
            {
                id: monday

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 5

                text: "MON"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.mon ? 1.0 : 0.3
                font.pointSize: 16
            }
            Text
            {
                id: tuesday

                anchors.left: monday.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 5

                text: "TUE"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.tue ? 1.0 : 0.3
                font.pointSize: 16
            }
            Text
            {
                id: wednesday

                anchors.left: tuesday.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 5

                text: "WED"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.wed ? 1.0 : 0.3
                font.pointSize: 16
            }
            Text
            {
                id: thursday

                anchors.left: wednesday.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 5

                text: "THU"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.thu ? 1.0 : 0.3
                font.pointSize: 16
            }
            Text
            {
                id: friday

                anchors.left: thursday.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 5
                width: parent.width / 5

                text: "FRI"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                opacity: model.fri ? 1.0 : 0.3
                font.pointSize: 16
            }
        }
    }
}


