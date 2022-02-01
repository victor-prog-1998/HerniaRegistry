import QtQuick 2.0
import "Properties.js" as Properties
import QtQuick.Controls 2.2

Item {
    id: root
    property int userID: 0
    property bool adminMode: false
    property alias listView: listView
    signal openCardClicked(var cardId)


    function show()
    {
        if(!adminMode)
            listView.model =  checkBox.checked? dbWorker.getAllAvailableCardsModel(userID) :
                                           dbWorker.getAllCardsModel(userID);
        else
            listView.model = dbWorker.getAllCardsModel(userID);
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

            CustomButton{
                rectangle.implicitHeight: 40
                rectangle.implicitWidth:  200
                text: "Показать"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                onClicked: root.show()
            }

            CheckBox{
                id: checkBox
                text: "Только доступные карты";
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
