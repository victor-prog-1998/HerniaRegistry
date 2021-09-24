import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 2.2
import "Properties.js" as Properties

Page{
    id: root
    signal exitClicked();
    header:  ProgramHeader{
                HeaderButton{
                    id: exitButton
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    text: "Назад"
                    onClicked: {

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

    function findDistribution(cardIdList, feature)
    {
        var distributionList = (feature === "По полу") ? dbWorker.sexDistribution(cardIdList) :
                               (feature === "По регионам") ? dbWorker.regionsDistribution(cardIdList) : [];
        pageTitle.text = "Распределение " + feature.toLowerCase();

        for(var i = 0; i < distributionList.length; ++i)
        {
            pieSeries.append(distributionList[i].label, distributionList[i].count)

            var legengObject = {};
            legengObject.col = pieSeries.at(i).color.toString();
            legengObject.label = distributionList[i].label;
            legengObject.patientsCount = distributionList[i].count;
            legengObject.percent = distributionList[i].percent;
            listModel.append(legengObject);
        }

    }

    ListModel{
        id: listModel
    }

    ListView{
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: chartView.right
        anchors.margins: 20
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

    ChartView{
        id: chartView
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width * 0.6
        legend.visible: false

        PieSeries{
            id: pieSeries
            size: 0.9

            onSliceAdded: {
                slice.color = Qt.rgba(Math.random(), Math.random(), Math.random());
//                var hue = (pieSeries.count - 1) * 0.02;
//                slice.color = Qt.hsva(hue,1,1);
                slice.explodeDistanceFactor = 0.02;
            }
            onHovered: {
                slice.exploded = state
                if(state)
                    chartView.ToolTip.show(slice.label);
                else
                    chartView.ToolTip.hide();

            }
        }
    }

    CustomButton{
        text: "Другие цвета"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 20
        rectangle.radius: height / 2
        rectangle.implicitHeight: 40
        color: Properties.buttonColor
        hoverColor: Properties.buttonHoverColor
        font.pixelSize: Properties.buttonFontPixelSize
        onClicked: {
            for(var i = 0; i < pieSeries.count; ++i)
            {
                var newColor = Qt.rgba(Math.random(), Math.random(), Math.random());
                pieSeries.at(i).color = newColor;
                listModel.get(i).col = newColor.toString();
            }
        }
    }

}
