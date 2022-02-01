import QtQuick 2.9
import QtQuick.Controls 2.3

Popup{
    id: root
    implicitHeight: contentItem.implicitHeight
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    // focus: true
    padding: 1
    property alias model: listView.model
    signal selected(var data)

    onOpened: {

    }

    contentItem: ListView{
        id: listView
        clip: true
        implicitHeight: contentHeight
        ScrollIndicator.vertical: ScrollIndicator {}

        function processDelegateClicked(data)
        {
            root.selected(data)
            root.close();
        }

        delegate: Component{
            Loader{
                sourceComponent: Component{
                    Rectangle{
                                id: delegateRect
                                border.width: delegateMouseArea.containsMouse ? 1 : 0;
                                color: (index % 2) ? "white" : "#dadada"
                                height: 30
                                width: listView.width
                                implicitHeight: txt.implicitHeight

                                Text{
                                    id: txt
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: 5
                                    text: modelData
                                }
                                MouseArea{
                                    id:delegateMouseArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: {
                                        listView.processDelegateClicked(modelData)
                                    }
                                }
                            }
                }
            }
        }

    }
}


