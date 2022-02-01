import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    signal authClicked(string login, string password)
    signal registrationClicked();

//    property real windowWidth: 600
//    property real windowHeight: 400

    BackgroundGradient{
        anchors.fill: parent
    }

    function clearFields()
    {
        loginField.clear();
        passwordField.clear();
    }

    ColumnLayout{

        anchors.centerIn: parent
        anchors.margins: 15
        spacing: 15
        width: parent.width / 2
        height: parent.height / 3
        Label{
            text: "Авторизация"
            font.pixelSize: 20
            font.bold: true

            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignCenter

            Layout.minimumWidth: 200
            Layout.maximumWidth: 400

//            Layout.minimumHeight: 30
//            Layout.maximumHeight: 70
//            Layout.fillHeight: true
        }
        CustomTextField{
            id: loginField
            font.pixelSize: 18
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignCenter

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            selectByMouse: true
            placeholderText: "Введите логин"
            horizontalAlignment: TextInput.AlignHCenter
        }
        CustomTextField{
            id: passwordField
            font.pixelSize: 18
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignCenter

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            selectByMouse: true
            placeholderText: "Введите пароль"
            echoMode: TextField.Password
            horizontalAlignment: TextInput.AlignHCenter
        }
        CustomButton{
            text: "Войти"
            onClicked: authClicked(loginField.text, passwordField.text)
            enabled: ((loginField.text != "")&&(passwordField.text != ""))

            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignCenter

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            color: Properties.buttonColor;
            hoverColor: Properties.buttonHoverColor;
            font.pixelSize: Properties.buttonFontPixelSize;
        }
        CustomButton{
            text: "Регистрация"
            onClicked: registrationClicked();
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumWidth: 400
            Layout.alignment: Qt.AlignCenter

            Layout.minimumHeight: 30
            Layout.maximumHeight: 70
            Layout.fillHeight: true

            color: "#e3e03d"
            hoverColor: "#c9c72c"
            font.pixelSize: Properties.buttonFontPixelSize
        }
    }
}
