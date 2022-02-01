import QtQuick 2.0


CustomButton{
    id: backButton


    anchors.verticalCenter: parent.verticalCenter
//    anchors.right: parent.right
//    anchors.rightMargin: 10
    text: "Назад"
    //onClicked: backClicked();
    //Layout.fillWidth: true

    rectangle.border.color: "#3778fa"
    font.pixelSize: 18
    width: 100
    // height: 32 // linux
}
