import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

Page{
    property int userID: 0
    property string userFio: ""
    signal exitClicked();
    property alias messageDialog: messageDialog;

    header:  ProgramHeader{
                HeaderButton{
                    id: exitButton
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: "Выйти"
                    onClicked: {
                        exitClicked();
                    }
                }
                HeaderButton{
                    width: 130
                    anchors.right: exitButton.left
                    anchors.rightMargin: 10
                    color: "#6ffc95"
                    hoverColor: "#3dd465"
                    rectangle.border.color: "#00a12b"
                    text: "Статистика"
                    onClicked: {
                        programRoot.openStatisticsPage();
                    }
                }
                Text{
                    font.pixelSize: 18
                    text: userFio
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true
                    width: parent.width / 2
                }
    }


    CustomMessageDialog{
        id: messageDialog
    }

    CustomMessageDialog{
        id: yesNoMessageDialog
        standardButtons: StandardButton.No | StandardButton.Yes
    }

//    BackgroundGradient{
//        anchors.fill: parent
//    }
}
