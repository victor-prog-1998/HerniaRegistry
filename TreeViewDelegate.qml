import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle{
    height: modelData.visible ? 30 : 0
    visible: modelData.visible
    color: "white"
    Rectangle{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "lightgray"
    }

    Row{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15

        Item{
            width: modelData.level * 15
            height: parent.height
        }

        Row{
            visible: modelData.expandable
            spacing: 5
            Image{
                source:  modelData.open ? "qrc:/icons/collapse-icon.png" : "qrc:/icons/expand-icon.png"
                MouseArea{
                    anchors.fill: parent
                    onClicked: modelData.open = !modelData.open
                }
            }
            Text{
                text: modelData.text
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 16
            }
        }


        CheckBox{
            visible: !modelData.expandable
            font.pixelSize: 16
            text: modelData.text
            checked: modelData.checked
            onClicked: modelData.checked = checked
            indicator.implicitWidth: 24
            indicator.implicitHeight: 24
            leftPadding: 0
        }
    }
}


