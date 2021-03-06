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
            ulcerLabel.visible = info.ulcer
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
            ulcerLabel.visible = false;
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
        text: "?????????????? ?????????? ???? ??????????????"
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
        text: root.riskFactorsArePresent ? "??????????????????????????" : "????????????????"
        color: Properties.buttonColor;
        hoverColor: Properties.buttonHoverColor;
        font.pixelSize: Properties.buttonFontPixelSize;
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
                        titleLabel.text: "?????? ????????????????????????"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: sportActivitiesField
                        titleLabel.text: "?????????????? ??????????????"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: smokingHistoryField
                        titleLabel.text: "??????????????"
                        visible: root.riskFactorsArePresent
                    }

                    LabelWithData{
                        id: cigsPerDayField
                        titleLabel.text: "?????????????? ?? ????????"
                    }

                    LabelWithData{
                        id: yearsOfSmokingField
                        titleLabel.text: "???????? ?????????????? ?? ??????????"
                    }



                    Label{
                        id: diabetesILabel
                        text: "???????????????? ???????????? I ????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: diabetesIILabel
                        text: "???????????????? ???????????? II ????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: hoblLabel
                        text: "????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: hypertensionLabel
                        text: "????????????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: heartDiseaseLabel
                        text: "?????????????????? ??????????????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: kidneyDiseaseLabel
                        text: "?????????????????????? ??????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: gastritisLabel
                        text: "??????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: ulcerLabel
                        text: "?????????????????????? ????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: aorticAneurysmLabel
                        text: "?????????????????? ??????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: immunosuppressionLabel
                        text: "??????????????????????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: coagulopathyLabel
                        text: "????????????????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    Label{
                        id: plateletAggregationInhibitorsLabel
                        text: "???????????????????? ?????????????????? ??????????????????????"
                        color: "navy"
                        font.pixelSize: 18
                    }

                    LabelWithData{
                        id: otherFactorsField
                        titleLabel.text: "???????????? ?????????????? ??????????"
                    }

                }
            }
        }
    }
}
