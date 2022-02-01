import QtQuick 2.9
import QtQuick.Controls 2.2
import "Properties.js" as Properties

Button{
    id: root
    property alias rectangle: rect
    property color color: "white"
    property color hoverColor: "lightgray"

    background: Rectangle{
        id: rect
        color: mouseArea.containsMouse ? parent.hoverColor : parent.color
        radius: Properties.roundnessRaduis
        MouseArea{
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: root.clicked()
        }
        // linux
//        Text{
//            anchors.centerIn: parent
//            text: root.text
//            color: "black"
//            font.pixelSize: 12
//        }
        // linux
    }
}
