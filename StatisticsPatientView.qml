import QtQuick 2.0

ListView{
    id: root

    delegate:StatisticsPatientDelegate {
        width: parent.width
    }

    spacing: 10
    focus: true
    clip: true
}
