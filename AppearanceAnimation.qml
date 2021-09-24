import QtQuick 2.0

PropertyAnimation{
    properties: "scale,opacity"
    from: 0.0
    to: 1.0
    duration: 400
    easing.type: Easing.OutExpo
}
