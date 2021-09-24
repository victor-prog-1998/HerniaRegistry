import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

ColumnLayout{
    id: root
    spacing: 10
    property alias checkBox: checkBox
    property alias hernialRingWidthField: hernialRingWidthField
    property alias hernialSacWidthField: hernialSacWidthField
    property alias hernialSacLengthField: hernialSacLengthField

    function isReady()
    {
        return(!hernialRingWidthField.isEmpty() && !hernialSacWidthField.isEmpty() && !hernialSacLengthField.isEmpty());
    }

    function isChecked()
    {
        return checkBox.checked;
    }

    function reset()
    {
        checkBox.checked = false;
        hernialRingWidthField.reset();
        hernialSacWidthField.reset();
        hernialSacLengthField.reset();
    }

    function checkFields()
    {
        var ok = true;
        if(!myFunctions.checkNum(hernialRingWidthField.field.text, false))
        {
            hernialRingWidthField.setIncorrectState("Укажите ширину корректно!");
            ok = false;
        }
        else hernialRingWidthField.setNormalState();

        if(!myFunctions.checkNum(hernialSacWidthField.field.text, false))
        {
            hernialSacWidthField.setIncorrectState("Укажите ширину корректно!");
            ok = false;
        }
        else hernialSacWidthField.setNormalState();

        if(!myFunctions.checkNum(hernialSacLengthField.field.text, false))
        {
            hernialSacLengthField.setIncorrectState("Укажите длину корректно!");
            ok = false;
        }
        else hernialSacLengthField.setNormalState();


        return ok;
    }

    CheckBox{
        id: checkBox
        font.pixelSize: 16
    }
    ColumnLayout{
        id: fieldsLayout
        spacing: 10
        width: parent.width
        visible: checkBox.checked
        Behavior on visible{
            AppearanceAnimation{
                target: fieldsLayout
            }
        }
        TextFieldWithLabel{
            id: hernialRingWidthField
            label.text: "Ширина грыжевых ворот (см)" + Properties.redPointer;
            Layout.minimumWidth: 320
            field.implicitHeight: 40
        }
        TextFieldWithLabel{
            id: hernialSacWidthField
            label.text: "Ширина грыжевого мешка (см)" + Properties.redPointer;
            Layout.minimumWidth: 320
            field.implicitHeight: 40
        }
        TextFieldWithLabel{
            id: hernialSacLengthField
            label.text: "Длина грыжевого мешка (см)" + Properties.redPointer;
            Layout.minimumWidth: 320
            field.implicitHeight: 40
        }
    }
}
