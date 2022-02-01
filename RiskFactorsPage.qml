import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "Properties.js" as Properties

Page{

    id: root
    property int cardId: 0
    property bool editMode: false
    signal exitClicked();
    signal finished();
    BackgroundGradient{
        anchors.fill: parent
    }

    onEditModeChanged: {
        if((editMode == true) && (cardId != 0))
            setOldInfo();
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
            text: editMode ? "Редактирование факторов риска" : "Добавление факторов риска"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            width: parent.width / 2
        }
    }

    function reset()
    {
        occupationComboBox.reset();
        sportActivitiesComboBox.reset();
        smokingHistoryComboBox.reset();
        cigsPerDayField.reset();
        yearsOfSmokingField.reset();
        diabetesICheckBox.checked = false;
        diabetesIICheckBox.checked = false;
        hoblCheckBox.checked = false;
        hypertensionCheckBox.checked = false;
        heartDiseaseCheckBox.checked = false;
        kidneyDiseaseCheckBox.checked = false;
        gastritisCheckBox.checked = false;
        ulcerCheckBox.checked = false;
        aorticAneurysmCheckBox.checked = false;
        immunosuppressionCheckBox.checked = false;
        coagulopathyCheckBox.checked = false;
        plateletAggregationInhibitorsCheckBox.checked = false;
        otherFactorsArea.reset();
        cardId = 0;
        editMode = false;
    }

    function formIsReady()
    {
        return occupationComboBox.isSelected() && sportActivitiesComboBox.isSelected()
                && smokingHistoryComboBox.isSelected();
    }

    function setOldInfo()
    {
        var oldInfo = dbWorker.getRiskFactorsInfo(cardId);

        occupationComboBox.comboBox.currentIndex = oldInfo.occupationId - 1;
        sportActivitiesComboBox.comboBox.currentIndex = oldInfo.sportActivitiesId - 1;
        smokingHistoryComboBox.comboBox.currentIndex = oldInfo.smokingHistoryId - 1;
        cigsPerDayField.field.text = (oldInfo.cigsPerDay === 0) ? "" : oldInfo.cigsPerDay;
        yearsOfSmokingField.field.text = (oldInfo.yearsOfSmoking === 0) ? "" : oldInfo.yearsOfSmoking;

        diabetesICheckBox.checked = oldInfo.diabetesI;
        diabetesIICheckBox.checked = oldInfo.diabetesII;
        hoblCheckBox.checked = oldInfo.hobl;
        hypertensionCheckBox.checked = oldInfo.hypertension;
        heartDiseaseCheckBox.checked = oldInfo.heartDisease;
        kidneyDiseaseCheckBox.checked = oldInfo.kidneyDisease;
        gastritisCheckBox.checked = oldInfo.gastritis;
        ulcerCheckBox.checked = oldInfo.ulcer;
        aorticAneurysmCheckBox.checked = oldInfo.aorticAneurysm;
        immunosuppressionCheckBox.checked = oldInfo.immunosuppression;
        coagulopathyCheckBox.checked = oldInfo.coagulopathy;
        plateletAggregationInhibitorsCheckBox.checked = oldInfo.plateletAggregationInhibitors;

        otherFactorsArea.area.text = oldInfo.otherFactors;

    }

    function checkFields()
    {
        var ok = true;

        // Число сигарет в день
        if(cigsPerDayField.field.text != "")
        {
            if(myFunctions.checkNum(cigsPerDayField.field.text, false))
            {
                cigsPerDayField.field.highlight = false;
                cigsPerDayField.field.placeholderText = "";
            }
            else
            {
                cigsPerDayField.field.highlight = true;
                cigsPerDayField.field.placeholderText = "Укажите число корректно!"
                cigsPerDayField.field.clear();
                ok = false;
            }
        }

        // Стаж курения
        if(yearsOfSmokingField.field.text != "")
        {
            if(myFunctions.checkNum(yearsOfSmokingField.field.text, false))
            {
                yearsOfSmokingField.field.highlight = false;
                yearsOfSmokingField.field.placeholderText = "";
            }
            else
            {
                yearsOfSmokingField.field.highlight = true;
                yearsOfSmokingField.field.placeholderText = "Укажите стаж корректно!";
                yearsOfSmokingField.field.clear();
                ok = false;
            }
        }

        // другие факторы риска
        if(otherFactorsArea.area.text != "")
        {
            if(myFunctions.checkPrintableString(otherFactorsArea.area.text, true))
            {
                otherFactorsArea.area.highlight = false;
                otherFactorsArea.area.placeholderText = "";
            }
            else
            {
                otherFactorsArea.area.highlight = true;
                otherFactorsArea.area.placeholderText = "Введите данные корректно!"
                otherFactorsArea.area.clear();
                ok = false;
            }
        }
        return ok;
    }

    function addRiskFactors()
    {
        /*Q_INVOKABLE bool insertRiskFactors(int cardId, int occupationId, int sportActivitiesId, int smokingHistoryId,
                           const QString& cigsPerDay, const QString& yearsOfSmoking,
                           bool diabetesI, bool diabetesII, bool hobl, bool hypertension,
                           bool heartDisease, bool kidneyDisease, bool gastritis, bool ulcer, bool aorticAneurysm,
                           bool immunosuppression, bool coagulopathy, bool plateletAggregationInhibitors,
                           const QString& otherFactors);*/

        var occupationId = occupationComboBox.comboBox.currentIndex + 1;
        var sportActivitiesId = sportActivitiesComboBox.comboBox.currentIndex + 1;
        var smokingHistoryId = smokingHistoryComboBox.comboBox.currentIndex + 1;
        var cigsPerDay = cigsPerDayField.visible ? cigsPerDayField.field.text : "";
        var yearsOfSmoking = yearsOfSmokingField.visible ? yearsOfSmokingField.field.text : "";
        var diabetesI = diabetesICheckBox.checked;
        var diabetesII = diabetesIICheckBox.checked;
        var hobl = hoblCheckBox.checked;
        var hypertension = hypertensionCheckBox.checked;
        var heartDisease = heartDiseaseCheckBox.checked;
        var kidneyDisease = kidneyDiseaseCheckBox.checked;
        var gastritis = gastritisCheckBox.checked;
        var ulcer = ulcerCheckBox.checked;
        var aorticAneurysm = aorticAneurysmCheckBox.checked;
        var immunosuppression = immunosuppressionCheckBox.checked;
        var coagulopathy = coagulopathyCheckBox.checked;
        var plateletAggregationInhibitors = plateletAggregationInhibitorsCheckBox.checked;
        var otherFactors = otherFactorsArea.area.text;

        return dbWorker.insertRiskFactors(root.cardId, occupationId, sportActivitiesId, smokingHistoryId, cigsPerDay, yearsOfSmoking,
                                          diabetesI, diabetesII, hobl, hypertension, heartDisease, kidneyDisease,
                                          gastritis, ulcer, aorticAneurysm, immunosuppression, coagulopathy,
                                          plateletAggregationInhibitors, otherFactors);
    }

    function editRiskFactors()
    {
        var occupationId = occupationComboBox.comboBox.currentIndex + 1;
        var sportActivitiesId = sportActivitiesComboBox.comboBox.currentIndex + 1;
        var smokingHistoryId = smokingHistoryComboBox.comboBox.currentIndex + 1;
        var cigsPerDay = cigsPerDayField.visible ? cigsPerDayField.field.text : "";
        var yearsOfSmoking = yearsOfSmokingField.visible ? yearsOfSmokingField.field.text : "";
        var diabetesI = diabetesICheckBox.checked;
        var diabetesII = diabetesIICheckBox.checked;
        var hobl = hoblCheckBox.checked;
        var hypertension = hypertensionCheckBox.checked;
        var heartDisease = heartDiseaseCheckBox.checked;
        var kidneyDisease = kidneyDiseaseCheckBox.checked;
        var gastritis = gastritisCheckBox.checked;
        var ulcer = ulcerCheckBox.checked;
        var aorticAneurysm = aorticAneurysmCheckBox.checked;
        var immunosuppression = immunosuppressionCheckBox.checked;
        var coagulopathy = coagulopathyCheckBox.checked;
        var plateletAggregationInhibitors = plateletAggregationInhibitorsCheckBox.checked;
        var otherFactors = otherFactorsArea.area.text;
        return dbWorker.updateRiskFactors(root.cardId, occupationId, sportActivitiesId, smokingHistoryId, cigsPerDay, yearsOfSmoking,
                                          diabetesI, diabetesII, hobl, hypertension, heartDisease, kidneyDisease,
                                          gastritis, ulcer, aorticAneurysm, immunosuppression, coagulopathy,
                                          plateletAggregationInhibitors, otherFactors);
    }

    ScrollView{
        anchors.fill: parent
        anchors.margins: 40
        contentHeight: Math.max(parent.height, layout.height)
        contentWidth: Math.max(parent.width, layout.width)
        clip: true

        ColumnLayout{
            id: layout
            spacing: 10

            width: root.width / 2

            ComboBoxWithLabel{
                id: occupationComboBox
                label.text: "Род деятельности" + Properties.redPointer;
                Layout.minimumWidth: 320
                //Layout.maximumWidth: 450
                comboBox.model: dbWorker.occupations();
            }

            ComboBoxWithLabel{
                id: sportActivitiesComboBox
                label.text: "Занятия спортом" + Properties.redPointer;
                Layout.minimumWidth: 320
                //Layout.maximumWidth: 450
                comboBox.model: dbWorker.sportActivities();
            }

            ComboBoxWithLabel{
                id: smokingHistoryComboBox
                label.text: "Курение" + Properties.redPointer;
                Layout.minimumWidth: 320
                //Layout.maximumWidth: 450
                comboBox.model: dbWorker.smokingHistories();
            }

            ColumnLayout{   // Для курения
                id: smokingLayout
                width: parent.width
                visible: (smokingHistoryComboBox.comboBox.currentText == "Бывший курильщик (бросил >12 мес. назад)") ||
                         (smokingHistoryComboBox.comboBox.currentText == "Постоянный курильщик");
                Behavior on visible{
                    AppearanceAnimation{
                        target: smokingLayout
                    }
                }


                TextFieldWithLabel{
                    id: cigsPerDayField
                    label.text: "Число сигарет в день";
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: yearsOfSmokingField
                    label.text: "Стаж курения (в годах)";
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }
            } // конец колонки для курения

            CheckBox{
                id: diabetesICheckBox
                text: "Сахарный диабет I типа"
                font.pixelSize: 16
            }

            CheckBox{
                id: diabetesIICheckBox
                text: "Сахарный диабет II типа"
                font.pixelSize: 16
            }

            CheckBox{
                id: hoblCheckBox
                text: "ХОБЛ"
                font.pixelSize: 16
            }
            CheckBox{
                id: hypertensionCheckBox
                text: "Гипертония"
                font.pixelSize: 16
            }
            CheckBox{
                id: heartDiseaseCheckBox
                text: "Сердечное заболевание"
                font.pixelSize: 16
            }
            CheckBox{
                id: kidneyDiseaseCheckBox
                text: "Заболевание почек"
                font.pixelSize: 16
            }
            CheckBox{
                id: gastritisCheckBox
                text: "Гастрит"
                font.pixelSize: 16
            }
            CheckBox{
                id: ulcerCheckBox
                text: "Пептическая язва"
                font.pixelSize: 16
            }


            CheckBox{
                id: aorticAneurysmCheckBox
                text: "Аневризмы аорты"
                font.pixelSize: 16
            }

            CheckBox{
                id: immunosuppressionCheckBox
                text: "Иммуносупрессия"
                font.pixelSize: 16
            }

            CheckBox{
                id: coagulopathyCheckBox
                text: "Коагулопатия"
                font.pixelSize: 16
            }

            CheckBox{
                id: plateletAggregationInhibitorsCheckBox
                text: "Ингибиторы агрегации тромбоцитов (ацетилсалициловые<br>
                       кислоты / клопидогрель и т.д.), прекращено в течение 7 дней"
                font.pixelSize: 16
            }

            TextAreaWithLabel{
                id: otherFactorsArea
                label.text: "Другие факторы риска"
                Layout.minimumWidth: 320
                area.implicitHeight: 100
                // rectangle.radius:   cigsPerDayField.field.rectangle.radius;
            }

            Item{
                height: 10
            }

            CustomButton{
                id: finishButton
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                rectangle.implicitHeight: 40
                text: editMode ? "Сохранить изменения" : "Завершить"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                enabled: root.formIsReady();

                onClicked: {
                    if(checkFields())
                    {
                        if(!root.editMode)
                        {
                            if(root.addRiskFactors())
                            {
                                messageDialog.showInformationMessage("Информация", "Факторы риска добавлены в карту");
                                root.reset();
                                root.finished();
                            }
                            else
                            {
                                messageDialog.showCriticalMessage("Ошибка", "Не удалось добавить факторы риска в базу");
                            }
                        }
                        else
                        {
                            if(root.editRiskFactors())
                            {
                                messageDialog.showInformationMessage("Информация", "Изменения сохранены");
                                root.reset();
                                root.finished();
                            }
                            else
                            {
                                messageDialog.showCriticalMessage("Ошибка", "Не удалось сохранить изменения");
                            }
                        }
                    }
                }
            }
        }
    }
    CustomMessageDialog{
        id: messageDialog
    }
}
