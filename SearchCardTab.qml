import QtQuick 2.0
import "Properties.js" as Properties
import QtQuick.Controls 2.2

Item {
    id: root
    property int userID: 0
    property alias listView: listView
    property bool adminMode: false
    signal openCardClicked(var cardId)

    function show()
    {
        if(snilsField.field.text.length == Properties.snilsLength)
        {
            listView.model = dbWorker.getCardBySnils(userID, snilsField.field.text, (!adminMode) && checkBox.checked);
        }
    }

    Item{
        anchors.fill: parent
        anchors.margins: 20
        Column{
            id: controlsColumn
            width: parent.width
            spacing: 15
            //anchors.margins: 10
            anchors.left: parent.left
            anchors.top: parent.top

            TextFieldWithLabel{
                id: snilsField
                label.text: "СНИЛС";
                field.implicitWidth: 200
                field.implicitHeight: 40
                field.inputMask: Properties.snilsInputMask
            }

            CustomButton{
                rectangle.implicitHeight: 40
                rectangle.implicitWidth:  200
                text: "Найти карту"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                rectangle.radius: height / 2
                onClicked: root.show()
                enabled: snilsField.field.text.length == Properties.snilsLength
            }

            CheckBox{
                id: checkBox
                text: "Поиск только среди доступных карт";
                font.pixelSize: 16
                visible: !adminMode
            }

        }

        PatientListView{
            id: listView
            anchors.top: controlsColumn.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 20
            //model: dbWorker.getAllCardsModel(userID)
            onOpenCardClicked: root.openCardClicked(cardId)
        }
    }
}
