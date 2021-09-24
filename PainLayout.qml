import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ColumnLayout{
    id: root
    spacing: 10
    property alias checkBox: checkBox
    property alias label: label
    property alias spinBox: spinBox

    function reset()
    {
        checkBox.checked = false;
        spinBox.value = 0;
    }

    CheckBox{
        id: checkBox
        font.pixelSize: 16
    }

    ColumnLayout{
        id: layout
        width: parent.width
        visible: checkBox.checked
        Behavior on visible{
            AppearanceAnimation{
                target: layout
            }
        }
        Label{
            id: label
            font.pixelSize: 16
        }

        RowLayout{
            spacing: 10
            SpinBox{
                id: spinBox
                from: 0
                to: 10
                value: 0
                font.pixelSize: 20
            }
            Label{
                verticalAlignment: Qt.AlignTop
                text: "0 - нет боли, 5 - терпимая боль,<br>10 - нетерпимая боль"
                font.pixelSize: 14
            }
        }
    }
}
