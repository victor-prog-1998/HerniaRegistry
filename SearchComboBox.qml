import QtQuick 2.9
import QtQuick.Controls 2.3
import "Properties.js" as Properties

Rectangle{
    id: root
    height: 40
    radius: Properties.roundnessRaduis
    color: "white"

    property var model
    property alias font: input.font

    signal clicked()
    signal selected()

    property bool selectedFlag: false
    property int currentIndex: -1
    property string currentText: ""



    onModelChanged: popup.model = model

    //onCurrentIndexChanged: console.log("Current index: " + currentIndex);
    // onCurrentTextChanged: console.log("Current text: " + currentText);

    TextInput{
        id: input
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        leftPadding: 10
        selectByMouse: true
        opacity: enabled ? 1.0 : 0.3;

        onTextEdited: {
            selectedFlag = false;
            input.color = "black"
            input.font.italic = false;
            //console.log("Text edited: " + text)
            popup.model = findStartingWith(text);
            if(!popup.opened) popup.open();
        }
        onEditingFinished: {
            //console.log("Editing finished: " + text)
            if(!selectedFlag)
            {
                var idx = findInModel(text); // вернет индекс строки из модели, если в модели она есть (регистр не важен)
                if(idx === -1)
                {
                    input.color = "red"
                    input.font.italic = true;
                    root.currentText = "";
                }

                else
                {
                    root.currentText = text = model[idx];
                    root.selected();
                }

                popup.close();
                popup.model = root.model;

                root.currentIndex = idx;
            }
        }

    }

    CustomButton{
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 12
        rectangle.implicitHeight: 16
        rectangle.implicitWidth: 16
        onClicked: {
            popup.opened ? popup.close() : popup.open();
        }

        Image {
            anchors.fill: parent
            rotation: 180
            source: "qrc:/icons/combo-box-indicator.png"
            opacity: enabled ? 1.0 : 0.3

            NumberAnimation on rotation {
                id: iconAnimation
                easing.type: Easing.InOutSine
                running: false
                duration: 150
            }
        }
    }

    ListPopup{
        id: popup
        model: root.model
        x: root.x
        y: root.height + 2
        width: root.width
        onOpenedChanged: {
            iconAnimation.to = opened ? 0 : 180;
            iconAnimation.running = true;
        }

        onSelected: {
            selectedFlag = true;
            input.color = "black"
            input.font.italic = false;
            input.text = data;
            model = root.model;
            root.currentIndex = root.model.indexOf(data);
            root.currentText = data;
            root.selected();
        }
    }

    function findStartingWith(leftSubstring)
    {
        var m = [];
        for(var i = 0; i < model.length; ++i)
        {
            var str = model[i];
            if(str.toLowerCase().indexOf(leftSubstring.toLowerCase()) !== -1)
                m.push(str);
        }

        return m;
    }

    function findInModel(str) // CaseInsensitive
    {
        for(var i = 0; i < model.length; ++i)
        {
            if(str.toLowerCase() === model[i].toLowerCase())
                return i;
        }
        return -1;
    }

    function reset()
    {
        root.currentIndex = -1;
        root.currentText = "";
        input.color = "black"
        input.font.italic = false;
        input.text = "";
        popup.model = root.model;
        popup.close();
        // root.model = [];
    }

    function setIndex(index)
    {
        if(index >= root.model.length)
        {
            console.log("SearchComboBox::setIndex: некорретный индекс");
            return;
        }
        var text = root.model[index];
        input.text = text;
        root.currentText = text;
        root.currentIndex = index;
    }

    function find(data)
    {
        return root.model.indexOf(data);
    }

}
