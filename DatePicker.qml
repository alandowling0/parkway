import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Item {
    id: root

    width: 1000
    height: 620

    property int margin: 50

    signal dateNotPicked()
    signal datePicked(string date)

    Rectangle
    {
        anchors.fill: parent
        opacity: 0.8

        MouseArea
        {
            anchors.fill: parent
            onClicked: dateNotPicked()
        }
    }

    MouseArea
    {
        height: Math.min(parent.height, parent.width) - root.margin
        width: height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Calendar
        {
            id:calendar
            anchors.fill: parent

            property date today: new Date()
            maximumDate: Date.fromLocaleDateString(today.toLocaleDateString())

            onClicked:
            {
                datePicked(date.toLocaleDateString())
            }

            style: CalendarStyle
            {
                navigationBar: Rectangle
                {
                    height: calendar.height / 8
                    property int toolButtonWidth: calendar.width / 7

                    ToolButton
                    {
                        id: previousYear
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        width: toolButtonWidth
                        onClicked: control.showPreviousYear()
                        Image
                        {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: height
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "./images/PreviousYear.png"
                        }
                    }

                    ToolButton
                    {
                        id: previousMonth
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: previousYear.right
                        width: toolButtonWidth
                        onClicked: control.showPreviousMonth()
                        Image
                        {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: height
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "./images/PreviousMonth.png"
                        }
                    }

                    Text
                    {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: previousMonth.right
                        anchors.right: nextMonth.left
                        text: styleData.title
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 25
                        fontSizeMode: Text.Fit
                    }

                    ToolButton
                    {
                        id: nextYear
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        width: toolButtonWidth
                        onClicked: control.showNextYear()
                        Image
                        {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: height
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "./images/NextYear.png"
                        }
                    }

                    ToolButton
                    {
                        id: nextMonth
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.right: nextYear.left
                        width: toolButtonWidth
                        onClicked: control.showNextMonth()
                        Image
                        {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: height
                            anchors.horizontalCenter: parent.horizontalCenter
                            source: "./images/NextMonth.png"
                        }
                    }
                }
            }
        }
    }
}

