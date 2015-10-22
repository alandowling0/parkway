import QtQuick 2.0

Rectangle{
    width: 1000
    height: 600
    border.color: "red"
    border.width: 2
    radius: 5

    ListView
    {
        id: daysList
        anchors.fill: parent
        model: daysModel
        delegate: daysDelegate
        orientation: ListView.Horizontal
        interactive: false
    }

    ListModel{
        id: daysModel
        ListElement
        {
            day: "MON"
            attends: true
        }

        ListElement
        {
            day: "TUE"
            attends: false
        }

        ListElement
        {
            day: "WED"
            attends: true
        }

        ListElement
        {
            day: "THU"
            attends: false
        }

        ListElement
        {
            day: "FRI"
            attends: true
        }
    }

    Component
    {
        id: daysDelegate
        Text
        {
            height: daysList.height
            width: daysList.width / daysModel.count
            text: model.day
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            opacity: model.attends ? 1.0 : 0.3
            font.pointSize: 16
        }
    }
}


