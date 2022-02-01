import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    signal userRegistrationClicked();
    signal doctorRegistrationClicked();
    signal backClicked();

//    property real windowWidth: 400
//    property real windowHeight: 200

    BackgroundGradient{
        anchors.fill: parent
    }

    header: ProgramHeader{
                HeaderButton{
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    onClicked: backClicked();
                }
    }

    ColumnLayout{


        anchors.centerIn: parent
        anchors.margins: 15
        spacing: 15
        width: parent.width / 2
        height: parent.height / 5
        Label{
            text: "Тип пользователя"
            font.pixelSize: 20
            font.bold: true

            horizontalAlignment: Text.AlignHCenter

            Layout.alignment: Qt.AlignCenter
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
        }
        CustomButton{
            text: "Врач"
            onClicked: doctorRegistrationClicked();

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            color: Properties.buttonColor;
            hoverColor: Properties.buttonHoverColor;
            font.pixelSize: Properties.buttonFontPixelSize;

        }
        CustomButton{
            text: "Рядовой пользователь"
            onClicked: userRegistrationClicked();

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            color: Properties.buttonColor;
            hoverColor: Properties.buttonHoverColor;
            font.pixelSize: Properties.buttonFontPixelSize;

        }

    }
}
