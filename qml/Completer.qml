import QtQuick 2.0
import QtQuick.Controls 2.0

FocusScope {
    id: root

    signal selected(string selectedText)

    property int maxRows: 5
    property var model: []
    property real fontSize: Math.max(8, root.height * 0.25)
    property string placeholderText: "Search..."

    TextField {
        id: textField

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: root.height

        selectByMouse: true
        font.pointSize: root.fontSize
        placeholderText: root.placeholderText

        onActiveFocusChanged: {
            if(activeFocus)
                optionsPopup.open()
        }

        onPressed: optionsPopup.open()
    }

    Item {
        id: optionsArea

        anchors.top: textField.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: optionsPopup.visible ? root.height * Math.min(root.maxRows, optionsList.count) : 0

        Popup {
            id: optionsPopup

            height: parent.height
            width: parent.width

            padding: 0

            ListView {
                id: optionsList

                anchors.fill: parent
                clip: true

                model: {
                    var options = []

                    for(var i=0; i<root.model.length; ++i)
                    {
                        if(root.model[i].toLowerCase().indexOf(textField.text.toLowerCase()) >= 0)
                        {
                            options.push(root.model[i])
                        }
                    }

                    return options
                }

                delegate: Item {
                    height: root.height
                    width: parent.width

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: textField.leftPadding
                        font.pointSize: root.fontSize
                        text: modelData
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            root.selected(modelData)
                            optionsPopup.close()
                            textField.clear()
                        }
                    }
                }
            }
        }
    }
}
