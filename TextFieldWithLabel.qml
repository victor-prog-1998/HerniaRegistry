import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ColumnLayout{
//    spacing: 10
//    Layout.margins: 10

    function setIncorrectState(text)
    {
        field.highlight = true;
        field.placeholderText = text;
        field.clear();
    }

    function setNormalState()
    {
        field.highlight = false;
        field.placeholderText = ""
    }

    function reset()
    {
        field.clear();
        setNormalState();
    }

    function isEmpty()
    {
        return field.text == "";
    }

    Layout.fillWidth: true
    Layout.fillHeight: true
    property alias label: label
    property alias field: field

    Label{
        id: label
        font.pixelSize: 16
        Layout.fillWidth: true
//        Layout.fillHeight: true
//        Layout.minimumHeight: 20
//        Layout.maximumHeight: 25
    }
    CustomTextField{
        id: field
        font.pixelSize: 18
        Layout.fillWidth: true
//        Layout.fillHeight: true
//        Layout.minimumHeight: 30
//        Layout.maximumHeight: 70
        rectangle.radius: height / 2
    }
}
