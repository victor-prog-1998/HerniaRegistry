import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 2.2
import "Properties.js" as Properties

Page{
    id: root
    signal exitClicked();
    property string infoLabelBarDefaultText: "Наведите курсор на столбец для получения информации"
    property string infoLabelPieDefaultText: "Наведите курсор на сектор для получения информации"
    // property string infoLabelPie
    property bool pieSeriesIsAvailable: false
    property int yAxisMax: 0


    header:  ProgramHeader{
                HeaderButton{
                    id: otherColorsButton
                    text: "Другие цвета"
                    anchors.right: exitButton.left
                    anchors.rightMargin: 10
                    width: 150
                    color: "#6ffc95"
                    hoverColor: "#3dd465"
                    onClicked: {
                        for(var i = 0; i < barSeries.count; ++i)
                        {
                            var newColor = Qt.rgba(Math.random(), Math.random(), Math.random());
                            barSeries.at(i).color = newColor;
                            pieSeries.at(i).color = newColor;
                            listModel.get(i).col = newColor.toString();
                        }
                    }
                }

                HeaderButton{
                    id: exitButton
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: "Назад"
                    onClicked: {
                        barSeries.clear();
                        pieSeries.clear();
                        listModel.clear();

                        root.exitClicked();
                    }
                }
                Text{
                    id: pageTitle
                    font.pixelSize: 18
                    //text: "Распределение"
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true
                    width: parent.width / 2
                }
    }


    ListModel{
        id: listModel
    }

    ComboBoxWithLabel{
        id: visualFormComboBox
        visible: pieSeriesIsAvailable
        comboBox.model: ["Круговая диаграмма", "Гистограмма"]
        label.text: "Визуальное представление"
        anchors.left: chartView.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 10
        background.border.width: 1

        comboBox.onActivated: {
            if(comboBox.currentText === "Гистограмма")
                seriesAxisY.gridVisible = true;
            else
                seriesAxisY.gridVisible = false;
        }


    }

    ListView{
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: visualFormComboBox.bottom
        anchors.left: chartView.right
        anchors.topMargin: 10
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        model: listModel
        spacing: 3
        delegate: Component{
            Row{
                spacing: 5
                Rectangle{
                    height: 20
                    width: 40
                    border.width: 1
                    color: col
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    text: (index + 1) + ") " + label + " - " + patientsCount + " (" + percent + "%)";
                }
            }
        }
    }

    Rectangle{
        id: infoRect
        color: "transparent"
        height: 40
        anchors.left: parent.left
        anchors.top: parent.top
        width: chartView.width
        anchors.topMargin: 10

        Label{
            id: infoLabel
            font.pointSize: 12
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 25
            text: root.infoLabelBarDefaultText
        }
    }

    ChartView{
        id: chartView
        anchors.left: parent.left
        anchors.top: infoRect.bottom
        anchors.bottom: parent.bottom
        width: parent.width * 0.6
        legend.visible: false

        // *********************** Круговая диаграмма ***********************************

        PieSeries{
            id: pieSeries
            size: 0.9
            visible: pieSeriesIsAvailable ? (visualFormComboBox.comboBox.currentText === "Круговая диаграмма") : false;

            onSliceAdded: {
                slice.color = Qt.rgba(Math.random(), Math.random(), Math.random());
                slice.explodeDistanceFactor = 0.02;
            }
            onHovered: {

                slice.exploded = state
//                if(state)
//                    chartView.ToolTip.show(slice.label);
//                else
//                    chartView.ToolTip.hide();

                if(state)
                {
                    var idx = getElementIndex(slice.label, slice.value);
                    if(idx > -1)
                        infoLabel.text = getInfo(idx);
                }

                else
                    infoLabel.text = root.infoLabelPieDefaultText;

            }
        }

        // ************************* Гистограмма *****************************************

        BarSeries{
            id: barSeries
            barWidth: 0.8

            visible: pieSeriesIsAvailable ? (visualFormComboBox.comboBox.currentText === "Гистограмма") : true

            axisX: BarCategoryAxis{
                 categories: [" "]
                 visible: parent.visible
            }

            axisY: ValueAxis{
                visible: parent.visible
                id: seriesAxisY
                min: 0
                onMaxChanged: {
                    tickCount = max + 1;
                }
            }

            onHovered: {
                // параметр index в сигнале не поможет понять, какой индекс имеет столбец,
                // так как он возвращает индекс группы (у нас всего одна группа, так что всегда == 0)
                barset.borderColor = "black"
                barset.borderWidth = (status) ? 3 : 0;
                if(status)
                {
                    var idx = getElementIndex(barset.label, barset.at(0));
                    if(idx > -1)
                        infoLabel.text = getInfo(idx);
                }

                else
                    infoLabel.text = root.infoLabelBarDefaultText;
            }

            onBarsetsAdded: {
                var lastIndex = count - 1;
                barSeries.at(lastIndex).color = Qt.rgba(Math.random(), Math.random(), Math.random());
            }

        }
    }

    function findDistribution(cardIdList, feature)
    {

        if(feature === "По полу" || feature === "По регионам")
        {
            pieSeriesIsAvailable = true;
            visualFormComboBox.comboBox.currentIndex = 0;
        }

        else pieSeriesIsAvailable = false;

        var distributionList = [];

        if(feature === "По полу")
            distributionList = dbWorker.sexDistribution(cardIdList);
        else if(feature === "По регионам")
            distributionList = dbWorker.regionsDistribution(cardIdList);
        else if(feature === "По способам оперативного лечения")
            distributionList = dbWorker.operationMethodsDistribution(cardIdList);
        else if(feature === "По техникам натяжных операций")
            distributionList = dbWorker.tensionOperationsDistribution(cardIdList);
        else if(feature === "По техникам ненатяжных операций")
            distributionList = dbWorker.nonTensionOperationsDistribution(cardIdList);
        else if(feature === "По типам сеток")
            distributionList = dbWorker.meshesDistribution(cardIdList);
        else if(feature === "По типам фиксации")
            distributionList = dbWorker.fixationDistribution(cardIdList);
        else if(feature === "По типам такеров")
            distributionList = dbWorker.tuckersDistribution(cardIdList);
        else if(feature === "По операционным осложнениям")
            distributionList = dbWorker.complicationsDistribution(cardIdList);

        var count = cardIdList.length;

        var patientWordEnding = ""; // метод getPatientWordEnding() здесь не подходит
        if((count % 10) == 1)
            patientWordEnding = ((count % 100) == 11) ? "ов" : "а";
        else
            patientWordEnding = "ов";

        pageTitle.text = "Распределение " + feature.toLowerCase() +
                " среди " + count + " пациент" + patientWordEnding;
        var maxValue = 0;

        for(var i = 0; i < distributionList.length; ++i)
        {
            var value = distributionList[i].count;
            if(value > maxValue)
                maxValue = value;

            barSeries.append(distributionList[i].label, [value])
            pieSeries.append(distributionList[i].label, [value])

            pieSeries.at(i).color = barSeries.at(i).color;


            var legengObject = {};
            legengObject.col = barSeries.at(i).color.toString();
            legengObject.label = distributionList[i].label;
            legengObject.patientsCount = distributionList[i].count;
            legengObject.percent = distributionList[i].percent;
            listModel.append(legengObject);
        }

//        for(i = 0; i < 35; ++i) // тест на большое количество столбцов
//        {
//            var v = i + 1;
//            if(v > maxValue)
//                maxValue = v;
//            var lbl = "А";
//            for(var j = 0; j < (i % 10); ++j)
//                lbl += "a";

//            barSeries.append(lbl, [v]);
//            var idx = distributionList.length + i;

//            legengObject = {};
//            legengObject.col = barSeries.at(idx).color.toString();
//            legengObject.label = lbl;
//            legengObject.patientsCount = v
//            legengObject.percent = v * 10
//            listModel.append(legengObject);
//        }

//        root.yAxisMax = maxValue + 1;

//        if(!(pieSeriesIsAvailable && visualFormComboBox.comboBox.currentText === "Круговая диаграмма"))
//            seriesAxisY.max = maxValue + 1;

        seriesAxisY.max = maxValue + 1;
        if(pieSeriesIsAvailable && visualFormComboBox.comboBox.currentText === "Круговая диаграмма")
            seriesAxisY.gridVisible = false;
        else
            seriesAxisY.gridVisible = true;

    }

    function getInfo(index)
    {
        var elem = listModel.get(index);
        var info = elem.label + ": " + elem.patientsCount + " пациент";
        info += getPatientWordEnding(elem.patientsCount);
        info += " (" + elem.percent + " %)";
        return info;
    }

    function getElementIndex(_label, _count)
    {

        console.log("_Label: " + _label);
        console.log("_Count: " + _count);
        for(var i = 0; i < listModel.count; ++i)
        {
            var elem = listModel.get(i);
            if (elem.label === _label && elem.patientsCount === _count)
                return i;
        }
        return -1;
    }

    function getPatientWordEnding(_count) // формирует окончание для слова "пациент" по числу пациентов
    {
        /*
         Сначала смотрим, лежит ли остаток деления на 100 в интервале 11...19
         Если да, то возвращаем окончание "ов"
         Если нет, то смотрим остаток деления на 10:
         0 - "ов"
         1 - ""
         2 - "a"
         3 - "a"
         4 - "a"
         5 - "ов"
         6 - "ов"
         7 - "ов"
         8 - "ов"
         9 - "ов" */

        var mod100 = _count % 100;
        if(mod100 >= 11 && mod100 <= 19)
            return "ов";

        var mod10 = _count % 10;
        switch(mod10)
        {
        case 1:
            return "";
        case 2:
        case 3:
        case 4:
            return "a";
        default:
            return "ов";
        }
    }


}
