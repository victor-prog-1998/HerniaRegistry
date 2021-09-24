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
    rectangle.radius: height / 2
    font.pixelSize: 18
    width: 100
}
