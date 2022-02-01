import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

RadioButton{
    id: root
    //property int radius: 10
    property int fontPixelSize: 16


    indicator: Rectangle{
        id: rect
        width: root.height
        height: root.height
        radius: width / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        border.color: root.down ? "#17a81a" : "#21be2b"
        Rectangle{
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            radius: parent.radius / 2
            color: root.down ? "#17a81a" : "#21be2b"
            visible: root.checked
        }
    }

    contentItem: Label{
        id: txt
        text: root.text
        font.pixelSize: root.fontPixelSize
        verticalAlignment: Text.AlignVCenter
        anchors.left: rect.right
        anchors.leftMargin: 10
    }
}
