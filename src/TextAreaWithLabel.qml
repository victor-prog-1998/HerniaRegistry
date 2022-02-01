import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ColumnLayout{
    id: root

    function reset()
    {
        area.clear();
        area.highlight = false;
        area.placeholderText = "";
    }

    Layout.fillWidth: true
    Layout.fillHeight: true
    property alias label: label
    property alias area: area
    property alias rectangle: rect

    Label{
        id: label
        font.pixelSize: 16
        Layout.fillWidth: true
    }
    Flickable{
        Layout.fillWidth: true
        height: area.implicitHeight
        id: flickable
        ScrollBar.vertical: ScrollBar { }
        TextArea.flickable: TextArea{
            id: area
            selectByMouse: true
            Layout.fillWidth: true
            font.pixelSize: 18
            property bool highlight: false

            background: Rectangle{
                id: rect
                border.color: area.highlight ? "red" : rect.color;
                border.width: area.highlight ? 2 : 0;
                radius: 5
            }
            implicitHeight: 100
        }
    }


}

