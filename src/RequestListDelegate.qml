import QtQuick 2.0
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

/*
      int doctorId = q.value(0).toInt();
      QString fio = q.value(2).toString();
      QString birthDate = MyFunctions::dateToNormalFormat(q.value(3).toString());
      int experience = q.value(4).toInt();
      QString region = this->getRegionByID(q.value(5).toInt());
      QString locality = q.value(6).toString();
      QString mainWork = q.value(7).toString();
      QString extraWork = q.value(8).toString();
      QString speciality = q.value(9).toString();
      QString certificate = q.value(10).toString();
      QString email = q.value(11).toString();*/

Rectangle{
    color: "white"
    radius: 10
    height: 330
    signal accepted(bool success)
    signal rejected(bool success)
    ColumnLayout{
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        spacing: 5
        property int titleLabelWidth: 300
        LabelWithData{
            titleLabel.text: "ФИО"
            dataLabel.text: modelData.fio
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Дата рождения"
            dataLabel.text: modelData.birthDate
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Опыт работы"
            dataLabel.text: modelData.experience
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Регион"
            dataLabel.text: modelData.region
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Населённый пункт"
            dataLabel.text: modelData.locality
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Место работы (основное)"
            dataLabel.text: modelData.mainWork
            titleLabelWidth: parent.titleLabelWidth
        }
        LabelWithData{
            titleLabel.text: "Место работы (дополнительное)"
            visible: modelData.extraWork !== ""
            dataLabel.text: modelData.extraWork
            titleLabelWidth: parent.titleLabelWidth
        }

        LabelWithData{
            titleLabel.text: "Специальность"
            dataLabel.text: modelData.speciality
            titleLabelWidth: parent.titleLabelWidth
        }

        LabelWithData{
            titleLabel.text: "№ действующего сертификата"
            dataLabel.text: modelData.certificate
            titleLabelWidth: parent.titleLabelWidth
        }

        LabelWithData{
            titleLabel.text: "Почта"
            dataLabel.text: modelData.email
            titleLabelWidth: parent.titleLabelWidth
        }

        Item{
            height: 10
        }

        RowLayout{
            spacing: 15
            CustomButton{
                text: "Отклонить"
                color: "#ff776e"
                hoverColor: "#f55b51"
                font.pixelSize: 16
                rectangle.implicitHeight: 30
                Layout.minimumWidth: 130
                onClicked: rejected(dbWorker.rejectRequest(modelData.doctorId));
            }
            CustomButton{
                text: "Принять"
                color: "#61ff6e"
                hoverColor: "#48db54"
                font.pixelSize: 16
                rectangle.implicitHeight: 30
                Layout.minimumWidth: 130
                onClicked: accepted(dbWorker.acceptRequest(modelData.doctorId));
            }
        }
    }
}
