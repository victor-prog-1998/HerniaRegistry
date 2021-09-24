import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    id: root
    property int userId: 0
    property int cardId: 0
    /* первоначальные значения уникальных данных пациента
     * нужны при проверке существования пациентов с такими данными в базе
     * чтобы проверять только в том случае, если новое значение отличается от исходного */
    property string originalPassport: ""
    property string originalPolisType: ""
    property string originalPolisNumber: ""
    property string originalSnils: ""
    // ***********************************************************************************
    signal changesSaved()
    signal exitClicked()

    BackgroundGradient{
        anchors.fill: parent
    }

    onCardIdChanged: {
        if(cardId != 0)
        {
            // Заполнение формы старыми данными и инициализация свойств уникальных данных пациента
            // фио др пол телефон регион район нас.пункт улица дом квартира паспорт снилс полис кровь вес рост жалобы
            /*

        Q_INVOKABLE bool insertPatientCard(int userID, const QString& fio, const QDate& birthDate, const QString& sex,
                               const QString& phone, const QString& region, const QString& district,
                               const QString& locality, const QString& street, const QString& house, const QString& flat,
                               const QString& passport, const QString& snils,
                               const QString& polisType, const QString& polisNumber, const QString& bloodType,
                               const QString& rhesusFactor, const QString& weight, const QString& height,
                               const QString& complaints);

              */

            var mainInfo = dbWorker.getMainCardInfo(cardId);
            var fio = mainInfo.fio.split(' ');
            surnameField.field.text = fio[0];
            nameField.field.text = fio[1];
            patronymicField.field.text = fio[2];

            birthDateInput.setDate(mainInfo.birthDate);
            (mainInfo.sex === "М") ? (maleRadioButton.checked = true) : (femaleRadioButton.checked = true);
            phoneField.field.text = mainInfo.phone;
            regionComboBox.comboBox.currentIndex = mainInfo.regionId - 1;
            districtField.field.text = mainInfo.district;
            localityField.field.text = mainInfo.locality;
            streetField.field.text = mainInfo.street;
            houseField.field.text = mainInfo.house;
            flatField.field.text = mainInfo.flat;
            passportField.field.text = root.originalPassport = mainInfo.passport;
            snilsField.field.text = root.originalSnils = mainInfo.snils;
            originalPolisType = mainInfo.polisType;
            (mainInfo.polisType === "ОМС") ? (omsRadioButton.checked = true) : (dmsRadioButton.checked = true);
            polisField.field.text = root.originalPolisNumber = mainInfo.polisNumber;
            (mainInfo.bloodType === "I") ? (group1RadioButton.checked = true) : (mainInfo.bloodType === "II") ?
                                               (group2RadioButton.checked = true) : (mainInfo.bloodType === "III") ?
                                                   (group3RadioButton.checked = true) : (group4RadioButton.checked = true);
            (mainInfo.rhesusFactor === "+") ? (rhPlusRadioButton.checked = true) : (rhMinusRadioButton.checked = true);
            weightField.field.text = mainInfo.weight;
            heightField.field.text = mainInfo.height;
            complaintsArea.area.text = mainInfo.complaints;

        }
    }

    header: ProgramHeader{
        HeaderButton{
            anchors.right: parent.right
            anchors.rightMargin: 10
            text: "Назад"
            onClicked: {
                root.reset();
                exitClicked();
            }
        }
        Text{
            font.pixelSize: 18
            text: "Редактирование основной информации "
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            width: parent.width / 2
        }
    }

    function reset()
    {
        nameField.reset();
        surnameField.reset();
        patronymicField.reset();
        birthDateInput.reset();
        sexGroupBox.reset();
        phoneField.reset();
        regionComboBox.reset();
        districtField.reset();
        localityField.reset();
        streetField.reset();
        houseField.reset();
        flatField.reset();
        passportField.reset();
        snilsField.reset();
        polisTypeGroupBox.reset();
        polisField.reset();
        bloodTypeGroupBox.reset();
        rhesusGroupBox.reset();
        weightField.reset();
        heightField.reset();
        complaintsArea.reset();

        root.originalPassport = 0;
        root.originalPolisType = 0;
        root.originalPolisNumber = 0;
        root.originalSnils = 0;
        root.cardId = 0;
    }

    function cardIsReady()
    { // фио др пол телефон регион город улица дом паспорт снилс полис кровь вес рост
        if(surnameField.field.text == "") return false;
        if(nameField.field.text == "") return false;
        if(patronymicField.field.text == "") return false;
        if(!birthDateInput.isSelected()) return false;
        if(!sexGroupBox.isSelected()) return false;
        if(phoneField.field.text.length < Properties.phoneNumberLength) return false;
        if(!regionComboBox.isSelected()) return false;
        if(localityField.field.text == "") return false;
        if(streetField.field.text == "") return false;
        if(houseField.field.text == "") return false;
        if(passportField.field.text.length < Properties.passportLength) return false;
        if(snilsField.field.text.length < Properties.snilsLength) return false;
        if(!polisTypeGroupBox.isSelected()) return false;
        if(polisField.field.text.length < Properties.polisLength) return false;
        if(!bloodTypeGroupBox.isSelected()) return false;
        if(!rhesusGroupBox.isSelected()) return false;
        if(weightField.field.text == "") return false;
        if(heightField.field.text == "") return false;
        return true;
    }

    function checkFields()
    {
        // фио район населенный пункт улица дом квартира вес рост жалобы
        // + проверка паспорта полиса и снилса на повтор

        var ok = true;
        // ФИО
        if(myFunctions.checkCapitalizeWord(surnameField.field.text))
        {
            surnameField.field.highlight = false;
            surnameField.field.placeholderText = "";
        }
        else
        {
            surnameField.field.highlight = true;
            surnameField.field.placeholderText = "Укажите фамилию корректно!";
            surnameField.field.clear();
            ok = false;
        }

        if(myFunctions.checkCapitalizeWord(nameField.field.text))
        {
            nameField.field.highlight = false;
            nameField.field.placeholderText = "";
        }
        else
        {
            nameField.field.highlight = true;
            nameField.field.placeholderText = "Укажите имя корректно!";
            nameField.field.clear();
            ok = false;
        }

        if(myFunctions.checkCapitalizeWord(patronymicField.field.text))
        {
            patronymicField.field.highlight = false;
            patronymicField.field.placeholderText = "";
        }
        else
        {
            patronymicField.field.highlight = true;
            patronymicField.field.placeholderText = "Укажите отчество корректно!";
            patronymicField.field.clear();
            ok = false;
        }

        // район
        if(districtField.field.text != "")
        {
            if(myFunctions.checkPrintableString(districtField.field.text))
            {
                districtField.field.highlight = false;
                districtField.field.placeholderText = "";
            }
            else
            {
                districtField.field.highlight = true;
                districtField.field.placeholderText = "Укажите район корректно!";
                districtField.field.clear();
                ok = false;
            }
        }
        // населённый пункт
        if(myFunctions.checkPrintableString(localityField.field.text))
        {
            localityField.field.highlight = false;
            localityField.field.placeholderText = "";
        }
        else
        {
            localityField.field.highlight = true;
            localityField.field.placeholderText = "Укажите населённый пункт корректно!";
            localityField.field.clear();
            ok = false;
        }
        // улица
        if(myFunctions.checkPrintableString(streetField.field.text))
        {
            streetField.field.highlight = false;
            streetField.field.placeholderText = "";
        }
        else
        {
            streetField.field.highlight = true;
            streetField.field.placeholderText = "Укажите улицу корректно!";
            streetField.field.clear();
            ok = false;
        }
        // дом
        if(myFunctions.checkPrintableString(houseField.field.text))
        {
            houseField.field.highlight = false;
            houseField.field.placeholderText = "";
        }
        else
        {
            houseField.field.highlight = true;
            houseField.field.placeholderText = "Укажите дом корректно!";
            houseField.field.clear();
            ok = false;
        }
        if(flatField.field.text != "")
        {
            if(myFunctions.checkNum(flatField.field.text, false))
            {
                flatField.field.highlight = false;
                flatField.field.placeholderText = "";
            }
            else
            {
                flatField.field.highlight = true;
                flatField.field.placeholderText = "Укажите квартиру корректно!";
                flatField.field.clear();
                ok = false;
            }
        }
        // вес
        if(myFunctions.checkNum(weightField.field.text, false))
        {
            weightField.field.highlight = false;
            weightField.field.placeholderText = "";
        }
        else
        {
            weightField.field.highlight = true;
            weightField.field.placeholderText = "Укажите вес корректно!";
            weightField.field.clear();
            ok = false;
        }
        // рост
        if(myFunctions.checkNum(heightField.field.text, false))
        {
            heightField.field.highlight = false;
            heightField.field.placeholderText = "";
        }
        else
        {
            heightField.field.highlight = true;
            heightField.field.placeholderText = "Укажите рост корректно!";
            heightField.field.clear();
            ok = false;
        }

        // жалобы
        if(complaintsArea.area.text != "")
        {
            if(myFunctions.checkPrintableString(complaintsArea.area.text, true))
            {
                complaintsArea.area.highlight = false;
                complaintsArea.area.placeholderText = "";
            }
            else
            {
                complaintsArea.area.highlight = true;
                complaintsArea.area.placeholderText = "Введите жалобы корректно!"
                complaintsArea.area.clear();
                ok = false;
            }
        }

        /* ************* Проверка полей на повтор *******************************
          В полях используется inputMask. Чтобы отобразить сообщение о повторе,
          нужно эту маску временно убрать, а затем снова установить, когда пользователь нажмет на поле
          ввода (сигнал pressed())
          */


        // паспорт
        if((passportField.field.text != root.originalPassport) && (dbWorker.passportExists(passportField.field.text)))
        {
            passportField.field.highlight = true;
            passportField.field.inputMask = "";
            passportField.field.placeholderText = "Пациент с таким паспортом уже есть в базе";
            passportField.field.clear();
            ok = false;
        }
        else
        {
            passportField.field.highlight = false;
            passportField.field.placeholderText = "";
        }

        // снилс
        if((snilsField.field.text != root.originalSnils) && (dbWorker.snilsExists(snilsField.field.text)))
        {
            snilsField.field.highlight = true;
            snilsField.field.inputMask = "";
            snilsField.field.placeholderText = "Пациент с таким снилсом уже есть в базе";
            snilsField.field.clear();
            ok = false;
        }
        else
        {
            snilsField.field.highlight = false;
            snilsField.field.placeholderText = "";
        }

        // полис
        var polisType = omsRadioButton.checked ? "ОМС" : "ДМС";
        if(((polisType !== originalPolisType) || (polisField.field.text != originalPolisNumber))
                && (dbWorker.polisExists(omsRadioButton.checked ? "ОМС" : "ДМС", polisField.field.text)))
        {
            polisField.field.highlight = true;
            polisField.field.inputMask = "";
            polisField.field.placeholderText = "Пациент с таким полисом уже есть в базе";
            polisField.field.clear();
            ok = false;
        }
        else
        {
            polisField.field.highlight = false;
            polisField.field.placeholderText = "";
        }

        return ok;
    }

    function saveChanges()
    {
        // фио др пол телефон регион район нас.пункт улица дом квартира паспорт снилс полис кровь вес рост жалобы
        /*

    Q_INVOKABLE bool updatePatientCard(int cardId, const QString& fio, const QDate& birthDate, const QString& sex,
                           const QString& phone, const QString& region, const QString& district,
                           const QString& locality, const QString& street, const QString& house, const QString& flat,
                           const QString& passport, const QString& snils,
                           const QString& polisType, const QString& polisNumber, const QString& bloodType,
                           const QString& rhesusFactor, const QString& weight, const QString& height,
                           const QString& complaints);

          */
        var fio = surnameField.field.text + " " + nameField.field.text + " " + patronymicField.field.text;
        var birthDate = birthDateInput.toDateString();
        var sex = maleRadioButton.checked ? "Мужской" : "Женский";
        var phone = phoneField.field.text;
        var region = regionComboBox.comboBox.currentText;
        var district = districtField.field.text;
        var locality = localityField.field.text;
        var street = streetField.field.text;
        var house = houseField.field.text;
        var flat = flatField.field.text;
        var passport = passportField.field.text;
        var snils = snilsField.field.text;
        var polisType = omsRadioButton.checked ? "ОМС" : "ДМС";
        var polisNumber = polisField.field.text;
        var bloodType = group1RadioButton.checked ? "I" : group2RadioButton.checked ? "II" :
                        group3RadioButton.checked ? "III" : "IV";
        var rhesus = rhPlusRadioButton.checked ? "Rh+" : "Rh-";
        var weight = weightField.field.text;
        var height_ = heightField.field.text;
        var complaints = complaintsArea.area.text;
        return dbWorker.updatePatientCard(root.cardId, fio, birthDate, sex, phone, region, district, locality,
                                          street, house, flat, passport, snils, polisType, polisNumber,
                                          bloodType, rhesus, weight, height_, complaints);

    }

    ScrollView{
        anchors.fill: parent
        contentHeight: Math.max(parent.height, layout.height)
        contentWidth: Math.max(parent.width, layout.width)
        clip: true

        ColumnLayout{
            id: layout
            spacing: 10
            anchors.left: parent.left
            anchors.leftMargin: 50
            width: root.width / 2

            Item{
                height: 20
            }

            TextFieldWithLabel{
                id: snilsField
                label.text: "СНИЛС" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
                field.inputMask: Properties.snilsInputMask;
                field.onPressed: {
                    if(field.inputMask == "")
                        field.inputMask = Properties.snilsInputMask;
                }
            }

            TextFieldWithLabel{
                id: surnameField
                label.text: "Фамилия" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: nameField
                label.text: "Имя" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: patronymicField
                label.text: "Отчество" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }


            DateInputWithLabel{
                id: birthDateInput
                label.text: "Дата рождения" + Properties.redPointer;

                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
            }

            CustomGroupBox{
                id: sexGroupBox
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                title: "Пол" + Properties.redPointer;
                function isSelected()
                {
                    return ((maleRadioButton.checked) || (femaleRadioButton.checked));
                }
                function reset()
                {
                    maleRadioButton.checked = false;
                    femaleRadioButton.checked = false;
                }

                RowLayout{
                    anchors.fill: parent
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: maleRadioButton
                        text: "Мужской"
                        //checked: true
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: femaleRadioButton
                        text: "Женский"
                        implicitHeight: 16
                    }
                }
            }


            TextFieldWithLabel{
                id: phoneField
                label.text: "Телефон" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
                field.inputMask: Properties.phoneInputMask;
            }

            ComboBoxWithLabel{
                id: regionComboBox
                label.text: "Регион" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                comboBox.model: dbWorker.regions();
            }

            TextFieldWithLabel{
                id: districtField
                label.text: "Район"
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: localityField
                label.text: "Населённый пункт" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: streetField
                label.text: "Улица" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: houseField
                label.text: "Дом" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: flatField
                label.text: "Квартира"
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: passportField
                label.text: "Паспортные данные" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
                field.inputMask: Properties.passportInputMask;
                field.onPressed: {
                    if(field.inputMask == "")
                        field.inputMask = Properties.passportInputMask;
                }
            }





            CustomGroupBox{
                id: polisTypeGroupBox
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                title: "Тип полиса" + Properties.redPointer;
                function isSelected()
                {
                    return((omsRadioButton.checked) ||(dmsRadioButton.checked));
                }
                function reset()
                {
                    omsRadioButton.checked = false;
                    dmsRadioButton.checked = false;
                }

                RowLayout{
                    anchors.fill: parent
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: omsRadioButton
                        text: "ОМС"
                        //checked: true
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: dmsRadioButton
                        text: "ДМС"
                        implicitHeight: 16
                    }
                }
            }

            TextFieldWithLabel{
                id: polisField
                label.text: "Номер полиса (16 цифр)" + Properties.redPointer;
                field.inputMask: Properties.polisInputMask;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
                field.onPressed: {
                    if(field.inputMask == "")
                        field.inputMask = Properties.polisInputMask;
                }
            }

            CustomGroupBox{
                id: bloodTypeGroupBox
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                title: "Группа крови" + Properties.redPointer;
                function isSelected()
                {
                    return ((group1RadioButton.checked) || (group2RadioButton.checked) ||
                            (group3RadioButton.checked) || (group4RadioButton.checked))
                }

                function reset()
                {
                    group1RadioButton.checked = false;
                    group2RadioButton.checked = false;
                    group3RadioButton.checked = false;
                    group4RadioButton.checked = false;
                }

                RowLayout{
                    anchors.fill: parent
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: group1RadioButton
                        text: "I"
                        //checked: true
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: group2RadioButton
                        text: "II"
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: group3RadioButton
                        text: "III"
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: group4RadioButton
                        text: "IV"
                        implicitHeight: 16
                    }
                }
            }

            CustomGroupBox{
                id: rhesusGroupBox
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                title: "Резус фактор" + Properties.redPointer;
                function isSelected()
                {
                    return((rhPlusRadioButton.checked) ||(rhMinusRadioButton.checked));
                }
                function reset()
                {
                    rhPlusRadioButton.checked = false;
                    rhMinusRadioButton.checked = false;
                }

                RowLayout{
                    anchors.fill: parent
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: rhPlusRadioButton
                        text: "Rh+"
                        //checked: true
                        implicitHeight: 16
                    }
                    CustomRadioButton{
                        Layout.fillWidth: true
                        id: rhMinusRadioButton
                        text: "Rh-"
                        implicitHeight: 16
                    }
                }
            }

            TextFieldWithLabel{
                id: weightField
                label.text: "Вес (кг)" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextFieldWithLabel{
                id: heightField
                label.text: "Рост (см)" + Properties.redPointer;
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                field.implicitHeight: 40
            }

            TextAreaWithLabel{
                id: complaintsArea
                label.text: "Жалобы"
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                area.implicitHeight: 100
                rectangle.radius:   nameField.field.rectangle.radius;

            }

            Item{
                height: 10
            }

            CustomButton{
                id: addCardButton
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                rectangle.implicitHeight: 40
                text: "Сохранить изменения"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                rectangle.radius: height / 2
                enabled: root.cardIsReady();

                onClicked: {
                    if(root.checkFields())
                    {
                        if(root.saveChanges())
                        {
                            messageDialog.showInformationMessage("Информация", "Изменения сохранены");
                            root.reset();
                            root.changesSaved();
                        }
                        else
                            messageDialog.showCriticalMessage("Ошибка", "Не удалось сохранить изменения");
                    }
                }

            }

            Item{
                height: 20
            }

        }
    }

    CustomMessageDialog{
        id: messageDialog
    }

}
