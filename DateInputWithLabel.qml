import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "Properties.js" as Properties



ColumnLayout{

    function toDateString()
    {
        var month =  monthComboBox.currentIndex + 1;
        if(month < 10) month = '0' + month;
        var day = dayComboBox.currentIndex + 1;
        if(day < 10) day = '0' + day;
        return String( yearComboBox.currentText + '-' + month + '-' + day);
        //return "3 + 2";
    }

    function isSelected()
    {
        return ((dayComboBox.currentIndex != -1)&&(monthComboBox.currentIndex != -1)
                &&(yearComboBox.currentIndex != -1));
    }


    function reset()
    {
        dayComboBox.currentIndex = -1;
        dayComboBox.previousIndex = -1;
        monthComboBox.currentIndex = -1;
        yearComboBox.currentIndex = -1;

    }

    function setDate(date)
    {
        var year = myFunctions.parseYear(date);
        var month = myFunctions.parseMonth(date);
        var day = myFunctions.parseDay(date);
        var currentDate = new Date();
        var yearIndex = currentDate.getFullYear() - year;

        yearComboBox.currentIndex = yearIndex;
        monthComboBox.currentIndex = month - 1;
        dayComboBox.currentIndex = day - 1;
        dayComboBox.previousIndex = day - 1;  // имитация того, что день был выставлен пользователем
    }

//    spacing: 10
//    Layout.margins: 10
    Layout.fillWidth: true
    Layout.fillHeight: true
    property alias label: label
    //property alias field: field

    Label{
        id: label
        font.pixelSize: 16
        Layout.fillWidth: true
//        Layout.fillHeight: true
//        Layout.minimumHeight: 20
//        Layout.maximumHeight: 25
    }
    RowLayout{
        Layout.fillWidth: true
        ComboBox{
            id: dayComboBox
            property int previousIndex: -1
            property bool firstLaunch: true // свойство для корректного отображения комбобокса дня даты при начальном показе
                                                                                                       // элемента ввода даты
            model: {
                var list = [];
                var month = monthComboBox.currentIndex;
                var year = Number(yearComboBox.currentText);
                var count;
                if((month === 3) || (month === 5) || (month === 8) || (month === 10)) // апр, июнь, сент, нояб
                    count = 30;
                else if(month === 1) // февраль
                    count = (year % 4) ? 28 : 29;
                else
                    count = 31;

                for(var i = 0; i < count; ++i)
                    list.push(i + 1);
                return list;
            }
            onActivated: previousIndex = currentIndex; // срабатывает только при выборе значения пользователем


            onModelChanged: {
                if(firstLaunch)
                {
                    firstLaunch = false;
                    currentIndex = -1;
                }
                else
                {
                    console.log("prev: " + previousIndex + ", count: " + count);
                    currentIndex = (previousIndex >= count) ? (count - 1) : previousIndex;
                    previousIndex = currentIndex;
                /* Сигнал срабатывает не только при смене модели, но и при ее первоначальной загрузке.
                   Переменная firstLaunch нужна для проверки, действительно ли модель поменялась или
                   просто была установлена первоначальная модель. Когда сигнал срабатывает при начальной
                   загрузке, то свойство count почему-то равно 0. Поэтому нужно явно устанавливать индекс в 0,
                   иначе в комбобоксе изначально будет выбран пустой элемент (индекс -1)
                */
                }
            }


            currentIndex: -1
            Layout.minimumWidth: 80
            //Layout.maximumWidth: 100
            implicitHeight: 40
//            Layout.minimumHeight: 30
//            Layout.maximumHeight: 70
            Layout.fillWidth: true
            //Layout.fillHeight: true
            font.pixelSize: 18
            background: Rectangle{
                radius: Properties.roundnessRaduis
            }
        }

        ComboBox{
            id: monthComboBox
            model: ["Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"]
            currentIndex: -1
            Layout.minimumWidth: 130
            implicitHeight: 40
//            Layout.minimumHeight: 30
//            Layout.maximumHeight: 70
            Layout.fillWidth: true
            //Layout.fillHeight: true
            font.pixelSize: 18
            background: Rectangle{
                radius: Properties.roundnessRaduis
            }
        }

        ComboBox{
            id: yearComboBox
            model: {
                var list = []
                var date = new Date();
                var currentYear = date.getFullYear();

                for(var i = 0; i < 150; ++i)
                    list.push(currentYear - i);
                return list;
            }

            currentIndex: -1
            Layout.minimumWidth: 95
            implicitHeight: 40
//            Layout.minimumHeight: 30
//            Layout.maximumHeight: 70
            Layout.fillWidth: true
            //Layout.fillHeight: true
            font.pixelSize: 18
            background: Rectangle{
                radius: Properties.roundnessRaduis
            }

        }
    }
}
