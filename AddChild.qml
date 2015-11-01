import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    width: 1000
    height: 620

    Image
    {
        id: photo

        anchors.top: parent.top
        anchors.left: parent.left
        height: parent.height / 2
        width: parent.width / 3

        source: "./images/face.jpg"
        fillMode: Image.PreserveAspectFit
    }

    TextField
    {
        id: name
        anchors.top: parent.top
        anchors.left: photo.right
        anchors.right: parent.right
        height: 75
        anchors.margins: 25
        font.pointSize: 20
        clip: true
        maximumLength: 100
        selectByMouse: true
        placeholderText: "Enter name"
    }

    TextField
    {
        id: dob
        anchors.top: name.bottom
        anchors.left: photo.right
        anchors.right: parent.right
        height: 75
        anchors.margins: 25
        font.pointSize: 20
        clip: true
        maximumLength: 100
        selectByMouse: true
        placeholderText: "Enter date of birth"

        MouseArea{
            anchors.fill: parent
            onClicked: calendar.visible = true
        }
    }

    Item
    {
        id:calendar
        anchors.fill: parent
        visible: false

        Rectangle
        {
            anchors.fill: parent
            opacity: 0.75

            MouseArea
            {
                anchors.fill: parent
                onClicked: calendar.visible = false
            }
        }
        MouseArea
        {
            anchors.centerIn: parent

            height: 500
            width: 500
            onClicked: {}
        }
        Calendar
        {
            anchors.centerIn: parent

            height: 500
            width: 500

            property date today: new Date()
            maximumDate: Date.fromLocaleDateString(today.toLocaleDateString())

            onClicked:{
                calendar.visible = false
                dob.text = date.toLocaleDateString()
            }

            style: CalendarStyle
            {
                navigationBar: Rectangle
                {
                    height: calendar.height / 5

                    Text
                    {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: previousMonth.right
                        anchors.right: nextMonth.left
                        text: styleData.title
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 12
                    }

                    ToolButton
                    {
                        id: previousYear
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        width: parent.width / 6
                        iconSource: "./images/2left.png"
                        onClicked: control.showPreviousYear()
                    }
                    ToolButton
                    {
                        id: previousMonth
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: previousYear.right
                        width: parent.width / 6
                        iconSource: "./images/left.png"
                        onClicked: control.showPreviousMonth()
                    }

                    ToolButton
                    {
                        id: nextYear
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        width: parent.width / 6
                        iconSource: "./images/2right.png"
                        onClicked: control.showNextYear()
                    }
                    ToolButton
                    {
                        id: nextMonth
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: nextYear.left
                        width: parent.width / 6
                        iconSource: "./images/right.png"
                        onClicked: control.showNextMonth()
                    }
                }
            }
        }
    }
}

