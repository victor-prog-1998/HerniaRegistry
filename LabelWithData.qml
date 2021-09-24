import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

// Для отображения информации
// слева - метка с названием признака (ФИО, телефон, почта и т д)
// справа - метка со значением признака

RowLayout{

    property alias titleLabel: titleLabel
    property alias dataLabel: dataLabel
    property int titleLabelWidth: 200

    function clearData()
    {
        dataLabel.text = "";
    }

    spacing: 10
    Label{
        id: titleLabel
        color: "navy"
        font.pixelSize: 18
        font.bold: true
        Layout.minimumWidth: titleLabelWidth
    }
    Label{
        id: dataLabel
        font.pixelSize: 18
        Layout.fillWidth: true
    }
}
