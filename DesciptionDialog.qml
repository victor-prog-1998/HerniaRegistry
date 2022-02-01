import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3

import "Properties.js" as Properties
import QtQuick.Layouts 1.3


Dialog{
    id: descriptionDialog
    property int imageIndex
    property alias textArea: textArea
    property alias image: image

    width: column.width + 40
    height: column.height + 40
    onVisibleChanged: {
        if(visible)
        {
            descriptionDialog.width = column.width + 40;
            descriptionDialog.height = column.height + 40;
        }

        else
            image.source = ""; // Иначе картинка, полученная из провайдера, не обновляется
                                // (когда ссылка на нее совпадает со ссылкой на старую)
    }



    contentItem: Rectangle{
        id: contentRect
        anchors.fill: parent
        BackgroundGradient{
            anchors.fill: parent
        }

        ColumnLayout{
            id: column
            anchors.centerIn: parent
            spacing: 20

            Image{
                id: image
                property int dispHeight: 0
                cache: false

                fillMode: Image.PreserveAspectFit
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: Math.min(sourceSize.height, Screen.height / 2)
                Layout.preferredWidth: sourceSize.width * (Layout.preferredHeight / sourceSize.height); // пропорция


//                onStatusChanged: {
//                    if(status == Image.Ready)
//                    {
//                        dispHeight = Math.min(sourceSize.height, Screen.height / 2)
//                        console.log(dispHeight);
//                    }

//                }



                //Layout.maximumHeight: image.height * image.scale
                //Layout.maximumWidth: image.width * image.scale

                //Layout.fillHeight: true
                //Layout.fillWidth: true
//                scale: {
//                    var maxHeight = Screen.height / 2
//                    if(image.height < maxHeight)
//                        return 1;
//                    else
//                        return maxHeight / image.height;    // < 1
//                }


            }



            TextAreaWithLabel{
                id: textArea
                //label.visible: false
                area.implicitHeight: 100
                Layout.minimumWidth: 300
                Layout.maximumWidth: 400
                Layout.alignment: Qt.AlignHCenter
            }

            Row{
                Layout.alignment: Qt.AlignHCenter
                spacing: 20
                CustomButton{
                    text: "Отмена"
                    color: Properties.buttonColor;
                    hoverColor: Properties.buttonHoverColor;
                    font.pixelSize: Properties.buttonFontPixelSize;
                    rectangle.implicitHeight: 40
                    rectangle.implicitWidth: 100
                    onClicked: {
                        reject();
                    }
                }
                CustomButton{
                    text: "Сохранить"
                    color: Properties.buttonColor;
                    hoverColor: Properties.buttonHoverColor;
                    font.pixelSize: Properties.buttonFontPixelSize;
                    rectangle.implicitHeight: 40
                    rectangle.implicitWidth: 100
                    onClicked: {
                        accept();
                    }
                }
            }
        }


    }
}
