import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3


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

    Label{
        id: label
        font.pixelSize: 16
        Layout.fillWidth: true
    }
    ComboBox{
        id: comboBox
//        model: {
//            var list = [];
//            for(var i = 0; i < 31; ++i)
//                list.push(i + 1);
//            return list;
//        }
        currentIndex: -1
        Layout.minimumWidth: 80
        //Layout.maximumWidth: 100
        implicitHeight: 40
        Layout.fillWidth: true
        font.pixelSize: 18
        background: Rectangle{
            radius: height / 2
        }
    }
}
