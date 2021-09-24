import QtQuick 2.0

Rectangle{
    id: root
    radius: 10
    height: column.implicitHeight + column.anchors.margins * 2
    color: "white"

    signal openButtonClicked(var herniaId)

    Column{
        id: column
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 10

        Text{
            anchors.left: parent.left
            color: "black"
            font.bold: true
            font.pixelSize: 18
            text: modelData.type + " грыжа"
        }

        Row{
            spacing: 10
            Text{
                text: "Тип:"
                color: "navy"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.typeInfo
                font.pixelSize: 16
            }
        }

        Row{
            spacing: 10
            Text{
                text: "Сторона:"
                color: "#19860f"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.side
                font.pixelSize: 16
            }
        }

        Row{
            spacing: 10
            Text{
                text: modelData.operation ? "Операция проводилась" : "Операция не проводилась"
                color: "#751382"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.operationInfo
                font.pixelSize: 16
                visible: modelData.operation
            }
        }



        Text{
            text: "Рецидив"
            color: "#911d0b"
            font.pixelSize: 16
            font.bold: true
            visible: modelData.recurrence
        }




    }

    Row{
        spacing: 10
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        Text{
            font.pixelSize: 14
            font.bold: true
            color: "navy"
            text: "№ по порядку"
        }
        Text{
            font.pixelSize: 14
            text: modelData.number
        }

    }
    CustomButton{
        id: openButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10
        text: "Открыть"
        height: 30
        width: 100
        rectangle.radius: 5
        color: "#1eff00"
        hoverColor: "#19d600"
        onClicked: root.openButtonClicked(modelData.herniaId)
    }

}
