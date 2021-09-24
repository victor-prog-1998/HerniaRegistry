import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    id: root
//    onCardIdListChanged: {
//        showDistributionButton.enabled = (cardIdList.length != 0)
//    }

    property var cardIdList: []
    signal exitClicked()
    signal showDistributionClicked(var cardList, string feature)
    header:  ProgramHeader{
                HeaderButton{
                    id: exitButton
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: "Назад"
                    onClicked: {
                        root.exitClicked();
                    }
                }
                Text{
                    font.pixelSize: 18
                    text: "Статистика"
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true
                    width: parent.width / 2
                }
    }
    BackgroundGradient{
        anchors.fill: parent
    }

    ColumnLayout{
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.margins: 10
        spacing: 10

        Label{
            text: "Признаки для поиска пациентов"
            font.pixelSize: 18
        }

        Rectangle{
            color: "white"
            Layout.fillHeight: true
            Layout.fillWidth: true
            StatisticsTreeView{
                anchors.fill: parent
                id: statisticsTreeView
            }
        }



        CustomButton{
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            //Layout.maximumWidth: 450
            rectangle.implicitHeight: 40
            text: "Сбросить признаки"
            font.family: "Arial"
            focusPolicy: Qt.WheelFocus
            color: "#f7786f"
            hoverColor: "#e6655c"
            font.pixelSize: Properties.buttonFontPixelSize;
            rectangle.radius: height / 2
            onClicked: treeViewModel.reset();
        }

        ComboBoxWithLabel{
            id: searchTypeComboBox
            label.text: "Тип поиска";
            Layout.minimumWidth: 320
            comboBox.model: ["Поиск \"И\"", "Поиск \"ИЛИ\""]
            comboBox.currentIndex: 0
        }

        RowLayout{
            spacing: 10
            CustomButton{
                Layout.fillWidth: true
                Layout.minimumWidth: 100
                rectangle.implicitHeight: 40
                text: "Все пациенты"
                color: "#f0ee6e"
                hoverColor: "#dedc52"
                font.pixelSize: Properties.buttonFontPixelSize;
                rectangle.radius: height / 2
                onClicked: {
                    var allCards = dbWorker.getAllCardsForStatistics();
                    patientView.model = allCards;
                    countLabel.text = "Число пациентов в базе: "  + allCards.length;
                    root.cardIdList = []
                    for(var i = 0; i < allCards.length; ++i)
                        cardIdList.push(allCards[i].cardId);
                    cardIdListChanged();                   // нужно вызывать вручную, так как при очистке и добавении элементов
                                                           // в список сигнал не вызывается
                }
            }
            CustomButton{
                Layout.fillWidth: true
                Layout.minimumWidth: 100
                rectangle.implicitHeight: 40
                text: "Найти пациентов"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                rectangle.radius: height / 2
                onClicked: {
                    var strict = searchTypeComboBox.comboBox.currentText == "Поиск \"И\"";
                    var cards = dbWorker.getStatisticsResults(strict);
                    patientView.model = cards
                    countLabel.text = "Найдено пациентов: " + cards.length;
                    root.cardIdList = []
                    for(var i = 0; i < cards.length; ++i)
                        cardIdList.push(cards[i].cardId);
                    cardIdListChanged();
                }
            }
        }

    }

    ColumnLayout{
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.margins: 10
        spacing: 10

        Label{
            id: countLabel
            font.pixelSize: 18
        }

        StatisticsPatientView{
            id: patientView
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        ComboBoxWithLabel{
            id: distributionTypeComboBox
            label.text: "Распределение";
            Layout.minimumWidth: 320
            comboBox.model: ["По полу", "По регионам"]
            comboBox.currentIndex: 0
        }

        CustomButton{
            id: showDistributionButton
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            rectangle.implicitHeight: 40
            text: "Показать распределение"
            font.family: "Arial"
            focusPolicy: Qt.WheelFocus
            color: Properties.buttonColor
            hoverColor: Properties.buttonHoverColor
            font.pixelSize: Properties.buttonFontPixelSize;
            rectangle.radius: height / 2
            enabled: cardIdList.length != 0
            onClicked: {
                showDistributionClicked(root.cardIdList, distributionTypeComboBox.comboBox.currentText)
            }
        }


    }


}
