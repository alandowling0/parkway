import QtQuick 2.0
import QtQuick.Controls 2.0

FocusScope {
    id: root

    property real rowHeight: 50
    property int maxRows: 5
    property real fontSize: Math.max(8, root.rowHeight * 0.25)
    property var model: [
        "Alan",
        "Isabel",
        "Michelle Gilchrist",
        "Rohan Gilchrist",
        "Alex",
        "Alan Dowling"
    ]

    property string text: textField.text
    property bool valid: textField.validInput
    property string placeholderText: "Enter Text"

    function clear() {
        textField.clear()
        optionsArea.optionSelected = false
    }

    TextField {
        id: textField

        property bool validInput: root.model.indexOf(text) >= 0

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: root.rowHeight
        selectByMouse: true

        font.pointSize: root.fontSize

        placeholderText: root.placeholderText

        onTextEdited: {
            var options = []

            for(var i=0; i<root.model.length; ++i)
            {
                if(root.model[i].toLowerCase().indexOf(text.toLowerCase()) >= 0)
                {
                    options.push(root.model[i])
                }
            }

            optionsList.model = options

            optionsArea.optionSelected = false
        }

        opacity: validInput ? 1.0 : 0.5
    }

    Rectangle {
        id: optionsArea

        property bool optionSelected: false

        anchors.top: textField.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: root.activeFocus && !optionsArea.optionSelected ? (root.rowHeight * Math.min(root.maxRows, optionsList.count)) : 0
        clip: true

        border.color: "lightgray"

        ListView {
            id: optionsList

            anchors.fill: parent
            model: root.model

            delegate: Item {
                height: root.rowHeight
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
                        textField.text = modelData

                        optionsArea.optionSelected = true
                    }
                }
            }
        }
    }
}
