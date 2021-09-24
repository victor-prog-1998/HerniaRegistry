import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties



Page{

    id: root
    signal registrationClicked();
    signal backClicked();
    signal requestSubmitted();
    signal requestFailed();

    function reset()
    {
        fioField.reset();
        birthDateInput.reset();
        experienceField.reset();
        regionComboBox.reset();
        localityField.reset();
        mainWorkField.reset();
        extraWorkField.reset();
        specialityField.reset();
        certificateField.reset();
        emailField.reset();
        loginField.reset();
        passwordField.reset();
        passwordConfirmationField.reset();
    }

    function formIsReady() // проверяет, все ли поля заполнены
    {
        if(fioField.field.text == "") return false;
        if(experienceField.field.text == "") return false;
        if(localityField.field.text == "") return false;
        if(mainWorkField.field.text == "") return false;
        if(specialityField.field.text == "") return false;
        if(certificateField.field.text == "") return false;
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

        // Стаж
        if(myFunctions.checkNum(experienceField.field.text, false))
        {
            experienceField.field.highlight = false;
            experienceField.field.placeholderText = "";
        }
        else
        {
            experienceField.field.highlight = true;
            experienceField.field.placeholderText = "Укажите стаж корректно!";
            experienceField.field.clear();
            ok = false;
        }

        // Населённый пункт
        if(myFunctions.checkPrintableString(localityField.field.text))
        {
            localityField.field.highlight = false;
            localityField.field.placeholderText = "";
        }
        else
        {
            localityField.field.highlight = true;
            localityField.field.placeholderText = "Укажите населенный пункт корректно!";
            localityField.field.clear();
            ok = false;
        }

        // Основное место работы
        if(myFunctions.checkPrintableString(mainWorkField.field.text))
        {
            mainWorkField.field.highlight = false;
            mainWorkField.field.placeholderText = "";
        }
        else
        {
            mainWorkField.field.highlight = true;
            mainWorkField.field.placeholderText = "Укажите место работы корректно!";
            mainWorkField.field.clear();
            ok = false;
        }

        // Дополнительное место работы
        if(extraWorkField.field.text != "")
        {
            if(myFunctions.checkPrintableString(extraWorkField.field.text))
            {
                extraWorkField.field.highlight = false;
                extraWorkField.field.placeholderText = "";
            }
            else
            {
                extraWorkField.field.highlight = true;
                extraWorkField.field.placeholderText = "Укажите место работы корректно!";
                extraWorkField.field.clear();
                ok = false;
            }
        }

        // Специальность
        if(myFunctions.checkPrintableString(specialityField.field.text))
        {
            specialityField.field.highlight = false;
            specialityField.field.placeholderText = "";
        }
        else
        {
            specialityField.field.highlight = true;
            specialityField.field.placeholderText = "Укажите специальность корректно!";
            specialityField.field.clear();
            ok = false;
        }

        // № сертификата
        if(myFunctions.checkNum(certificateField.field.text))
        {
            if(dbWorker.certificateExists(certificateField.field.text))
            {
                certificateField.field.highlight = true;
                certificateField.field.placeholderText = "Врач с таким сертификатом уже есть!";
                certificateField.field.clear();
                ok = false;
            }
            else
            {
                certificateField.field.highlight = false;
                certificateField.field.placeholderText = "";
            }
        }
        else
        {
            if(dbWorker.certificateExists(certificateField.field.text))
            {
                certificateField.field.highlight = true;
                certificateField.field.placeholderText = "Укажите номер корректно!";
                certificateField.field.clear();
                ok = false;
            }
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

    function makeRegistrationRequest()
    {
        /*
            bool DBWorker::makeDoctorRegRequest(const QString &FIO,
                              const QDate &birthDate,
                              int experience,
                              const QString &region,
                              const QString &locality,
                              const QString &work_main,
                              const QString &work_extra,
                              const QString &specialty,
                              const QString &certificate,
                              const QString &email,
                              const QString &login,
                              const QString &password)
          */
        var fio = fioField.field.text;
        var birthDate = birthDateInput.toDateString();
        var experience = Number(experienceField.field.text);
        var region = regionComboBox.comboBox.currentText;
        var locality = localityField.field.text;
        var mainWork = mainWorkField.field.text;
        var extraWork = extraWorkField.field.text;
        var speciality = specialityField.field.text;
        var certificate = certificateField.field.text;
        var email = emailField.field.text;
        var login = loginField.field.text;
        var password = passwordField.field.text;

        return dbWorker.makeDoctorRegRequest(fio,birthDate,experience,region,locality,mainWork,extraWork,speciality,
                                             certificate,email,login,password);
    }



//    property real windowWidth: 600
//    property real windowHeight: 400

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
                //Layout.margins: 30
                anchors.centerIn: parent
                spacing: 10
                width: root.width / 2
                //height: root.height / 1.5


                Label{
                    text: "Регистрация врача"
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
                    //field.placeholderText: root.height + ", " + item.height;
                }

                DateInputWithLabel{
                    id: birthDateInput
                    label.text: "Дата рождения"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                }

                TextFieldWithLabel{
                    id: experienceField
                    label.text: "Стаж"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                ComboBoxWithLabel{
                    id: regionComboBox
                    label.text: "Регион"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    comboBox.model: dbWorker.regions();
                }

                TextFieldWithLabel{
                    id: localityField
                    label.text: "Населённый пункт"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: mainWorkField
                    label.text: "Место работы (основное)"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: extraWorkField
                    label.text: "Место работы (дополнительное)"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: specialityField
                    label.text: "Специальность"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: certificateField
                    label.text: "№ действующего сертификата"
                    Layout.alignment: Qt.AlignCenter
                    Layout.minimumWidth: 320
                    Layout.maximumWidth: 450
                    field.implicitHeight: 40
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
                            if(root.makeRegistrationRequest())
                            {
                                root.reset();
                                requestSubmitted();
                            }
                            else
                                requestFailed();
                        }
                    }
                }

            }
        }
    }


}
