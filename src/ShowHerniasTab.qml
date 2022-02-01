import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import "Properties.js" as Properties

Item {
    id: root
    property bool editIsAvailable: false
    property int userId: 0
    property int cardId: 0
    signal addHerniaClicked()

    onCardIdChanged: {
        if(cardId != 0)
            root.showHernias();
    }


    function showHernias()
    {
        listView.model = dbWorker.getHerniasModel(root.cardId);
        countLabel.text = (listView.count > 0) ? ("Число грыж: " + listView.count) : "Грыжи отсутствуют";
    }

    RowLayout{
        id: rowLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20

        Label{
            id: countLabel
            text: ""
            font.pixelSize: 20
            font.bold: true
            Layout.alignment: Qt.AlignLeft
        }

        CustomButton{
            id: addButton
//            anchors.top: parent.top
//            anchors.right: parent.right
//            anchors.margins: 20
            Layout.alignment: Qt.AlignRight
            rectangle.implicitHeight: 40
            rectangle.implicitWidth:  160
            text: "Добавить грыжу"
            color: Properties.buttonColor;
            hoverColor: Properties.buttonHoverColor;
            font.pixelSize: Properties.buttonFontPixelSize;
            visible: root.editIsAvailable
            onClicked: addHerniaClicked()

        }
    }

    ListView{
        id: listView
        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        spacing: 10
        focus: true
        clip: true

        delegate: HerniaListDelegate{
            width: parent.width
            onOpenButtonClicked: {
                programRoot.openViewHerniaPage(herniaId, root.editIsAvailable, root.cardId, root.userId);
            }
        }
    }
}
