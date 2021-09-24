import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "Properties.js" as Properties

Page{
    id: root
    property int cardId: 0
    property int herniaId: 0
    property bool editIsAvailable
    signal exitClicked();

    onHerniaIdChanged: {
        if(herniaId != 0)
            root.setHerniaInfo();
    }

    header: ProgramHeader{
                HeaderButton{
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    onClicked: {
                        root.reset();
                        dbWorker.clearImageProvider();
                        exitClicked();
                    }
                }

                Text{
                    font.pixelSize: 18
                    text: "Просмотр информации о грыже"
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.verticalCenter: parent.verticalCenter
                    clip: true
                    width: parent.width / 2
                }
    }

    BackgroundGradient{
        anchors.fill: parent
    }

    function setHerniaInfo()
    {
        var herniaInfo = dbWorker.getHerniaInfo(herniaId);

        herniaTypeLabel.text = herniaInfo.herniaType + " грыжа";

        if(herniaInfo.ventralHerniaType !== "") // Если грыжа вентральная
        {
            ventralHerniaLayout.visible = true;
            ventralHerniaTypeLabel.dataLabel.text = herniaInfo.ventralHerniaType + ", " +
                    herniaInfo.ventralHerniaSubtype;
            ventralWidthLabel.dataLabel.text = herniaInfo.ventralHerniaWidth;
            ventralLengthLabel.dataLabel.text = herniaInfo.ventralHerniaLength;
        }

        else if(herniaInfo.groinHerniaType !== "") // Если грыжа паховая
        {
            groinHerniaLayout.visible = true;
            groinHerniaTypeLabel.dataLabel.text = herniaInfo.groinHerniaType;
            groinHerniaExaminationLabel.dataLabel.text = herniaInfo.groinHerniaExamination;
        }

        sideLabel.dataLabel.text = herniaInfo.herniaSide;
        recurrenceLabel.dataLabel.text = herniaInfo.recurrence ? "Да" : "Нет";

        if(herniaInfo.diagnostics)
        {
            diagnosticsLabel.visible = true;
            if(herniaInfo.clinicalExamination.length !== 0)
            {

                var ceObj = {};
                ceObj.method = "Клиническое обследование";
                ceObj.ringWidth = herniaInfo.clinicalExamination[0];
                ceObj.sacWidth = herniaInfo.clinicalExamination[1];
                ceObj.sacLength = herniaInfo.clinicalExamination[2];
                diagnignosticsModel.append(ceObj)
            }

            if(herniaInfo.uziDorsal.length !== 0)
            {
                var udObj = {};
                udObj.method = "УЗИ (положение на спине)";
                udObj.ringWidth = herniaInfo.uziDorsal[0];
                udObj.sacWidth = herniaInfo.uziDorsal[1];
                udObj.sacLength = herniaInfo.uziDorsal[2];
                diagnignosticsModel.append(udObj)
            }

            if(herniaInfo.uziStanding.length !== 0)
            {
                var usObj = {};
                usObj.method = "УЗИ (положение стоя)";
                usObj.ringWidth = herniaInfo.uziStanding[0];
                usObj.sacWidth = herniaInfo.uziStanding[1];
                usObj.sacLength = herniaInfo.uziStanding[2];
                diagnignosticsModel.append(usObj)
            }

            if(herniaInfo.kt.length !== 0)
            {
                var ktObj = {};
                ktObj.method = "КТ";
                ktObj.ringWidth = herniaInfo.kt[0];
                ktObj.sacWidth = herniaInfo.kt[1];
                ktObj.sacLength = herniaInfo.kt[2];
                diagnignosticsModel.append(ktObj)
            }

            if(herniaInfo.mrt.length !== 0)
            {
                var mrtObj = {};
                mrtObj.method = "МРТ";
                mrtObj.ringWidth = herniaInfo.mrt[0];
                mrtObj.sacWidth = herniaInfo.mrt[1];
                mrtObj.sacLength = herniaInfo.mrt[2];
                diagnignosticsModel.append(mrtObj)
            }
        }

        if((herniaInfo.preoperativePainInRest || herniaInfo.preoperativePainInMotion))
        {
            preoperativePainLabel.dataLabel.text = "Да"
            preoperativePainLayout.visible = true
            preoperativePainInRestLabel.dataLabel.text = herniaInfo.preoperativePainInRest ? ("Да (степень боли: " +
                    herniaInfo.preoperativePainInRestDegree + ")") : "Нет";
            preoperativePainInMotionLabel.dataLabel.text = herniaInfo.preoperativePainInMotion ? ("Да (степень боли: " +
                    herniaInfo.preoperativePainInMotionDegree + ")") : "Нет";
        }
        else
            preoperativePainLabel.dataLabel.text = "Нет";



        if(herniaInfo.operation)
            operationLabel.text = "Операция"; // просто как заголовок раздела
        else
            operationLabel.text = "Операция не проводилась";

        if(herniaInfo.operation)
        {
            operationLayout.visible = true;
            if(herniaInfo.operationSide !== "")
            {
                operationSideLabel.visible = true;
                operationSideLabel.dataLabel.text = herniaInfo.operationSide;
            }

            ringWidthLabel.dataLabel.text = herniaInfo.ringWidth;
            sacWidthLabel.dataLabel.text = herniaInfo.sacWidth;
            sacLengthLabel.dataLabel.text = herniaInfo.sacLength;
            operationMethodLabel.dataLabel.text = herniaInfo.operationMethod;
            operationTechniqueLabel.dataLabel.text = herniaInfo.operationTechnique;
            if(herniaInfo.mesh !== "")
            {
                nonTensionalOperationLayout.visible = true;
                meshLabel.dataLabel.text = herniaInfo.mesh;
                meshWidthLabel.dataLabel.text = herniaInfo.meshWidth;
                meshLengthLabel.dataLabel.text = herniaInfo.meshLength;
                fixationLabel.dataLabel.text = (herniaInfo.fixationType === "") ? "Нет" : "Да";
                if(herniaInfo.fixationType !== "")
                {
                    fixationTypeLabel.visible = true;
                    fixationTypeLabel.dataLabel.text = herniaInfo.fixationType;
                    if(herniaInfo.tuckers !== "")
                    {
                        tuckersTypeLabel.visible = true;
                        tuckersTypeLabel.dataLabel.text = herniaInfo.tuckers;
                    }
                }
                if(herniaInfo.peritoneumClosure !== "")
                {
                    peritoneumClosureLabel.visible = true;
                    peritoneumClosureLabel.dataLabel.text = herniaInfo.peritoneumClosure;
                }
                drainageLabel.dataLabel.text = herniaInfo.drainage ? "Да" : "Нет";
            } // Конец блока для ненатяжного лечения

            intraoperativeComplicationsLabel.dataLabel.text =
                    herniaInfo.intraoperativeComplications ? "Да" : "Нет";

            if(herniaInfo.intraoperativeComplications)
            {
                var intrList = [];
                if(herniaInfo.hemorrhage)
                    intrList.push("Кровотечение");
                if(herniaInfo.nerveDamage)
                    intrList.push("Повреждение нервных стволов");
                if(herniaInfo.cordInjury)
                    intrList.push("Ранение элементов семенного канатика");
                if(herniaInfo.bowelInjury)
                    intrList.push("Повреждение кишки и других внутренних органов");

                for(var i = 0; i < intrList.length; ++i)
                {
                    var intrObj = {};
                    intrObj.complication = intrList[i];
                    intraoperativeComplicationsModel.append(intrObj);
                }
            }

            earlyPostoperativeComplicationsLabel.dataLabel.text =
                    herniaInfo.earlyPostoperativeComplications ? "Да" : "Нет";

            if(herniaInfo.earlyPostoperativeComplications)
            {
                var earlyCompList = [];
                if(herniaInfo.woundInfection)
                    earlyCompList.push("Раневая инфекция (инфильтраты, нагноение)");
                if(herniaInfo.seroma)
                    earlyCompList.push("Серома (размер: " + herniaInfo.seromaSize + ")");
                if(herniaInfo.hematoma)
                    earlyCompList.push("Гематома");
                if(herniaInfo.cordSwelling)
                    earlyCompList.push("Отек семенного канатика и яичка");
                if(herniaInfo.orchiepididymitis)
                    earlyCompList.push("Орхоэпидидимит/орхит");

                for(i = 0; i < earlyCompList.length; ++i)
                {
                    var earlyCompObj = {};
                    earlyCompObj.complication = earlyCompList[i];
                    earlyPostoperativeComplicationsModel.append(earlyCompObj);
                }
            }

            latePostoperativeComplicationsLabel.dataLabel.text =
                    herniaInfo.latePostoperativeComplications ? "Да" : "Нет";

            if(herniaInfo.latePostoperativeComplications)
            {
                var lateCompList = [];
                if(herniaInfo.fistulas)
                    lateCompList.push("Свищи");
                if(herniaInfo.meshRejection)
                    lateCompList.push("Отторжение и сморщивание сетчатого импланта");
                if(herniaInfo.chronicNeuralgia)
                    lateCompList.push("Хроническая пахово-генитальная невралгия");
                if(herniaInfo.testicularAtrophy)
                    lateCompList.push("Атрофия яичка");
                if(herniaInfo.diseaseRecurrence)
                    lateCompList.push("Рецидив заболевания");

                for(i = 0; i < lateCompList.length; ++i)
                {
                    var lateCompObj = {};
                    lateCompObj.complication = lateCompList[i];
                    latePostoperativeComplicationsModel.append(lateCompObj);
                }
            }

            for(i = 0; i < 3; ++i)
            {
                var painObj = {};
                painObj.daysAfterOperation = (i == 0) ? 1 : (i == 1) ? 3 : 7;
                painObj.painIsPresent = (herniaInfo.earlyInRestPain[i] || herniaInfo.earlyInMotionPain[i]);
                painObj.inRest = herniaInfo.earlyInRestPain[i];
                painObj.inRestDegree = herniaInfo.earlyInRestPainDegree[i];
                painObj.inMotion = herniaInfo.earlyInMotionPain[i];
                painObj.inMotionDegree = herniaInfo.earlyInMotionPainDegree[i];
                painObj.analgesics = herniaInfo.earlyPainAnalgesics[i];
                painObj.analgesicsDays = herniaInfo.earlyPainAnalgesicsDays[i];
                painObj.orally = herniaInfo.earlyPainAnalgesicsOrally[i];
                painObj.injections = herniaInfo.earlyPainAnalgesicsInjections[i];
                earlyPainModel.append(painObj);
            }

            nerveInjuryLabel.dataLabel.text = herniaInfo.nerveInjury ? "Да" : "Нет";

            if((herniaInfo.chronicPainInRest || herniaInfo.chronicPainInMotion))
            {
                chronicPainLabel.dataLabel.text = "Да"
                chronicPainLayout.visible = true
                chronicPainInRestLabel.dataLabel.text = herniaInfo.chronicPainInRest ? ("Да (степень боли: " +
                        herniaInfo.chronicPainInRestDegree + ")") : "Нет";
                chronicPainInMotionLabel.dataLabel.text = herniaInfo.chronicPainInMotion ? ("Да (степень боли: " +
                        herniaInfo.chronicPainInMotionDegree + ")") : "Нет";
            }
            else
                chronicPainLabel.dataLabel.text = "Нет";




        }    // Конец блока для операции

        imagesLabel.text = herniaInfo.images ? "Изображения" : "Изображения не добавлены";
        if(herniaInfo.images)
        {
            for(i = 0; i < herniaInfo.imageSources.length; ++i)
            {
                var imageObj = {};
                imageObj.imageSource = herniaInfo.imageSources[i];
                imageObj.description = herniaInfo.imageDescriptions[i];
                imagesModel.append(imageObj);
                console.log("Image source: " + imageObj.imageSource);
            }
        }

     }

    function reset()
    {
        root.herniaId = 0;
        root.cardId  = 0;
        herniaTypeLabel.text = "";

        ventralHerniaLayout.visible = false;
        ventralHerniaTypeLabel.clearData();
        ventralWidthLabel.clearData();
        ventralLengthLabel.clearData();


        groinHerniaLayout.visible = false;
        groinHerniaTypeLabel.clearData();
        groinHerniaExaminationLabel.clearData();

        sideLabel.clearData();
        recurrenceLabel.clearData();

        diagnosticsLabel.visible = false;
        diagnignosticsModel.clear();

        preoperativePainLayout.visible = false;

        operationLayout.visible = false;
        operationSideLabel.visible = false;
        nonTensionalOperationLayout.visible = false;
        fixationTypeLabel.visible = false;
        tuckersTypeLabel.visible = false;
        peritoneumClosureLabel.visible = false;

        intraoperativeComplicationsModel.clear();
        earlyPostoperativeComplicationsModel.clear();
        latePostoperativeComplicationsModel.clear();

        earlyPainModel.clear();
        chronicPainLayout.visible = false;

        imagesModel.clear();
    }

    CustomButton{
        id: editButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        rectangle.implicitHeight: 40
        rectangle.implicitWidth:  160
        text: "Редактировать"
        color: Properties.buttonColor;
        hoverColor: Properties.buttonHoverColor;
        font.pixelSize: Properties.buttonFontPixelSize;
        rectangle.radius: height / 2
        visible: root.editIsAvailable
        onClicked: {
            programRoot.openEditHerniaPage(herniaId, cardId);
        }

    }

    Rectangle{
        anchors.top: editButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        color: "white"
        Item{
            anchors.fill: parent
            anchors.margins: 20

            ScrollView{
                id: scrollView
                clip: true
                anchors.fill: parent
                contentHeight: Math.max(parent.height, layout.height)
                contentWidth: Math.max(parent.width, layout.width)

                ColumnLayout{
                    id: layout
                    anchors.top: parent.top
                    anchors.left: parent.left
                    spacing: 10

                    Label{
                        id: herniaTypeLabel
                        font.pixelSize: 20
                        font.bold: true
                    }



                    ColumnLayout{
                        id: ventralHerniaLayout
                        visible: false
                        width: parent.width
                        LabelWithData{
                            id: ventralHerniaTypeLabel
                            titleLabel.text: "Тип вентральной грыжи"
                        }
                        LabelWithData{
                            id: ventralWidthLabel
                            titleLabel.text: "Ширина"
                        }
                        LabelWithData{
                            id: ventralLengthLabel
                            titleLabel.text: "Длина"
                        }
                    }

                    ColumnLayout{
                        id: groinHerniaLayout
                        visible: false
                        width: parent.width
                        LabelWithData{
                            id: groinHerniaTypeLabel
                            titleLabel.text: "Тип паховой грыжи"
                        }
                        LabelWithData{
                            id: groinHerniaExaminationLabel
                            titleLabel.text: "Результаты исследования"
                        }
                    }

                    LabelWithData{
                        id: sideLabel
                        titleLabel.text: "Сторона"
                    }

                    LabelWithData{
                        id: recurrenceLabel
                        titleLabel.text: "Рецидив"
                    }

                    Label{
                        id: diagnosticsLabel
                        font.pixelSize: 20
                        font.bold: true
                        visible: false
                        text: "Диагностика"
                    }

                    ListModel{
                        id: diagnignosticsModel
                    }

                    Repeater{
                        id: diagnignosticsRepeater
                        //width: parent.width
                        model: diagnignosticsModel
                        delegate: Component{
                            ColumnLayout{
                                Layout.leftMargin: 15
                                //width: diagnignosticsRepeater.width
                                Label{
                                    text: method
                                    font.pixelSize: 18
                                }

                                RowLayout{
                                    Item{
                                        width: 15
                                    }
                                    LabelWithData{
                                        titleLabel.font.bold: false
                                        titleLabel.text:  "Ширина грыжевых ворот"
                                        dataLabel.text: ringWidth
                                    }
                                }

                                RowLayout{
                                    Item{
                                        width: 15
                                    }
                                    LabelWithData{
                                        titleLabel.font.bold: false
                                        titleLabel.text:  "Ширина грыжевого мешка"
                                        dataLabel.text: sacWidth
                                    }
                                }

                                RowLayout{
                                    Item{
                                        width: 15
                                    }
                                    LabelWithData{
                                        titleLabel.font.bold: false
                                        titleLabel.text:  "Длина грыжевого мешка"
                                        dataLabel.text: sacLength
                                    }
                                }

                            }
                        }
                    }


                    LabelWithData{
                        id: preoperativePainLabel
                        titleLabel.text: "Предоперационная боль"
                    }

                    ColumnLayout{
                        id: preoperativePainLayout
                        visible: false
                        Layout.leftMargin: 15
                        LabelWithData{
                            id: preoperativePainInRestLabel
                            titleLabel.text: "Боль в покое"
                        }
                        LabelWithData{
                            id: preoperativePainInMotionLabel
                            titleLabel.text: "Боль в движении"
                        }
                    }








                    Label{
                        id: operationLabel
                        font.pixelSize: 20
                        font.bold: true
                    }

                    ColumnLayout{
                        id: operationLayout
                        visible: false
                        width: parent.width

                        LabelWithData{
                            id: operationSideLabel
                            titleLabel.text: "Сторона операции"
                            visible: false
                        }

                        LabelWithData{
                            id: ringWidthLabel;
                            titleLabel.text: "Ширина грыжевых ворот"
                        }
                        LabelWithData{
                            id: sacWidthLabel;
                            titleLabel.text: "Ширина грыжевого мешка"
                        }
                        LabelWithData{
                            id: sacLengthLabel;
                            titleLabel.text: "Длина грыжевого мешка"
                        }

                        LabelWithData{
                            id: operationMethodLabel
                            titleLabel.text: "Способ лечения"
                        }
                        LabelWithData{
                            id: operationTechniqueLabel
                            titleLabel.text: "Техника лечения"
                        }

                        ColumnLayout{
                            id: nonTensionalOperationLayout
                            visible: false
                            width: parent.width

                            LabelWithData{
                                id: meshLabel
                                titleLabel.text: "Сетка"
                            }
                            LabelWithData{
                                id: meshWidthLabel
                                titleLabel.text: "Ширина сетки"
                            }
                            LabelWithData{
                                id: meshLengthLabel
                                titleLabel.text: "Длина сетки"
                            }
                            LabelWithData{
                                id: fixationLabel
                                titleLabel.text: "Фиксация"
                            }

                            LabelWithData{
                                id: fixationTypeLabel
                                visible: false
                                titleLabel.text: "Тип фиксации"
                            }

                            LabelWithData{
                                id: tuckersTypeLabel
                                visible: false
                                titleLabel.text: "Тип такеров"
                            }

                            LabelWithData{
                                id: peritoneumClosureLabel
                                visible: false
                                titleLabel.text: "Закрытие брюшины"
                            }

                            LabelWithData{
                                id: drainageLabel
                                titleLabel.text: "Дренаж"
                            }

                        }   // Конец компоновки для ненатяжного лечения

                        LabelWithData{
                            id: intraoperativeComplicationsLabel
                            titleLabel.text: "Интраоперационные осложнения"
                        }

                        ListModel{
                            id: intraoperativeComplicationsModel
                        }

                        Repeater{
                            model: intraoperativeComplicationsModel
                            delegate: Component{
                                ColumnLayout{
                                    Layout.leftMargin: 15
                                    Label{
                                        font.pixelSize: 18
                                        text: "- " + complication
                                    }
                                }
                            }
                        }

                        LabelWithData{
                            id: earlyPostoperativeComplicationsLabel
                            titleLabel.text: "Ранние послеоперационные осложнения"
                        }

                        ListModel{
                            id: earlyPostoperativeComplicationsModel
                        }

                        Repeater{
                            model: earlyPostoperativeComplicationsModel
                            delegate: Component{
                                ColumnLayout{
                                    Layout.leftMargin: 15
                                    Label{
                                        font.pixelSize: 18
                                        text: "- " + complication
                                    }
                                }
                            }
                        }

                        LabelWithData{
                            id: latePostoperativeComplicationsLabel
                            titleLabel.text: "Поздние послеоперационные осложнения"
                        }

                        ListModel{
                            id: latePostoperativeComplicationsModel
                        }

                        Repeater{
                            model: latePostoperativeComplicationsModel
                            delegate: Component{
                                ColumnLayout{
                                    Layout.leftMargin: 15
                                    Label{
                                        font.pixelSize: 18
                                        text: "- " + complication
                                    }
                                }
                            }
                        }


                        ListModel{
                            id: earlyPainModel
                        }

                        Repeater{
                            model: earlyPainModel
                            delegate: Component{
                                ColumnLayout{
                                    LabelWithData{
                                        titleLabel.text: "Ранняя боль (" + daysAfterOperation + " cут. после операции)";
                                        dataLabel.text: painIsPresent ? "Да" : "Нет";
                                    }
                                    ColumnLayout{
                                        visible: painIsPresent
                                        Layout.leftMargin: 15
                                        LabelWithData{
                                            titleLabel.text: "Боль в покое"
                                            dataLabel.text: inRest ? ("Да (степень боли: " + inRestDegree + ")") : "Нет";
                                        }
                                        LabelWithData{
                                            titleLabel.text: "Боль в движении"
                                            dataLabel.text: inMotion ? ("Да (степень боли: " + inMotionDegree + ")") : "Нет";
                                        }
                                        LabelWithData{
                                            titleLabel.text: "Приём анальгетиков"
                                            dataLabel.text: {
                                                if(analgesics)
                                                {
                                                    var str = "Да (дней приёма: " + analgesicsDays + ", ";
                                                    var x = orally ? "перорально" : "";
                                                    if(injections)
                                                    {
                                                        if(x !== "")
                                                            x += " + ";
                                                        x += "инъекции";
                                                    }
                                                    str += x + ")";
                                                    return str;
                                                }
                                                return "Нет";
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        LabelWithData{
                            id: nerveInjuryLabel
                            titleLabel.text: "Травма нерва"
                        }

                        LabelWithData{
                            id: chronicPainLabel
                            titleLabel.text: "Хроническая послеоперационная боль (⩾ 3 месяцев)"
                        }

                        ColumnLayout{
                            id: chronicPainLayout
                            visible: false
                            Layout.leftMargin: 15
                            LabelWithData{
                                id: chronicPainInRestLabel
                                titleLabel.text: "Боль в покое"
                            }
                            LabelWithData{
                                id: chronicPainInMotionLabel
                                titleLabel.text: "Боль в движении"
                            }
                        }

                    }   // Конец компоновки для операции


                    Label{
                        id: imagesLabel
                        font.pixelSize: 20
                        font.bold: true
                    }

                    ListModel{
                        id: imagesModel
                    }

                    ColumnLayout{
                        Repeater{
                            model: imagesModel
                            delegate: Component{
                                ColumnLayout{
                                    id: imageLayout
                                    Layout.margins: 10
                                    Label{
                                        font.pixelSize: 18
                                        text: (description === "") ? "Описание отсутствует" : description;
                                    }

                                    Image{
                                        id: image
                                        source: imageSource
                                        cache: false  // без этого обновление картинки в провайдере (с той же ссылкой на неё)
                                                      // будет игнорироваться - будет отображаться старая
                                        fillMode: Image.PreserveAspectFit
                                    }
                                }
                            }
                        }
                    }





                }






            }
        }
    }


}
