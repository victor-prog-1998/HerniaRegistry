import QtQuick 2.0
import QtQuick.Dialogs 1.2
import "Properties.js" as Properties


Rectangle{
    property alias fileDialog: fileDialog
    height: 200
    color: "white"
    radius: 5
    property alias listModel: listModel

    function addImage(source, description)  // используется на странице грыжи в режиме редактирования
                                            // (для загрузки хранящихся в базе изображений)
                                            // первый аргумент - ссылка на изображение в провайдере
    {
        var item = {};
        item.src = source;
        item.description = description;
        listModel.append(item);
    }

    function reset()
    {
        listModel.clear();
    }

    Rectangle{
        id: addButtonRect
        color: "transparent"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 100

        CustomButton{
            id: addButton
            anchors.centerIn: parent
            rectangle.implicitHeight: 64
            rectangle.implicitWidth: 64
            rectangle.radius: 32
            color: "white"
            hoverColor: "gray"
            rectangle.border.width: 2
            rectangle.border.color: "darkgreen"
            onClicked: fileDialog.visible = true;
            Image{
                anchors.centerIn: parent
                source: "qrc:/icons/add-icon.png"
            }
        }

    }

    Rectangle{
        anchors.left: addButtonRect.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "transparent"

        Flickable{
            id: flickable
            clip: true
            height: parent.height
            anchors.fill: parent
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            contentHeight: row.implicitHeight
            contentWidth: row.implicitWidth
            Row{
                id: row
                spacing: 10
                Repeater{
                    id: repeater
                    model: listModel
                    Rectangle{
                        height: image.height
                        width: image.width
                        MouseArea{
                            id: imageMa
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: {
                                descriptionDialog.textArea.area.text = description
                                descriptionDialog.imageIndex = index
                                descriptionDialog.image.source = src
                                descriptionDialog.visible = true
                            }
                        }


                        Image{
                            id: image
                            height: flickable.height
                            fillMode: Image.PreserveAspectFit
                            //scale: imageMa.containsMouse ? 1.1 : 1;
                            source: src
                            smooth: true
                            cache: false
                        }

                        Rectangle{
                            visible: description == ""
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: 5
                            height: 12
                            radius: 6
                            Text{
                                anchors.centerIn: parent
                                text: "Нет описания"
                                font.pixelSize: 10
                            }
                        }

                        Rectangle{   // add
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.margins: 3
                            width: img.width
                            height: img.height
                            color: "transparent"
                            Image{
                                id: img
                                source: "qrc:/icons/delete-icon.png"
                                scale: ma.containsMouse ? 1.1 : 1
                            }
                            MouseArea{
                                id: ma
                                anchors.fill: parent
                                onClicked: listModel.remove(index)
                                hoverEnabled: true
                            }
                        }
//                        Rectangle{   // description
//                            anchors.left: parent.left
//                            anchors.top: parent.top
//                            anchors.margins: 3
//                            width: descriptionImage.width
//                            height: descriptionImage.height
//                            color: "transparent"
//                            Image{
//                                id: descriptionImage
//                                source: "qrc:/icons/edit-icon.png"
//                                scale: ma2.containsMouse ? 1.1 : 1
//                            }
//                            MouseArea{
//                                id: ma2
//                                anchors.fill: parent
//                                hoverEnabled: true
//                                onClicked: {
//                                    descriptionDialog.textArea.area.text = description
//                                    descriptionDialog.imageIndex = index
//                                    descriptionDialog.visible = true

//                                }
//                            }
//                        }
                    }


                }
            }
        }

    }




    ListModel{
        id: listModel
    }

    DesciptionDialog{
        id: descriptionDialog
        modality: Qt.WindowModal
        visible: false
        title: "Описание изображения"
        onAccepted: {
            listModel.get(imageIndex).description = textArea.area.text;
        }
    }

    FileDialog{
        id: fileDialog
        visible:  false
        modality: Qt.WindowModal
        title: "Select file"
        folder: "C:/Qt/"
        selectMultiple: true
        onAccepted: {

            for(var i = 0; i < fileUrls.length; ++i)
            {
                var item = {};
                item.src = fileUrls[i].toString();
                item.description = "";
                listModel.append(item);
            }

        }
    }
}


