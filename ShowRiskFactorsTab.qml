import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "Properties.js" as Properties

Item {
    id: root
    property bool editIsAvailable: false
    property bool riskFactorsArePresent: false
    property int userId: 0
    property int cardId: 0

    function setRiskFactorsInfo()
    {
        root.riskFactorsArePresent = dbWorker.riskFactorsArePresent(cardId);
        if(riskFactorsArePresent)
        {
            var info = dbWorker.getRiskFactorsInfo(cardId);
//            occupationField.visible = true;
//            sportActivitiesField.visible = true;
//            smokingHistoryField.visible = true;
            occupationField.dataLabel.text = dbWorker.getOccupationById(info.occupationId);
            sportActivitiesField.dataLabel.text = dbWorker.getSportActivitiesById(info.sportActivitiesId);
            smokingHistoryField.dataLabel.text = dbWorker.getSmokingHistoriesById(info.smokingHistoryId );

            cigsPerDayField.visible = (info.cigsPerDay !== 0);
            if(info.cigsPerDay !== 0)
                cigsPerDayField.dataLabel.text = info.cigsPerDay;
            yearsOfSmokingField.visible = (info.yearsOfSmoking !== 0);
            if(info.yearsOfSmoking !== 0)
                yearsOfSmokingField.dataLabel.text = info.yearsOfSmoking;

            diabetesILabel.visible = info.diabetesI;
            diabetesIILabel.visible = info.diabetesII;
            hoblLabel.visible = info.hobl;
            hypertensionLabel.visible = info.hypertension;
            heartDiseaseLabel.visible = info.heartDisease;
            kidneyDiseaseLabel.visible = info.kidneyDisease;
            gastritisLabel.visible = info.gastritis;
            aorticAneurysmLabel.visible = info.aorticAneurysm;
            immunosuppressionLabel.visible = info.immunosuppression;
            coagulopathyLabel.visible = info.coagulopathy
            plateletAggregationInhibitorsLabel.visible = info.plateletAggregationInhibitors;

            otherFactorsField.dataLabel.text = info.otherFactors;
            otherFactorsField.visible = (otherFactorsField.dataLabel.text != "");
        }

        else
        {
            cigsPerDayField.visible = false;
            yearsOfSmokingField.visible = false;
            diabetesILabel.visible = false;
            diabetesIILabel.visible = false;
            hoblLabel.visible = false;
            hypertensionLabel.visible = false;
            heartDiseaseLabel.visible = false;
            kidneyDiseaseLabel.visible = false;
            gastritisLabel.visible = false;
            aorticAneurysmLabel.visible = false;
            immunosuppressionLabel.visible = false;
            coagulopathyLabel.visible = false;
            plateletAggregationInhibitorsLabel.visible = false;
            otherFactorsField.visible = false;
        }

    }


    onCardIdChanged: {
        if(cardId != 0)
        {
            setRiskFactorsInfo();
        }
    }

    Label{
        id: missingRiskFactorsLabel
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 20
        text: "Факторы риска не указаны"
        font.bold: true
        font.pixelSize: 20
        visible: !root.riskFactorsArePresent
    }

    CustomButton{
        id: addEditButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        rectangle.implicitHeight: 40
        rectangle.implicitWidth:  120
        text: root.riskFactorsArePresent ? "Редактировать" : "Добавить"
        color: Properties.buttonColor;
        hoverColor: Properties.buttonHoverColor;
        font.pixelSize: Properties.buttonFontPixelSize;
        rectangle.radius: height / 2
        visible: root.editIsAvailable
        onClicked: programRoot.openRiskFactorsPage(cardId, riskFactorsArePresent);
    }

    Rectangle{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: editIsAvailable ? addEditButton.bottom : parent.top
        anchors.margins: 20
        color: "white"
        radius: 5

        Item{
            anchors.fill: parent
            anchors.margins: 10
            id: scrollItem
            ScrollView{
                anchors.fill: parent
                anchors.margins: 20
                contentWidth: Math.max(columnLayout.width, parent.width)
                //contentHeight: columnLayout.height
                contentHeight: Math.max(columnLayout.height, parent.height)
                clip: true



                ColumnLayout{
                    id: columnLayout
                    spacing: 10
                    anchors.left: parent.left
                    width: scrollItem.width

                    LabelWithData{
                        id: occupationField
                        titleLabel.text: "Род деятельности"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: sportActivitiesField
                        titleLabel.text: "Занятия спортом"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: smokingHistoryField
                        titleLabel.text: "Курение"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: cigsPerDayField
                        titleLabel.text: "Сигарет в день"
                    }

                    LabelWithData{
                        id: yearsOfSmokingField
                        titleLabel.text: "Стаж курения в годах"
                    }

                    /*diabetesICheckBox.checked = oldInfo.diabetesI;
        diabetesIICheckBox.checked = oldInfo.diabetesII;
        hoblCheckBox.checked = oldInfo.hobl;
        hypertensionCheckBox.checked = oldInfo.hypertension;
        heartDiseaseCheckBox.checked = oldInfo.heartDisease;
        kidneyDiseaseCheckBox.checked = oldInfo.kidneyDisease;
        gastritisCheckBox.checked = oldInfo.gastritis;
        aorticAneurysmCheckBox.checked = oldInfo.aorticAneurysm;
        immunosuppressionCheckBox.checked = oldInfo.immunosuppression;
        coagulopathyCheckBox.checked = oldInfo.coagulopathy;
        plateletAggregationInhibitorsCheckBox.checked = oldInfo.plateletAggregationInhibitors;*/

                    Label{
                        id: diabetesILabel
                        text: "Сахарный диабет I типа"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: diabetesIILabel
                        text: "Сахарный диабет II типа"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: hoblLabel
                        text: "ХОБЛ"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: hypertensionLabel
                        text: "Гипертония"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: heartDiseaseLabel
                        text: "Сердечное заболевание"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: kidneyDiseaseLabel
                        text: "Заболевание почек"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: gastritisLabel
                        text: "Гастрит / пептическая язва"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: aorticAneurysmLabel
                        text: "Аневризмы аорты"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: immunosuppressionLabel
                        text: "Иммуносупрессия"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: coagulopathyLabel
                        text: "Коагулопатия"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: plateletAggregationInhibitorsLabel
                        text: "Ингибиторы агрегации тромбоцитов"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    LabelWithData{
                        id: otherFactorsField
                        titleLabel.text: "Другие факторы риска"
                    }

                }
            }
        }
    }
}
