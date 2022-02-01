import QtQuick 2.0

Rectangle{
    radius: 10
    height: 125
    color: "white"

    signal openClicked(var cardId)

    Column{
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 8

        Text{
            anchors.left: parent.left
            color: "#004209"
            font.bold: true
            font.pixelSize: 18
            text: modelData.fio
        }

        Row{
            spacing: 10
            Text{
                text: "Дата рождения:"
                color: "navy"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.birthDate
                font.pixelSize: 16
            }
        }
        Row{
            spacing: 10
            Text{
                text: "Пол:"
                color: "navy"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.sex
                font.pixelSize: 16
            }
        }

        Row{
            spacing: 10
            Text{
                text: "Регион:"
                color: "navy"
                font.pixelSize: 16
                font.bold: true
            }
            Text{
                text: modelData.region
                font.pixelSize: 16
            }
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
        color: "#1eff00"
        hoverColor: "#19d600"
        visible: modelData.viewIsAvailable
        onClicked: openClicked(modelData.cardId)
    }



    Row{
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 10
        Text{
            color: "navy"
            font.bold: true
            font.pixelSize: 18
            text: "СНИЛС: "
        }
        Text{
            font.pixelSize: 18
            text: modelData.snils
        }
    }
}
