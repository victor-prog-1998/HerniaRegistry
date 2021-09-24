import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

ColumnLayout{
    id: root
    spacing: 10
    property string title: ""
    property alias checkBox: earlyPostoperativePainCheckBox
    property alias inRestPain: earlyPostperativeInRestPainLayout
    property alias inMotionPain: earlyPostperativeInMotionPainLayout
    property alias analgesicsCheckBox: analgesicsCheckBox
    property alias analgesicsDaysField: analgesicsDaysField
    property alias analgesicsOrallyCheckBox: analgesicsOrallyCheckBox
    property alias analgesicsInjectionsCheckBox: analgesicsInjectionsCheckBox


    function isReady()
    {
        if(!earlyPostperativeInRestPainLayout.checkBox.checked && !earlyPostperativeInMotionPainLayout.checkBox.checked)
            return false;
        if(analgesicsCheckBox.checked)
        {
            if(analgesicsDaysField.isEmpty()) return false;
            if(!analgesicsInjectionsCheckBox.checked && !analgesicsOrallyCheckBox.checked) return false;
        }
        return true;
    }

    function reset()
    {
        earlyPostoperativePainCheckBox.checked = false;
        earlyPostperativeInRestPainLayout.reset();
        earlyPostperativeInMotionPainLayout.reset();
        analgesicsCheckBox.checked = false;
        analgesicsDaysField.reset();
        analgesicsOrallyCheckBox.checked = false;
        analgesicsInjectionsCheckBox.checked = false;
    }

    function checkAnalgesicsDaysField()
    {
        if(!myFunctions.checkNum(analgesicsDaysField.field.text, false))
        {
            analgesicsDaysField.setIncorrectState("Укажите число корректно!");
            return false;
        }
        analgesicsDaysField.setNormalState();
        return true;
    }


    CheckBox{
        id: earlyPostoperativePainCheckBox
        text: root.title
        font.pixelSize: 16
    }

    ColumnLayout{       // для ранней послеоперационной боли
        id: earlyPostoperativePainLayout
        width: parent.width
        Layout.leftMargin: 30
        visible: earlyPostoperativePainCheckBox.checked
        Behavior on visible {
            AppearanceAnimation{
                target: earlyPostoperativePainLayout
            }
        }
        PainLayout{
            id: earlyPostperativeInRestPainLayout
            width: parent.width
            checkBox.text: "В покое"
            label.text: "Степень боли в покое"
        }

        PainLayout{
            id: earlyPostperativeInMotionPainLayout
            width: parent.width
            checkBox.text: "В движении"
            label.text: "Степень боли в движении"
        }

        CheckBox{
            id: analgesicsCheckBox
            text: "Анальгетики"
            font.pixelSize: 16
        }

            ColumnLayout{  // Для анальгетиков
                id: analgesicsLayout
                width: parent.width
                visible: analgesicsCheckBox.checked
                Behavior on visible {
                    AppearanceAnimation{
                        target: analgesicsLayout
                    }
                }
                TextFieldWithLabel{
                    id: analgesicsDaysField
                    label.text: "Число дней приема" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }

                CheckBox{
                    id: analgesicsOrallyCheckBox
                    text: "Перорально"
                    font.pixelSize: 16
                }

                CheckBox{
                    id: analgesicsInjectionsCheckBox
                    text: "Инъекции"
                    font.pixelSize: 16
                }

            } // конец колонки для анальгетиков

    } // конец колонки для ранней послеоперационной боли
}


