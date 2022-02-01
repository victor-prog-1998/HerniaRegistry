import QtQuick 2.0


Rectangle{
    radius: 5
    height: 70
    color: "white"

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        spacing: 5
        Row{
            spacing: 10
            Text{
                font.pixelSize: 14
                font.bold: true
                color: "navy"
                text: "Пол"
            }
            Text{
                font.pixelSize: 14
                text: modelData.sex
            }

        }
        Row{
            spacing: 10
            Text{
                font.pixelSize: 14
                font.bold: true
                color: "darkgreen"
                text: "Дата рождения"
            }
            Text{
                font.pixelSize: 14
                text: modelData.birthDate
            }

        }
        Row{
            spacing: 10
            Text{
                font.pixelSize: 14
                font.bold: true
                color: "darkred"
                text: "Регион"
            }
            Text{
                font.pixelSize: 14
                text: modelData.region
            }

        }
    }

}
