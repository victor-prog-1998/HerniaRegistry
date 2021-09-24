import QtQuick 2.0
import QtQuick.Controls 2.2
import "Properties.js" as Properties

GroupBox{
    id: root
    property alias titleLabel: lbl
    property alias rectangle: rect


    label: Label{
        id: lbl
        text: root.title
        font.pixelSize: 16
    }

    background: Rectangle {
        id: rect
         y: root.topPadding -  root.bottomPadding
         width: parent.width
         height: parent.height -  root.topPadding +  root.bottomPadding
         color: "transparent"
         border.color: Properties.groupBoxFrameColor
         radius: height / 2
         //antialiasing: false
    }
 }
