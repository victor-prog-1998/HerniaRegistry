import QtQuick 2.0

Item {

    Timer{
        interval: 1000
        running: true
        repeat: true
        onTriggered: listView.model = dbWorker.getRegistrationRequests();
    }

    ListView{
        id: listView
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10
        focus: true
        clip: true
        delegate: RequestListDelegate {
            width: parent.width
            onAccepted: {
                if(success)
                    msg.showInformationMessage("Информация", "Заявка на регистрацию врача подтверждена");
                else
                    msg.showCriticalMessage("Ошибка", "Не удалось подтвердить заявку на регистрацию");
            }
            onRejected: {
                if(success)
                    msg.showInformationMessage("Информация", "Заявка на регистрацию врача отклонена");
                else
                    msg.showCriticalMessage("Ошибка", "Не удалось отклонить заявку на регистрацию");
            }
        }
    }

    CustomMessageDialog{
        id: msg
        visible: false
    }
}
