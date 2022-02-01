import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "Properties.js" as Properties

Item{
    id: root
    property bool editIsAvailable: false
    property int userId: 0
    property int cardId: 0

    function setCardInfo()
    {
        var mainInfo = dbWorker.getMainCardInfo(cardId)

        var region = dbWorker.getRegionByID(mainInfo.regionId)
        var adress = "ул. " + mainInfo.street + ", дом " + mainInfo.house;
        if(mainInfo.flat !== "") adress += ", кв. " + mainInfo.flat;
        var polis = mainInfo.polisType + " № " + mainInfo.polisNumber;

        fioField.dataLabel.text = mainInfo.fio;
        birthDateField.dataLabel.text = mainInfo.birthDate;
        sexField.dataLabel.text = (mainInfo.sex === "М") ? "Мужской" : "Женский";
        phoneField.dataLabel.text = mainInfo.phone;
        regionField.dataLabel.text = region;
        districtField.visible = (mainInfo.district !== "");
        districtField.dataLabel.text = mainInfo.district;
        localityField.dataLabel.text = mainInfo.locality;
        adressField.dataLabel.text = adress;
        passportField.dataLabel.text = mainInfo.passport;
        snilsField.dataLabel.text = mainInfo.snils;
        polisField.dataLabel.text = polis;

        bloodTypeField.visible = (mainInfo.bloodType !== "");
        bloodTypeField.dataLabel.text = mainInfo.bloodType;

        rhesusFactorField.visible = (mainInfo.rhesusFactor !== "");
        rhesusFactorField.dataLabel.text = mainInfo.rhesusFactor;

        weightField.dataLabel.text = mainInfo.weight + " кг";
        heightField.dataLabel.text = mainInfo.height + " см";
        complaintsField.visible = (mainInfo.complaints !== "");
        complaintsField.dataLabel.text = mainInfo.complaints;
    }

    signal editClicked( var cardId)

    onCardIdChanged: {
        if(cardId != 0)
        {
            setCardInfo();
        }
    }

    CustomButton{
        id: editButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        rectangle.implicitHeight: 40
        rectangle.implicitWidth:  120
        text: "Редактировать"
        color: Properties.buttonColor;
        hoverColor: Properties.buttonHoverColor;
        font.pixelSize: Properties.buttonFontPixelSize;
        visible: root.editIsAvailable
        onClicked: editClicked(cardId)
    }

    Rectangle{
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: editIsAvailable ? editButton.bottom : parent.top
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

                    // Заполняем форму просмотра не в самих элементах, а при установке id карты (обработчик сигнала)
                    // иначе qml выдает ошибки в консоли, пытаясь получить доступ к несуществующей карте (но работает все правильно)


                    LabelWithData{
                        id: snilsField
                        titleLabel.text: "Снилс"
                    }

                    LabelWithData{
                        id: fioField
                        titleLabel.text: "ФИО"
                    }

                    LabelWithData{
                        id: birthDateField
                        titleLabel.text: "Дата рождения"
                    }

                    LabelWithData{
                        id: sexField
                        titleLabel.text: "Пол"
                    }

                    LabelWithData{
                        id: phoneField
                        titleLabel.text: "Телефон"
                    }

                    LabelWithData{
                        id: regionField
                        titleLabel.text: "Регион"
                    }

                    LabelWithData{
                        id: districtField
                        titleLabel.text: "Район"
                    }

                    LabelWithData{
                        id: localityField
                        titleLabel.text: "Населенный пункт"
                    }

                    LabelWithData{
                        id: adressField
                        titleLabel.text: "Адрес"
                    }

                    LabelWithData{
                        id: passportField
                        titleLabel.text: "Паспорт"
                    }


                    LabelWithData{
                        id: polisField
                        titleLabel.text: "Полис"
                    }

                    LabelWithData{
                        id: bloodTypeField
                        titleLabel.text: "Группа крови"
                    }

                    LabelWithData{
                        id: rhesusFactorField
                        titleLabel.text: "Резус-фактор"
                    }

                    LabelWithData{
                        id: weightField
                        titleLabel.text: "Вес"
                    }

                    LabelWithData{
                        id: heightField
                        titleLabel.text: "Рост"
                    }

                    LabelWithData{
                        id: complaintsField
                        titleLabel.text: "Жалобы"
                    }
                }
            }
        }



    }

}
