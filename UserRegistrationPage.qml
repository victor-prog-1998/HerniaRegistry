import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    id: root
    signal registrationClicked();
    signal backClicked();
    signal userRegistered();
    signal userRegistrationFailed();

//    property real windowWidth: 600
//    property real windowHeight: 400

    function reset()
    {
        fioField.reset();
        birthDateInput.reset();
        emailField.reset();
        loginField.reset();
        passwordField.reset();
        passwordConfirmationField.reset();






    }

    function formIsReady() // проверяет, все ли поля заполнены
    {
        if(fioField.field.text == "") return false;
        if(emailField.field.text == "") return false;
        if(loginField.field.text == "") return false;
        if(passwordField.field.text == "") return false;
        if(passwordConfirmationField.field.text == "") return false;
        return true;
    }


    function checkFields()
    {
        var ok = true;
        // ФИО
        if(myFunctions.checkFio(fioField.field.text))
        {
            fioField.field.highlight = false;
            fioField.field.placeholderText = "";
        }
        else
        {
            fioField.field.highlight = true;
            fioField.field.placeholderText = "Введите ФИО корректно!";
            fioField.field.clear();
            ok = false;
        }

        // Почта
        if(myFunctions.checkEmail(emailField.field.text))
        {
            emailField.field.highlight = false;
            emailField.field.placeholderText = "";
        }
        else
        {
            emailField.field.highlight = true;
            emailField.field.placeholderText = "Введите e-mail корректно!";
            emailField.field.clear();
            ok = false;
        }

        // Логин
        if(myFunctions.checkLogin(loginField.field.text))
        {
            if(dbWorker.loginExists(loginField.field.text))
            {
                loginField.field.highlight = true;
                loginField.field.placeholderText = "Такой логин уже занят!";
                loginField.field.clear();
                ok = false;
            }
            else
            {
                loginField.field.highlight = false;
                loginField.field.placeholderText = "";
            }
        }
        else
        {
            loginField.field.highlight = true;
            loginField.field.placeholderText = "Недопустимые символы в логине!";
            loginField.field.clear();
            ok = false;
        }

        // Пароль
        if(myFunctions.checkPassword(passwordField.field.text))
        {
            passwordField.field.highlight = false;
            passwordField.field.placeholderText = "";
        }
        else
        {
            passwordField.field.highlight = true;
            passwordField.field.placeholderText = "Недопустимые символы в пароле!";
            passwordField.field.clear();
            ok = false;
        }

        // Подтверждение пароля
        if(passwordConfirmationField.field.text == passwordField.field.text)
        {
            passwordConfirmationField.field.highlight = false;
            passwordConfirmationField.field.placeholderText = "";
        }
        else
        {
            passwordConfirmationField.field.highlight = true;
            passwordConfirmationField.field.placeholderText = "Пароли должны совпадать!";
            passwordConfirmationField.field.clear();
            ok = false;
        }
        return ok;
    }

    function registerUser()
    {
        var fio = fioField.field.text;
        var birthDate = birthDateInput.toDateString();
        var email = emailField.field.text;
        var login = loginField.field.text;
        var password = passwordField.field.text;

        return dbWorker.registerUser(STATUS_ORDINARY_USER, fio, birthDate, email, login, password);

    }


    header: ProgramHeader{
                HeaderButton{
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    onClicked: {
                        root.reset();
                        backClicked();

                    }
                }
    }

    BackgroundGradient{
        anchors.fill: parent
    }

    Item{
        anchors.fill: parent
        anchors.topMargin: 50
        anchors.bottomMargin: 50
        id: item
        ScrollView{
            anchors.fill: parent
            contentHeight: Math.max(parent.height, layout.height)
            contentWidth: Math.max(parent.width, layout.width)

            ColumnLayout{
                id: layout
                anchors.margins: 10
                anchors.centerIn: parent
                spacing: 10
                width: root.width / 2
                //height: root.height / 1.5


                Label{
                    text: "Регистрация рядового пользователя"
                    font.bold: true
                    font.pixelSize: 20
                    Layout.alignment: Qt.AlignCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Item{ // разделитель
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
    //                Layout.minimumHeight: 10
    //                Layout.maximumHeight: 30
                }
                TextFieldWithLabel{
                    id: fioField
                    label.text: "ФИО"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                DateInputWithLabel{
                    id: birthDateInput
                    label.text: "Дата рождения"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                }

                TextFieldWithLabel{
                    id: emailField
                    label.text: "Почта"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: loginField
                    label.text: "Логин"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: passwordField
                    label.text: "Пароль"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                    field.echoMode: TextField.Password
                }

                TextFieldWithLabel{
                    id: passwordConfirmationField
                    label.text: "Подтверждение пароля"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                    field.echoMode: TextField.Password
                }

                Item{ // разделитель
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    height: 10
    //                Layout.minimumHeight: 10
    //                Layout.maximumHeight: 30
                }

                CustomButton{
                    text: "Завершить"
                    Layout.fillWidth: true
                    //Layout.fillHeight: true
                    Layout.minimumWidth: 200
                    Layout.maximumWidth: 450

    //                Layout.minimumHeight: 30
    //                Layout.maximumHeight: 70

                    Layout.alignment: Qt.AlignCenter
                    rectangle.implicitHeight: 40

                    color: Properties.buttonColor;
                    hoverColor: Properties.buttonHoverColor;
                    font.pixelSize: Properties.buttonFontPixelSize;
                    rectangle.radius: height / 2
                    enabled: root.formIsReady();
                    onClicked: {
                        if(root.checkFields())
                        {
                            if(root.registerUser())
                            {
                                root.reset();
                                userRegistered();
                            }
                            else
                                userRegistrationFailed();
                        }

                    }
                }

            }
        }

    }


}
