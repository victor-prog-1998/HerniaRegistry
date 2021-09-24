import QtQuick 2.0

ListView{
    id: root
    signal openCardClicked(var cardId)

    delegate: PatientListDelegate {
        width: parent.width
        onOpenClicked:{
            root.openCardClicked(cardId);
            console.log("open clicked, id: " + cardId);
        }
    }

    spacing: 10
    focus: true
    clip: true

}
