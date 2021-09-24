import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page{
    id: root
    property bool editIsAvailable: false
    property int userId: 0
    property int cardId: 0

    property alias showRiskFactorsTab: showRiskFactorsTab

    signal closeCardClicked()
    signal editMainInfoClicked(var cardId);
    signal addHerniaClicked(var cardId)

    function updateMainInfo()
    {
        showMainCardInfoTab.setCardInfo();
    }

    function updateHernias()
    {
        showHerniasTab.showHernias();
    }

    BackgroundGradient{
        anchors.fill: parent
    }

    header: ProgramHeader{
        HeaderButton{
            anchors.right: parent.right
            anchors.rightMargin: 10
            text: "Назад"
            onClicked: {
                closeCardClicked();
            }
        }
        Text{
            font.pixelSize: 18
            text: "Просмотр карты пациента"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            width: parent.width / 2
        }
    }

    TabBar{
        id: tabBar
        width: parent.width
        TabButton{
            text: "Основная информация";
            id: tb1
        }

        TabButton{
            text: "Факторы риска";
        }

        TabButton{
            text: "Грыжи";
        }
    }

    StackLayout{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: tabBar.bottom
        currentIndex: tabBar.currentIndex


        ShowMainCardInfoTab{
            id: showMainCardInfoTab
            userId: root.userId
            cardId: root.cardId
            editIsAvailable: root.editIsAvailable
            onEditClicked: editMainInfoClicked(cardId)
        }

        ShowRiskFactorsTab{
            id: showRiskFactorsTab
            userId: root.userId
            cardId: root.cardId
            editIsAvailable: root.editIsAvailable
        }

        ShowHerniasTab{
            id: showHerniasTab
            userId: root.userId
            cardId: root.cardId
            editIsAvailable: root.editIsAvailable
            onAddHerniaClicked: root.addHerniaClicked(root.cardId)
        }


    }

}
