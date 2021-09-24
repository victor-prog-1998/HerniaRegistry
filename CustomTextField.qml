import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

TextField{
    property alias rectangle: rect
    property bool highlight: false
    selectByMouse: true
    background: Rectangle{
        id: rect
        border.color: highlight ? "red" : rect.color;
        border.width: highlight ? 2 : 0;

    }
}


