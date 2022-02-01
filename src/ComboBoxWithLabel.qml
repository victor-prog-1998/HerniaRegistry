import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties


// По умолчанию значение в комбобоксе устанавливается как невыбранное (индекс = -1)

ColumnLayout{
//    spacing: 10
//    Layout.margins: 10

    function reset()
    {
        comboBox.currentIndex = -1;
    }

    function isSelected()
    {
        return comboBox.currentIndex != -1;
    }


    Layout.fillWidth: true
    Layout.fillHeight: true
    property alias label: label
    property alias comboBox: comboBox
    property alias background: bgRect

    Label{
        id: label
        font.pixelSize: 16
        Layout.fillWidth: true
        opacity: enabled ? 1.0 : 0.3
        color: "black"
    }
    ComboBox{
        id: comboBox
        currentIndex: -1
        Layout.minimumWidth: 80
        //Layout.maximumWidth: 100
        implicitHeight: 40
        Layout.fillWidth: true
        font.pixelSize: 18
        background: Rectangle{
            id: bgRect
            radius: Properties.roundnessRaduis
        }

        // linux
//        contentItem: Text {
//                 leftPadding: 0
//                 rightPadding: comboBox.indicator.width + comboBox.spacing

//                 text: comboBox.displayText
//                 font: comboBox.font
//                 color: comboBox.pressed ? "navy" : "black"
//                 verticalAlignment: Text.AlignVCenter
//                 elide: Text.ElideRight
//             }

        // linux
    }
}
