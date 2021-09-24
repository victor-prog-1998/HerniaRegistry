import QtQuick 2.9
import QtQuick.Controls 2.2

Button{
    id: root
    property alias rectangle: rect
    property color color: "white"
    property color hoverColor: "lightgray"
    background: Rectangle{
        id: rect
        color: mouseArea.containsMouse ? parent.hoverColor : parent.color
        MouseArea{
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: root.clicked()
        }
    }
}
