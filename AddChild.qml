 import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import com.panchito.parkway 1.0

Rectangle
{
    width: 1000
    height: 300

    property int textInputMaxLength: 100
    property int textInputFontSize: 20
    property string annonymousFace: "./images/face.jpg"

    signal saved(string name, string dob, string group, string image);
    signal canceled;

    function clear()
    {
        photo.source = annonymousFace
        enterName.text = ""
        enterDob.text = ""
        enterGroup.currentIndex = 0
    }

    GroupsListModel{id:groupsListModel}

    Item
    {
        id: dataArea

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: buttonArea.top

        Image
        {
            id: photo
            anchors.top: dataArea.top
            anchors.bottom: dataArea.bottom
            anchors.left: dataArea.left
            width: dataArea.height

            source: annonymousFace
            fillMode: Image.PreserveAspectFit

            MouseArea
            {
                anchors.fill: parent
                onClicked: fileDialog.open()
            }
        }

        TextField
        {
            id: enterName
            anchors.top: dataArea.top
            anchors.right: dataArea.right
            anchors.left: photo.right
            height: dataArea.height / 3
            font.pointSize: textInputFontSize
            maximumLength: textInputMaxLength
            selectByMouse: true
            placeholderText: "Name"
        }

        TextField
        {
            id: enterDob
            anchors.top: enterName.bottom
            anchors.right: dataArea.right
            anchors.left: photo.right
            height: dataArea.height / 3
            font.pointSize: textInputFontSize
            maximumLength: textInputMaxLength
            selectByMouse: true
            placeholderText: "Date of Birth"
            readOnly: true

            Button
            {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: parent.height
                onClicked: dobPicker.visible = true

                Image
                {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "./images/calendar.png"
                }
            }
        }

        ComboBox
        {
            id: enterGroup
            anchors.top: enterDob.bottom
            anchors.right: dataArea.right
            anchors.left: photo.right
            height: dataArea.height / 3
            model: groupsListModel
            textRole: "name"
        }
    }

    Item
    {
        id: buttonArea

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50

        Button
        {
            id: cancelButton
            anchors.top: buttonArea.top
            anchors.bottom: buttonArea.bottom
            anchors.right: buttonArea.right
            width: 200
            text: "Cancel"
            onClicked: canceled()
        }

        Button
        {
            id: saveButton
            anchors.top: buttonArea.top
            anchors.bottom: buttonArea.bottom
            anchors.right: cancelButton.left
            width: 200
            text: "Save"
            onClicked: saved(enterName.text, enterDob.text, enterGroup.currentText, photo.source)
        }
    }

    FileDialog
    {
        id: fileDialog
        title: "Please choose a photo"
        nameFilters: [ "Image files (*.jpg *.png)" ]
        folder: shortcuts.pictures
        onAccepted: photo.source = fileDialog.fileUrl
    }

    DatePicker
    {
        id: dobPicker
        visible: false
        anchors.fill: parent
        onDateNotPicked: visible=false
        onDatePicked:
            {
            enterDob.text = date
            visible=false
            }
    }
}

