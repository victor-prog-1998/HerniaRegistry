import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import "Properties.js" as Properties

Page{

    id: root
    property int cardId: 0
    property int editHerniaId: 0      // id редактируемой грыжи
    property bool editMode: false
    signal exitClicked();
    signal finished();
    signal editingFinished();

    onVisibleChanged: {
        if(!visible) // обновляем комбобоксы, так как возможно, что в базу были внесены новые типы сеток/фиксаций/такеров
        {
            meshesComboBox.comboBox.model = dbWorker.meshes();
            fixationTypeComboBox.comboBox.model = dbWorker.fixationTypes();
            tuckersComboBox.comboBox.model = dbWorker.tuckers();
        }
    }



    BackgroundGradient{
        anchors.fill: parent
    }

    header: ProgramHeader{
        HeaderButton{
            anchors.right: parent.right
            anchors.rightMargin: 10
            text: "Назад"
            onClicked: {
                root.reset();
                exitClicked();
            }
        }
        Text{
            font.pixelSize: 18
            text: root.editMode ? "Редактирование информации о грыже" : "Добавление грыжи"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.verticalCenter: parent.verticalCenter
            clip: true
            width: parent.width / 2
        }
    }

    function setOldInfo()
    {
        if(root.editMode && (root.editHerniaId != 0))
        {
            // Проверять дочерние элементы на видимость (например, чтобы узнать тип грыжи) здесь бессмысленно,
            // так как используется AppearanceAnimation, и свойство visible
            // становится true только по завершении анимации, а не мгновенно

            var herniaInfo = dbWorker.getHerniaInfo(editHerniaId);

            herniaTypeComboBox.comboBox.currentIndex = herniaTypeComboBox.comboBox.find(herniaInfo.herniaType);
            // Если грыжа вентральная
            if(herniaInfo.ventralHerniaType !== "")
            {
                ventralHerniaTypeComboBox.comboBox.currentIndex =
                        ventralHerniaTypeComboBox.comboBox.find(herniaInfo.ventralHerniaType);
                // тип - срединная
                if(herniaInfo.ventralHerniaType === "Срединная")
                    midlineVentralHerniaTypeComboBox.comboBox.currentIndex =
                            midlineVentralHerniaTypeComboBox.comboBox.find(herniaInfo.ventralHerniaSubtype);
                // тип - латеральная
                else if(herniaInfo.ventralHerniaType === "Латеральная")
                    lateralVentralHerniaTypeComboBox.comboBox.currentIndex =
                            lateralVentralHerniaTypeComboBox.comboBox.find(herniaInfo.ventralHerniaSubtype);

                ventralHerniaWidthComboBox.comboBox.currentIndex =
                        ventralHerniaWidthComboBox.comboBox.find(herniaInfo.ventralHerniaWidth);
                ventralHerniaLengthField.field.text = herniaInfo.ventralHerniaLength;

            }

            // Если грыжа паховая
            else if(herniaInfo.groinHerniaType !== "")
            {
                groinHerniaTypeComboBox.comboBox.currentIndex = groinHerniaTypeComboBox.comboBox.find(herniaInfo.groinHerniaType);
                groinHerniaExaminationComboBox.comboBox.currentIndex =
                        groinHerniaExaminationComboBox.comboBox.find(herniaInfo.groinHerniaExamination)
            }

            herniaSideComboBox.comboBox.currentIndex = herniaSideComboBox.comboBox.find(herniaInfo.herniaSide);
            recurrenceCheckBox.checked = herniaInfo.recurrence;

            if(herniaInfo.diagnostics)
            {
                if(herniaInfo.clinicalExamination.length !== 0)
                {
                    clinicalExaminationLayout.checkBox.checked = true;
                    clinicalExaminationLayout.hernialRingWidthField.field.text =
                            herniaInfo.clinicalExamination[0];
                    clinicalExaminationLayout.hernialSacWidthField.field.text =
                            herniaInfo.clinicalExamination[1];
                    clinicalExaminationLayout.hernialSacLengthField.field.text =
                            herniaInfo.clinicalExamination[2];
                }

                if(herniaInfo.uziDorsal.length !== 0)
                {
                    uziDorsalLayout.checkBox.checked = true;
                    uziDorsalLayout.hernialRingWidthField.field.text =
                            herniaInfo.uziDorsal[0];
                    uziDorsalLayout.hernialSacWidthField.field.text =
                            herniaInfo.uziDorsal[1];
                    uziDorsalLayout.hernialSacLengthField.field.text =
                            herniaInfo.uziDorsal[2];
                }

                if(herniaInfo.uziStanding.length !== 0)
                {
                    uziStandingLayout.checkBox.checked = true;
                    uziStandingLayout.hernialRingWidthField.field.text =
                            herniaInfo.uziStanding[0];
                    uziStandingLayout.hernialSacWidthField.field.text =
                            herniaInfo.uziStanding[1];
                    uziStandingLayout.hernialSacLengthField.field.text =
                            herniaInfo.uziStanding[2];
                }

                if(herniaInfo.kt.length !== 0)
                {
                    ktLayout.checkBox.checked = true;
                    ktLayout.hernialRingWidthField.field.text =
                            herniaInfo.kt[0];
                    ktLayout.hernialSacWidthField.field.text =
                            herniaInfo.kt[1];
                    ktLayout.hernialSacLengthField.field.text =
                            herniaInfo.kt[2];
                }

                if(herniaInfo.mrt.length !== 0)
                {
                    mrtLayout.checkBox.checked = true;
                    mrtLayout.hernialRingWidthField.field.text =
                            herniaInfo.mrt[0];
                    mrtLayout.hernialSacWidthField.field.text =
                            herniaInfo.mrt[1];
                    mrtLayout.hernialSacLengthField.field.text =
                            herniaInfo.mrt[2];
                }
            }

            if(herniaInfo.preoperativePainInRest || herniaInfo.preoperativePainInMotion)
            {
                preoperativePainCheckBox.checked = true;
                if(herniaInfo.preoperativePainInRest)
                {
                    preoperativeInRestPainLayout.checkBox.checked = true;
                    preoperativeInRestPainLayout.spinBox.value = herniaInfo.preoperativePainInRestDegree;
                }
                if(herniaInfo.preoperativePainInMotion)
                {
                    preoperativeInMotionPainLayout.checkBox.checked = true;
                    preoperativeInMotionPainLayout.spinBox.value = herniaInfo.preoperativePainInMotionDegree;
                }
            }

            if(herniaInfo.operation)
            {
                operationCheckBox.checked = true;
                if(herniaInfo.operationSide !== "")
                    operationSideComboBox.comboBox.currentIndex =
                            operationSideComboBox.comboBox.find(herniaInfo.operationSide);

                ringWidthField.field.text = herniaInfo.ringWidth;
                sacWidthField.field.text = herniaInfo.sacWidth;
                sacLengthField.field.text = herniaInfo.sacLength;

                operationTechniqueComboBox.comboBox.currentIndex =
                        operationTechniqueComboBox.comboBox.find(herniaInfo.operationMethod);

                if(herniaInfo.mesh === "")  // Натяжной способ лечения
                    tissueRepairTechniqueTechniqueComboBox.comboBox.currentIndex =
                            tissueRepairTechniqueTechniqueComboBox.comboBox.find(herniaInfo.operationTechnique);

                else   // Ненатяжной способ лечения
                {
                    meshImplantRepairTechniqueComboBox.comboBox.currentIndex =
                            meshImplantRepairTechniqueComboBox.comboBox.find(herniaInfo.operationTechnique);
                    meshesComboBox.comboBox.currentIndex = meshesComboBox.comboBox.find(herniaInfo.mesh);
                    meshWidthField.field.text = herniaInfo.meshWidth;
                    meshLengthField.field.text = herniaInfo.meshLength;

                    if(herniaInfo.fixationType !== "") // Сетка была фиксирована
                    {
                        meshFixationCheckBox.checked = true;
                        fixationTypeComboBox.comboBox.currentIndex =
                                fixationTypeComboBox.comboBox.find(herniaInfo.fixationType);

                        if(herniaInfo.tuckers !== "") // Тип фиксации - такеры
                            tuckersComboBox.comboBox.currentIndex = tuckersComboBox.comboBox.find(herniaInfo.tuckers);
                    }

                    if(herniaInfo.peritoneumClosure !== "")
                        peritoneumClosureComboBox.comboBox.currentIndex =
                                peritoneumClosureComboBox.comboBox.find(herniaInfo.peritoneumClosure);
                    drainageCheckBox.checked = herniaInfo.drainage;

                }

                if(herniaInfo.intraoperativeComplications)
                {
                    intraOperativeComplicationsCheckBox.checked = true;
                    hemorrhageCheckBox.checked = herniaInfo.hemorrhage;
                    nerveDamageCheckBox.checked = herniaInfo.nerveDamage;
                    cordInjuryCheckBox.checked = herniaInfo.cordInjury;
                    bowelInjuryCheckBox.checked = herniaInfo.bowelInjury;
                }

                if(herniaInfo.earlyPostoperativeComplications)
                {
                    earlyPostOperativeComplicationsCheckBox.checked = true;
                    woundInfectionCheckBox.checked = herniaInfo.woundInfection;
                    if(herniaInfo.seroma)
                    {
                        seromaCheckBox.checked = true;
                        seromaSizeComboBox.comboBox.currentIndex =
                                seromaSizeComboBox.comboBox.find(herniaInfo.seromaSize);
                    }
                    hematomaCheckBox.checked = herniaInfo.hematoma;
                    cordSwellingCheckBox.checked = herniaInfo.cordSwelling;
                    orchiepididymitisCheckBox.checked = herniaInfo.orchiepididymitis;
                }

                if(herniaInfo.latePostoperativeComplications)
                {
                    latePostOperativeComplicationsCheckBox.checked = true;
                    fistulasCheckBox.checked = herniaInfo.fistulas;
                    meshRejectionCheckBox.checked = herniaInfo.meshRejection;
                    chronicNeuralgiaCheckBox.checked = herniaInfo.chronicNeuralgia;
                    testicularAtrophyCheckBox.checked = herniaInfo.testicularAtrophy;
                    diseaseRecurrenceCheckBox.checked = herniaInfo.diseaseRecurrence;
                }


                for(var i = 0; i < 3; ++i)
                {
                    var earlyPainLayout = (i == 0) ? earlyPainAfter1Day : (i == 1) ? earlyPainAfter3Days : earlyPainAfter7Days;
                    if(herniaInfo.earlyInRestPain[i] || herniaInfo.earlyInMotionPain[i])
                    {
                        earlyPainLayout.checkBox.checked = true;
                        if(herniaInfo.earlyInRestPain[i])
                        {
                            earlyPainLayout.inRestPain.checkBox.checked = true;
                            earlyPainLayout.inRestPain.spinBox.value = herniaInfo.earlyInRestPainDegree[i];
                        }
                        if(herniaInfo.earlyInMotionPain[i])
                        {
                            earlyPainLayout.inMotionPain.checkBox.checked = true;
                            earlyPainLayout.inMotionPain.spinBox.value = herniaInfo.earlyInMotionPainDegree[i];
                        }
                        if(herniaInfo.earlyPainAnalgesics[i])
                        {
                            earlyPainLayout.analgesicsCheckBox.checked = true;
                            earlyPainLayout.analgesicsDaysField.field.text = herniaInfo.earlyPainAnalgesicsDays[i];
                            earlyPainLayout.analgesicsOrallyCheckBox.checked = herniaInfo.earlyPainAnalgesicsOrally[i];
                            earlyPainLayout.analgesicsInjectionsCheckBox.checked = herniaInfo.earlyPainAnalgesicsInjections[i];
                        }
                    }
                }


                nerveInjuryCheckBox.checked = herniaInfo.nerveInjury;

                if(herniaInfo.chronicPainInRest || herniaInfo.chronicPainInMotion)
                {
                    chronicPostoperativePainCheckBox.checked = true;
                    if(herniaInfo.chronicPainInRest)
                    {
                        chronicPostoperativeInRestPainLayout.checkBox.checked = true;
                        chronicPostoperativeInRestPainLayout.spinBox.value = herniaInfo.chronicPainInRestDegree;
                    }
                    if(herniaInfo.chronicPainInMotion)
                    {
                        chronicPostoperativeInMotionPainLayout.checkBox.checked = true;
                        chronicPostoperativeInMotionPainLayout.spinBox.value = herniaInfo.chronicPainInMotionDegree;
                    }
                }

            } // Конец блока для операции


            if(herniaInfo.images)
            {
                for(i = 0; i < herniaInfo.imageSources.length; ++i)
                {
                    imageLoader.addImage(herniaInfo.imageSources[i], herniaInfo.imageDescriptions[i]);
                }
            }


        }

    }

    function saveChanges()
    {
        // 1) добавляем грыжу (как новую) с помощью функции addHernia()
        // 2) если добавление прошло успешно, то удалям старую грыжу с указанным id (из всех связанных таблиц)
        // 3) меняем id новой грыжи на указанный id старой (во всех связанных таблицах)

        var tmpHerniaId = root.addHernia();
        if(tmpHerniaId === 0)
            return false;

        dbWorker.deleteHerniaRecords(root.editHerniaId);
        dbWorker.changeHerniaId(tmpHerniaId, root.editHerniaId);


        return true;
    }

    function addHernia() // возвращает id добавленной грыжи
    {
        // Добавление записи в таблицу "Грыжи"
        var side = herniaSideComboBox.comboBox.currentText;
        var recurrence = recurrenceCheckBox.checked;
        var inRestPain = preoperativeInRestPainLayout.spinBox.visible ? preoperativeInRestPainLayout.spinBox.value : -1;
        var inMotionPain = preoperativeInMotionPainLayout.spinBox.visible ?
                    preoperativeInMotionPainLayout.spinBox.value : -1;

        var herniaId = dbWorker.insertHernia(root.cardId, side, recurrence, inRestPain, inMotionPain);
        console.log("Hernia id: " + herniaId);
        if(herniaId === 0) return 0;


        // Если грыжа вентральная
        if(ventralHerniaTypeComboBox.visible)
        {
            var type = ventralHerniaTypeComboBox.comboBox.currentText;
            var subtype = (midlineVentralHerniaTypeComboBox.visible) ?
                        midlineVentralHerniaTypeComboBox.comboBox.currentText :
                           lateralVentralHerniaTypeComboBox.comboBox.currentText;
            var ventralHerniaWidth = ventralHerniaWidthComboBox.comboBox.currentText;
            var length = ventralHerniaLengthField.field.text;
            if(!dbWorker.insertVentralHernia(herniaId, type, subtype, ventralHerniaWidth, length))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }

        // Если грыжа паховая
        if(groinHerniaTypeComboBox.visible)
        {
            var groinHerniaType = groinHerniaTypeComboBox.comboBox.currentText;
            var examination = groinHerniaExaminationComboBox.comboBox.currentText;
            if(!dbWorker.insertGroinHernia(herniaId, groinHerniaType, examination))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }

        /*Q_INVOKABLE bool insertDiagnostics(int herniaId, const QString& method,
                                       const QString& ringWidth, const QString& sacWidth,
                                       const QString& sacLength);*/
        // Диагностика - клиническое обследование
        if(clinicalExaminationLayout.checkBox.checked)
        {
            if(!dbWorker.insertDiagnostics(herniaId, clinicalExaminationLayout.checkBox.text,
                                           clinicalExaminationLayout.hernialRingWidthField.field.text,
                                           clinicalExaminationLayout.hernialSacWidthField.field.text,
                                           clinicalExaminationLayout.hernialSacLengthField.field.text))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }
        // Диагностика - УЗИ на спине
        if(uziDorsalLayout.checkBox.checked)
        {
            if(!dbWorker.insertDiagnostics(herniaId, uziDorsalLayout.checkBox.text,
                                           uziDorsalLayout.hernialRingWidthField.field.text,
                                           uziDorsalLayout.hernialSacWidthField.field.text,
                                           uziDorsalLayout.hernialSacLengthField.field.text))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }
        // Диагностика - УЗИ стоя
        if(uziStandingLayout.checkBox.checked)
        {
            if(!dbWorker.insertDiagnostics(herniaId, uziStandingLayout.checkBox.text,
                                           uziStandingLayout.hernialRingWidthField.field.text,
                                           uziStandingLayout.hernialSacWidthField.field.text,
                                           uziStandingLayout.hernialSacLengthField.field.text))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }
        // Диагностика - КТ
        if(ktLayout.checkBox.checked)
        {
            if(!dbWorker.insertDiagnostics(herniaId, ktLayout.checkBox.text,
                                           ktLayout.hernialRingWidthField.field.text,
                                           ktLayout.hernialSacWidthField.field.text,
                                           ktLayout.hernialSacLengthField.field.text))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }
        // Диагностика - МРТ
        if(mrtLayout.checkBox.checked)
        {
            if(!dbWorker.insertDiagnostics(herniaId, mrtLayout.checkBox.text,
                                           mrtLayout.hernialRingWidthField.field.text,
                                           mrtLayout.hernialSacWidthField.field.text,
                                           mrtLayout.hernialSacLengthField.field.text))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }

        // Операция
        if(operationCheckBox.checked)
        {
            var operationSide = operationSideComboBox.visible ? operationSideComboBox.comboBox.currentText : "";
            var ringWidth = ringWidthField.field.text;
            var sacWidth = sacWidthField.field.text;
            var sacLength = sacLengthField.field.text;
            var method = operationTechniqueComboBox.comboBox.currentText;
            var technique = tissueRepairTechniqueTechniqueComboBox.visible ?
                        tissueRepairTechniqueTechniqueComboBox.comboBox.currentText :
                        meshImplantRepairTechniqueComboBox.comboBox.currentText;

            // Для разделов с осложнениями не нужно проверять, стоит ли галочка раздела,
            // т.к если она не стоит, то метод dbWorker будет записывать false (или пустоту) в базу
            var intraOperativeComplications = intraOperativeComplicationsCheckBox.checked;
            var hemorrhage = hemorrhageCheckBox.checked;
            var nerveDamage = nerveDamageCheckBox.checked;
            var cordInjury = cordInjuryCheckBox.checked;
            var bowelInjury = bowelInjuryCheckBox.checked;

            var earlyPostOperativeComplications = earlyPostOperativeComplicationsCheckBox.checked;
            var woundInfection = woundInfectionCheckBox.checked;
            var seroma = seromaCheckBox.checked;
            var seromaSize = seromaSizeComboBox.comboBox.currentText;
            var hematoma = hematomaCheckBox.checked;
            var cordSwelling = cordSwellingCheckBox.checked;
            var orchiepididymitis = orchiepididymitisCheckBox.checked;

            var latePostOperativeComplications = latePostOperativeComplicationsCheckBox.checked;
            var fistulas = fistulasCheckBox.checked;
            var meshRejection = meshRejectionCheckBox.checked;
            var chronicNeuralgia = chronicNeuralgiaCheckBox.checked;
            var testicularAtrophy = testicularAtrophyCheckBox.checked;
            var diseaseRecurrence = diseaseRecurrenceCheckBox.checked;

            var nerveInjury = nerveInjuryCheckBox.checked;
            var chronicPostoperativeInRestPain = chronicPostoperativeInRestPainLayout.checkBox.checked ?
                        chronicPostoperativeInRestPainLayout.spinBox.value : -1;
            var chronicPostoperativeInMotionPain = chronicPostoperativeInMotionPainLayout.checkBox.checked ?
                        chronicPostoperativeInMotionPainLayout.spinBox.value : -1;

            /*Q_INVOKABLE bool insertOperation(int herniaId, const QString& side, const QString& ringWidth, const QString& sacWidth,
                                        const QString& sacLength,
                                     const QString& method, const QString& technique, bool intraoperativeComplications,
                                     bool hemorrage, bool nerveDamage, bool spermaticCordInjury, bool bowelInjury,
                                     bool earlyComplications, bool woundInfection, bool seroma, const QString& seromaSize,
                                     bool hematoma, bool spermaticCordSwelling, bool orchiepididymitis,
                                     bool lateComplications, bool fistulas, bool meshRejection, bool chronicNeuralgia,
                                     bool testicularAtrophy, bool recurrence, bool nerveInjury,
                                     int chronicPainInRest, int chronicPainInMotion);*/
            if(!dbWorker.insertOperation(herniaId, operationSide, ringWidth, sacWidth, sacLength, method, technique,
                                         intraOperativeComplications, hemorrhage, nerveDamage, cordInjury, bowelInjury,
                                         earlyPostOperativeComplications,
                                         woundInfection, seroma, seromaSize, hematoma, cordSwelling, orchiepididymitis,
                                         latePostOperativeComplications, fistulas, meshRejection, chronicNeuralgia,
                                         testicularAtrophy, diseaseRecurrence, nerveInjury, chronicPostoperativeInRestPain,
                                         chronicPostoperativeInMotionPain))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }

            // Ненатяжной способ операции

            if(meshImplantRepairTechniqueComboBox.visible)
            {
                var mesh = anotherMeshCheckBox.checked ? anotherMeshField.field.text :
                                                         meshesComboBox.comboBox.currentText;
                var meshWidth = meshWidthField.field.text;
                var meshLength = meshLengthField.field.text;
                var fixation = "";
                if(meshFixationCheckBox.checked)
                {
                    fixation = anotherFixationTypeCheckBox.checked ? anotherFixationTypeField.field.text :
                                                                         fixationTypeComboBox.comboBox.currentText;
                }


                var tuckers = ""
                if(anotherTuckersCheckBox.visible) // если тип фиксации - такеры
                {
                    tuckers = anotherTuckersCheckBox.checked ? anotherTuckersField.field.text :
                                                               tuckersComboBox.comboBox.currentText;
                }

                var closure = peritoneumClosureComboBox.visible ? peritoneumClosureComboBox.comboBox.currentText : "";
                var drainage = drainageCheckBox.checked;

                /*Q_INVOKABLE bool insertNonTensionOperation(int herniaId, const QString& mesh, const QString& meshWidth,
                                               const QString& meshLength, const QString& fixation, const QString& tuckers,
                                               const QString& peritoneumClosure, bool drainage);*/

                if(!dbWorker.insertNonTensionOperation(herniaId, mesh, meshWidth,
                                                       meshLength, fixation, tuckers, closure, drainage))
                {
                    dbWorker.deleteHerniaRecords(herniaId);
                    return 0;
                }



            }

            /*Q_INVOKABLE bool insertEarlyPostOperativePain(int herniaId, int daysAfterOperation, int painInRest, int painInMotion,
                                              bool analgesics, const QString& daysOfMedication,
                                              bool orally, bool injections);*/


            // Ранняя боль - 1 сутки
            if(earlyPainAfter1Day.checkBox.checked)
            {
                var inRest1 = earlyPainAfter1Day.inRestPain.checkBox.checked ? earlyPainAfter1Day.inRestPain.spinBox.value : -1;
                var inMotion1 = earlyPainAfter1Day.inMotionPain.checkBox.checked ? earlyPainAfter1Day.inMotionPain.spinBox.value : -1;
                var analgesics1 = earlyPainAfter1Day.analgesicsCheckBox.checked;
                var daysOfMedication1 = earlyPainAfter1Day.analgesicsCheckBox.checked ?
                            earlyPainAfter1Day.analgesicsDaysField.field.text : "";
                var orally1 = earlyPainAfter1Day.analgesicsCheckBox.checked ?
                            earlyPainAfter1Day.analgesicsOrallyCheckBox.checked : false;
                var injections1 = earlyPainAfter1Day.analgesicsCheckBox.checked ?
                            earlyPainAfter1Day.analgesicsInjectionsCheckBox.checked : false;
                if(!dbWorker.insertEarlyPostOperativePain(herniaId, 1, inRest1, inMotion1, analgesics1,
                                                          daysOfMedication1, orally1, injections1))
                {
                    dbWorker.deleteHerniaRecords(herniaId);
                    return 0;
                }
            }

            // Ранняя боль - 3 суток
            if(earlyPainAfter3Days.checkBox.checked)
            {
                var inRest3 = earlyPainAfter3Days.inRestPain.checkBox.checked ? earlyPainAfter3Days.inRestPain.spinBox.value : -3;
                var inMotion3 = earlyPainAfter3Days.inMotionPain.checkBox.checked ? earlyPainAfter3Days.inMotionPain.spinBox.value : -3;
                var analgesics3 = earlyPainAfter3Days.analgesicsCheckBox.checked;
                var daysOfMedication3 = earlyPainAfter3Days.analgesicsCheckBox.checked ?
                            earlyPainAfter3Days.analgesicsDaysField.field.text : "";
                var orally3 = earlyPainAfter3Days.analgesicsCheckBox.checked ?
                            earlyPainAfter3Days.analgesicsOrallyCheckBox.checked : false;
                var injections3 = earlyPainAfter3Days.analgesicsCheckBox.checked ?
                            earlyPainAfter3Days.analgesicsInjectionsCheckBox.checked : false;
                if(!dbWorker.insertEarlyPostOperativePain(herniaId, 3, inRest3, inMotion3, analgesics3,
                                                          daysOfMedication3, orally3, injections3))
                {
                    dbWorker.deleteHerniaRecords(herniaId);
                    return 0;
                }
            }

            // Ранняя боль - 7 суток
            if(earlyPainAfter7Days.checkBox.checked)
            {
                var inRest7 = earlyPainAfter7Days.inRestPain.checkBox.checked ? earlyPainAfter7Days.inRestPain.spinBox.value : -7;
                var inMotion7 = earlyPainAfter7Days.inMotionPain.checkBox.checked ? earlyPainAfter7Days.inMotionPain.spinBox.value : -7;
                var analgesics7 = earlyPainAfter7Days.analgesicsCheckBox.checked;
                var daysOfMedication7 = earlyPainAfter7Days.analgesicsCheckBox.checked ?
                            earlyPainAfter7Days.analgesicsDaysField.field.text : "";
                var orally7 = earlyPainAfter7Days.analgesicsCheckBox.checked ?
                            earlyPainAfter7Days.analgesicsOrallyCheckBox.checked : false;
                var injections7 = earlyPainAfter7Days.analgesicsCheckBox.checked ?
                            earlyPainAfter7Days.analgesicsInjectionsCheckBox.checked : false;
                if(!dbWorker.insertEarlyPostOperativePain(herniaId, 7, inRest7, inMotion7, analgesics7,
                                                          daysOfMedication7, orally7, injections7))
                {
                    dbWorker.deleteHerniaRecords(herniaId);
                    return 0;
                }
            }


        } // Конец блока для операции

        // Добавление записей в таблицу "Изображения грыж"
        if(imageLoader.listModel.count > 0)
        {
            var srcList = [];
            var descriptionList = [];
            for(var i = 0; i < imageLoader.listModel.count; ++i)
            {
                srcList.push(imageLoader.listModel.get(i).src);
                descriptionList.push(imageLoader.listModel.get(i).description);
            }
            if(!dbWorker.insertHerniaImages(herniaId, srcList, descriptionList))
            {
                dbWorker.deleteHerniaRecords(herniaId);
                return 0;
            }
        }





        return herniaId;
    }


    function formIsReady()
    {
        if(!herniaTypeComboBox.isSelected()) return false;
        if(herniaTypeComboBox.comboBox.currentText == "Послеоперационная вентральная")
        {
            if(!ventralHerniaTypeComboBox.isSelected()) return false;
            if(ventralHerniaTypeComboBox.comboBox.currentText == "Срединная")
            {
                if(!midlineVentralHerniaTypeComboBox.isSelected()) return false;
            }
            else if(ventralHerniaTypeComboBox.comboBox.currentText == "Латеральная")
            {
                if(!lateralVentralHerniaTypeComboBox.isSelected()) return false;
            }
            if(!ventralHerniaWidthComboBox.isSelected()) return false;
            if(ventralHerniaLengthField.isEmpty()) return false;
        }
        else if(herniaTypeComboBox.comboBox.currentText == "Паховая")
        {
            if(!groinHerniaTypeComboBox.isSelected()) return false;
            if(!groinHerniaExaminationComboBox.isSelected()) return false;

        }

        if(!herniaSideComboBox.isSelected()) return false;

        if(clinicalExaminationLayout.isChecked() && !clinicalExaminationLayout.isReady())
            return false;
        if(uziDorsalLayout.isChecked() && !uziDorsalLayout.isReady())
            return false;
        if(uziStandingLayout.isChecked() && !uziStandingLayout.isReady())
            return false;
        if(ktLayout.isChecked() && !ktLayout.isReady())
            return false;
        if(mrtLayout.isChecked() && !mrtLayout.isReady())
            return false;

        if(preoperativePainCheckBox.checked)
        {
           if(!preoperativeInRestPainLayout.checkBox.checked && !preoperativeInMotionPainLayout.checkBox.checked)
               return false;
        }

        if(operationCheckBox.checked)
        {
            if(herniaSideComboBox.comboBox.currentText == "Двусторонняя")
                if(!operationSideComboBox.isSelected()) return false;
            if(ringWidthField.isEmpty()) return false;
            if(sacWidthField.isEmpty()) return false;
            if(sacLengthField.isEmpty()) return false;
            if(!operationTechniqueComboBox.isSelected()) return false;
            if(operationTechniqueComboBox.comboBox.currentText == "Натяжной способ")
            {
                if(!tissueRepairTechniqueTechniqueComboBox.isSelected())
                    return false;
            }
            else if(operationTechniqueComboBox.comboBox.currentText == "Ненатяжной способ")
            {
                if(!meshImplantRepairTechniqueComboBox.isSelected())
                    return false;
                if(!anotherMeshCheckBox.checked)  // Когда сетка выбирается из списка
                {
                    if(!meshesComboBox.isSelected()) return false;
                }
                else       // Когда сетка вводится вручную
                {
                    if(anotherMeshField.isEmpty()) return false;
                }
                if(meshWidthField.isEmpty()) return false;
                if(meshLengthField.isEmpty()) return false;
                if(meshFixationCheckBox.checked) //  Сетка была фиксирована
                {
                    if(!anotherFixationTypeCheckBox.checked) // тип фиксации выбирается из списка
                    {
                        if(!fixationTypeComboBox.isSelected()) return false;
                        if(fixationTypeComboBox.comboBox.currentText == "Такеры")
                        {
                            if(!anotherTuckersCheckBox.checked) // тип такеров выбирается из списка
                            {
                                if(!tuckersComboBox.isSelected()) return false;
                            }
                            else                           // тип такеров вводится вручную
                            {
                                if(anotherTuckersField.isEmpty()) return false;
                            }
                        }
                    }
                    else    // тип фиксации вводится вручную
                    {
                        if(anotherFixationTypeField.isEmpty()) return false;
                    }
                }

                if(meshImplantRepairTechniqueComboBox.comboBox.currentText == "TAPP")
                    if(!peritoneumClosureComboBox.isSelected()) return false;


            }  // Конец блока для ненатяжного лечения

            if(intraOperativeComplicationsCheckBox.checked)
            {
                if(!hemorrhageCheckBox.checked && !nerveDamageCheckBox.checked &&
                        !cordInjuryCheckBox.checked && !bowelInjuryCheckBox.checked)
                    return false;
            }

            if(earlyPostOperativeComplicationsCheckBox.checked)
            {
                if(!woundInfectionCheckBox.checked && !seromaCheckBox.checked && !hematomaCheckBox.checked
                        && !cordSwellingCheckBox.checked && !orchiepididymitisCheckBox.checked)
                    return false;
                if(seromaCheckBox.checked && !seromaSizeComboBox.isSelected()) return false;
            }

            if(latePostOperativeComplicationsCheckBox.checked)
            {
                if(!fistulasCheckBox.checked && !meshRejectionCheckBox.checked &&
                        !chronicNeuralgiaCheckBox.checked && !testicularAtrophyCheckBox.checked &&
                        !diseaseRecurrenceCheckBox.checked)
                    return false;
            }

            if(earlyPainAfter1Day.checkBox.checked)
                if(!earlyPainAfter1Day.isReady())
                    return false;

            if(earlyPainAfter3Days.checkBox.checked)
                if(!earlyPainAfter3Days.isReady())
                    return false;

            if(earlyPainAfter7Days.checkBox.checked)
                if(!earlyPainAfter7Days.isReady())
                    return false;

            if(chronicPostoperativePainCheckBox.checked)
            {
                if(!chronicPostoperativeInRestPainLayout.checkBox.checked
                        && !chronicPostoperativeInMotionPainLayout.checkBox.checked)
                    return false;
            }

        } // Конец блока для операции

        return true;
    }

    function reset()
    {
        herniaTypeComboBox.reset();
        ventralHerniaTypeComboBox.reset();
        midlineVentralHerniaTypeComboBox.reset();
        lateralVentralHerniaTypeComboBox.reset();
        ventralHerniaWidthComboBox.reset();
        ventralHerniaLengthField.reset();
        groinHerniaTypeComboBox.reset();
        groinHerniaExaminationComboBox.reset();
        herniaSideComboBox.reset();
        recurrenceCheckBox.checked = false;

        clinicalExaminationLayout.reset();
        uziStandingLayout.reset();
        uziDorsalLayout.reset();
        mrtLayout.reset();
        ktLayout.reset();

        preoperativePainCheckBox.checked = false;
        preoperativeInRestPainLayout.reset();
        preoperativeInMotionPainLayout.reset();

        operationCheckBox.checked = false;
        operationSideComboBox.reset();
        ringWidthField.reset();
        sacWidthField.reset();
        sacLengthField.reset();
        operationTechniqueComboBox.reset();
        tissueRepairTechniqueTechniqueComboBox.reset();
        meshImplantRepairTechniqueComboBox.reset();
        meshesComboBox.reset();
        anotherMeshCheckBox.checked = false;
        anotherMeshField.reset();
        meshWidthField.reset();
        meshLengthField.reset();
        meshFixationCheckBox.checked = false;
        fixationTypeComboBox.reset();
        anotherFixationTypeCheckBox.checked = false;
        anotherFixationTypeField.reset();
        tuckersComboBox.reset();
        anotherTuckersCheckBox.checked = false;
        anotherTuckersField.reset();
        peritoneumClosureComboBox.reset();
        drainageCheckBox.checked = false;

        intraOperativeComplicationsCheckBox.checked = false;
        hemorrhageCheckBox.checked = false;
        nerveDamageCheckBox.checked = false;
        cordInjuryCheckBox.checked = false;
        bowelInjuryCheckBox.checked = false;

        earlyPostOperativeComplicationsCheckBox.checked = false;
        woundInfectionCheckBox.checked = false;
        seromaCheckBox.checked = false;
        seromaSizeComboBox.reset();
        hematomaCheckBox.checked = false;
        cordSwellingCheckBox.checked = false;
        orchiepididymitisCheckBox.checked = false;

        latePostOperativeComplicationsCheckBox.checked = false;
        fistulasCheckBox.checked = false;
        meshRejectionCheckBox.checked = false;
        chronicNeuralgiaCheckBox.checked = false;
        testicularAtrophyCheckBox.checked = false;
        diseaseRecurrenceCheckBox.checked = false;

        earlyPainAfter1Day.reset();
        earlyPainAfter3Days.reset();
        earlyPainAfter7Days.reset();

        nerveInjuryCheckBox.checked = false;
        chronicPostoperativePainCheckBox.checked = false;
        chronicPostoperativeInRestPainLayout.reset();
        chronicPostoperativeInMotionPainLayout.reset();

        imageLoader.reset();

        root.cardId = 0;
        root.editHerniaId = 0;
        root.editMode = false;
    }

    function checkFields()
    {
        var ok = true;
        if(ventralHerniaLengthField.visible && !ventralHerniaLengthField.isEmpty())
        {
            if(!myFunctions.checkNum(ventralHerniaLengthField.field.text, false))
            {
                ventralHerniaLengthField.setIncorrectState("Укажите длину корректно!");
                ok = false;
            }
            else
                ventralHerniaLengthField.setNormalState();
        }

        if(clinicalExaminationLayout.isChecked())
            if(!clinicalExaminationLayout.checkFields())
                ok = false;
        if(uziDorsalLayout.isChecked())
            if(!uziDorsalLayout.checkFields())
                ok = false;
        if(uziStandingLayout.isChecked())
            if(!uziStandingLayout.checkFields())
                ok = false;
        if(mrtLayout.isChecked())
            if(!mrtLayout.checkFields())
                ok = false;
        if(ktLayout.isChecked())
            if(!ktLayout.checkFields())
                ok = false;

        if(ringWidthField.visible && !ringWidthField.isEmpty())
        {
            if(!myFunctions.checkNum(ringWidthField.field.text, false))
            {
                ringWidthField.setIncorrectState("Укажите ширину корректно!");
                ok = false;
            }
            else
                ringWidthField.setNormalState();
        }

        if(sacWidthField.visible && !sacWidthField.isEmpty())
        {
            if(!myFunctions.checkNum(sacWidthField.field.text, false))
            {
                sacWidthField.setIncorrectState("Укажите ширину корректно!");
                ok = false;
            }
            else
                sacWidthField.setNormalState();
        }

        if(sacLengthField.visible && !sacLengthField.isEmpty())
        {
            if(!myFunctions.checkNum(sacLengthField.field.text, false))
            {
                sacLengthField.setIncorrectState("Укажите длину корректно!");
                ok = false;
            }
            else
                sacLengthField.setNormalState();
        }

        if(anotherMeshCheckBox.visible && !anotherMeshField.isEmpty())
        {
            if(!myFunctions.checkPrintableString(anotherMeshField.field.text))
            {
                anotherMeshField.setIncorrectState("Введите название корректно!");
                ok = false;
            }
            else
                anotherMeshField.setNormalState();
        }



        if(meshWidthField.visible && !meshWidthField.isEmpty())
        {
            if(!myFunctions.checkNum(meshWidthField.field.text, false))
            {
                meshWidthField.setIncorrectState("Укажите ширину корректно!");
                ok = false;
            }
            else
                meshWidthField.setNormalState();
        }

        if(meshLengthField.visible && !meshLengthField.isEmpty())
        {
            if(!myFunctions.checkNum(meshLengthField.field.text, false))
            {
                meshLengthField.setIncorrectState("Укажите длину корректно!");
                ok = false;
            }
            else
                meshLengthField.setNormalState();
        }



        if(anotherFixationTypeField.visible && !anotherFixationTypeField.isEmpty())
        {
            if(!myFunctions.checkPrintableString(anotherFixationTypeField.field.text))
            {
                anotherFixationTypeField.setIncorrectState("Укажите тип корректно!");
                ok = false;
            }
            else
                anotherFixationTypeField.setNormalState();

        }


        if(anotherTuckersField.visible && !anotherTuckersField.isEmpty())
        {
            if(!myFunctions.checkPrintableString(anotherTuckersField.field.text))
            {
                anotherTuckersField.setIncorrectState("Укажите тип корректно!");
                ok = false;
            }
            else
                anotherTuckersField.setNormalState();
        }

        if(earlyPainAfter1Day.analgesicsDaysField.visible && !earlyPainAfter1Day.analgesicsDaysField.isEmpty())
            if(!earlyPainAfter1Day.checkAnalgesicsDaysField()) ok = false;

        if(earlyPainAfter3Days.analgesicsDaysField.visible && !earlyPainAfter3Days.analgesicsDaysField.isEmpty())
            if(!earlyPainAfter3Days.checkAnalgesicsDaysField()) ok = false;

        if(earlyPainAfter7Days.analgesicsDaysField.visible && !earlyPainAfter7Days.analgesicsDaysField.isEmpty())
            if(!earlyPainAfter7Days.checkAnalgesicsDaysField()) ok = false;

        return ok;


    }



    ScrollView{
        anchors.fill: parent
        anchors.margins: 40
        contentHeight: Math.max(parent.height, layout.height)
        contentWidth: Math.max(parent.width, layout.width)
        clip: true

        ColumnLayout{
            id: layout
            spacing: 10
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.margins: 50
            width: root.width / 2


            ComboBoxWithLabel{
                id: herniaTypeComboBox
                label.text: "Тип грыжи" + Properties.redPointer;
                Layout.minimumWidth: 320
                //Layout.maximumWidth: 450
                comboBox.model: dbWorker.herniaTypes();
            }

            ColumnLayout{ // Для вентральной грыжи
                id: ventralLayout
                spacing: 10
                width: parent.width
                visible: herniaTypeComboBox.comboBox.currentText == "Послеоперационная вентральная"
                Behavior on visible{
                    AppearanceAnimation{
                        target: ventralLayout
                    }
                }

                ComboBoxWithLabel{
                    id: ventralHerniaTypeComboBox
                    label.text: "Тип вентральной грыжи" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    //Layout.maximumWidth: 450
                    comboBox.model: dbWorker.ventralHerniaTypes();
                }

                ComboBoxWithLabel{
                    id: midlineVentralHerniaTypeComboBox
                    label.text: "Тип вентральной срединной грыжи" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    //Layout.maximumWidth: 450
                    comboBox.model: dbWorker.ventralMidlineHerniaTypes();
                    visible: ventralHerniaTypeComboBox.comboBox.currentText == "Срединная"
                    Behavior on visible{
                        AppearanceAnimation{
                            target: midlineVentralHerniaTypeComboBox
                        }
                    }
                }

                ComboBoxWithLabel{
                    id: lateralVentralHerniaTypeComboBox
                    label.text: "Тип вентральной латеральной грыжи" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.ventralLateralHerniaTypes();
                    visible: ventralHerniaTypeComboBox.comboBox.currentText == "Латеральная"
                    Behavior on visible{
                        AppearanceAnimation{
                            target: lateralVentralHerniaTypeComboBox
                        }
                    }
                }

                ComboBoxWithLabel{
                    id: ventralHerniaWidthComboBox
                    label.text: "Ширина (см)" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.ventralHerniaWidths();
                }

                TextFieldWithLabel{
                    id: ventralHerniaLengthField
                    label.text: "Длина (см)" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }



            }  // Конец колонки для вентральной грыжи

            ColumnLayout{ // Для паховой грыжи
                id: groinLayout
                spacing: 10

                width: parent.width
                visible: herniaTypeComboBox.comboBox.currentText == "Паховая"
                Behavior on visible{
                    AppearanceAnimation{
                        target: groinLayout
                    }
                }

                ComboBoxWithLabel{
                    id: groinHerniaTypeComboBox
                    label.text: "Тип паховой грыжи" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.groinHerniaTypes();
                }

                ComboBoxWithLabel{
                    id: groinHerniaExaminationComboBox
                    label.text: "Результаты исследования" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.groinHerniaExaminations();
                }



            } // Конец колонки для паховой грыжи

            ComboBoxWithLabel{
                id: herniaSideComboBox
                label.text: "Сторона" + Properties.redPointer;
                Layout.minimumWidth: 320
                comboBox.model: dbWorker.sides();
            }

            CheckBox{
                id: recurrenceCheckBox
                text: "Рецидив"
                font.pixelSize: 16
            }

            Label{
                text: "Диагноз"
                font.pixelSize: 20
                font.bold: true
            }

            DiagnosticMethodLayout{
                id: clinicalExaminationLayout
                width: parent.width
                checkBox.text: dbWorker.diagnosticMethods()[0]
            }

            DiagnosticMethodLayout{
                id: uziDorsalLayout
                width: parent.width
                checkBox.text: dbWorker.diagnosticMethods()[1]
            }

            DiagnosticMethodLayout{
                id: uziStandingLayout
                width: parent.width
                checkBox.text: dbWorker.diagnosticMethods()[2]
            }

            DiagnosticMethodLayout{
                id: ktLayout
                width: parent.width
                checkBox.text: dbWorker.diagnosticMethods()[3]
            }

            DiagnosticMethodLayout{
                id: mrtLayout
                width: parent.width
                checkBox.text: dbWorker.diagnosticMethods()[4]
            }



            Label{
                text: "Предоперационная боль"
                font.pixelSize: 20
                font.bold: true
            }
            CheckBox{
                id: preoperativePainCheckBox
                text: "Боль имеется"
                font.pixelSize: 16
            }

            ColumnLayout{ // Для предоперационной боли
                id: preoperativePainLayout
                width: parent.width
                Layout.leftMargin: 30
                visible: preoperativePainCheckBox.checked
                Behavior on visible {
                    AppearanceAnimation{
                        target: preoperativePainLayout
                    }
                }

                PainLayout{
                    id: preoperativeInRestPainLayout
                    width: parent.width
                    checkBox.text: "В покое"
                    label.text: "Степень боли в покое (в течение 4 нед. до операции)"
                }

                PainLayout{
                    id: preoperativeInMotionPainLayout
                    width: parent.width
                    checkBox.text: "В движении"
                    label.text: "Степень боли в движении (в течение 4 нед. до операции)"
                }
            }

            Label{
                text: "Операция"
                font.pixelSize: 20
                font.bold: true
            }
            CheckBox{
                id: operationCheckBox
                text: "Операция проводилась"
                font.pixelSize: 16
            }

            ColumnLayout{                    // Для операции
                id: operationLayout
                width: parent.width
                visible: operationCheckBox.checked
                Behavior on visible {
                    AppearanceAnimation{
                        target: operationLayout
                    }
                }

                ComboBoxWithLabel{
                    id: operationSideComboBox
                    visible: herniaSideComboBox.comboBox.currentText == "Двусторонняя"
                    label.text: "Сторона" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: ["Правосторонняя", "Левосторонняя"];
                }

                TextFieldWithLabel{
                    id: ringWidthField
                    label.text: "Ширина грыжевых ворот (см)" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: sacWidthField
                    label.text: "Ширина грыжевого мешка (см)" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }

                TextFieldWithLabel{
                    id: sacLengthField
                    label.text: "Длина грыжевого мешка (см)" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    field.implicitHeight: 40
                }

                // здесь был раздел "Рецидивная операция"

//                ComboBoxWithLabel{
//                    id: hernialHoleWidthComboBox
//                    label.text: "Ширина грыжевых ворот" + Properties.redPointer;
//                    Layout.minimumWidth: 320
//                    comboBox.model: dbWorker.hernialHoleSizes();
//                }

//                ComboBoxWithLabel{
//                    id: hernialSacWidthComboBox
//                    label.text: "Ширина грыжевого мешка" + Properties.redPointer;
//                    Layout.minimumWidth: 320
//                    comboBox.model: dbWorker.hernialSacSizes();
//                }

//                ComboBoxWithLabel{
//                    id: hernialSacLengthComboBox
//                    label.text: "Длина грыжевого мешка" + Properties.redPointer;
//                    Layout.minimumWidth: 320
//                    comboBox.model: dbWorker.hernialSacSizes();
//                }

                ComboBoxWithLabel{
                    id: operationTechniqueComboBox
                    label.text: "Способ оперативного лечения" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.operationTechniques();
                }

                ComboBoxWithLabel{
                    id: tissueRepairTechniqueTechniqueComboBox
                    label.text: "Техника натяжного способа" + Properties.redPointer;
                    Layout.minimumWidth: 320
                    comboBox.model: dbWorker.tissueRepairTechniques();
                    visible: operationTechniqueComboBox.comboBox.currentText == "Натяжной способ";
                    Behavior on visible {
                        AppearanceAnimation{
                            target: tissueRepairTechniqueTechniqueComboBox
                        }
                    }
                }

                ColumnLayout{ // Для ненатяжного способа
                    id: meshImplantRepairTechniqueLayout
                    width: parent.width
                    visible: operationTechniqueComboBox.comboBox.currentText == "Ненатяжной способ"
                    Behavior on visible {
                        AppearanceAnimation{
                            target: meshImplantRepairTechniqueLayout
                        }
                    }

                    ComboBoxWithLabel{
                        id: meshImplantRepairTechniqueComboBox
                        label.text: "Техника ненатяжного способа" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        comboBox.model: dbWorker.meshImplantRepairTechniques();
                    }

                    ComboBoxWithLabel{
                        id: meshesComboBox
                        label.text: "Тип сетки" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        comboBox.model: dbWorker.meshes();
                        enabled: !anotherMeshCheckBox.checked
                    }

                    CheckBox{
                        id: anotherMeshCheckBox
                        text: "Другой тип сетки"
                        font.pixelSize: 16
                    }

                    TextFieldWithLabel{
                        id: anotherMeshField
                        label.text: "Укажите тип сетки" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        field.implicitHeight: 40
                        visible: anotherMeshCheckBox.checked
                        Behavior on visible {
                            AppearanceAnimation
                            {
                                target: anotherMeshField
                            }
                        }
                    }

                    TextFieldWithLabel{
                        id: meshWidthField
                        label.text: "Ширина сетки (см)" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        field.implicitHeight: 40
                    }

                    TextFieldWithLabel{
                        id: meshLengthField
                        label.text: "Длина сетки (см)" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        field.implicitHeight: 40
                    }

                    CheckBox{
                        id: meshFixationCheckBox
                        text: "Сетка была фиксирована"
                        font.pixelSize: 16
                    }

                    ColumnLayout{           // для фиксации
                        id: fixationLayout
                        width: parent.width
                        visible: meshFixationCheckBox.checked
                        Behavior on visible {
                            AppearanceAnimation{
                                target: fixationLayout
                            }
                        }
                        ComboBoxWithLabel{
                            id: fixationTypeComboBox
                            label.text: "Тип фиксации" + Properties.redPointer;
                            Layout.minimumWidth: 320
                            comboBox.model: dbWorker.fixationTypes();
                            enabled: !anotherFixationTypeCheckBox.checked
                        }

                        CheckBox{
                            id: anotherFixationTypeCheckBox
                            text: "Другой тип фиксации"
                            font.pixelSize: 16
                        }

                        TextFieldWithLabel{
                            id: anotherFixationTypeField
                            label.text: "Укажите тип фиксации" + Properties.redPointer;
                            Layout.minimumWidth: 320
                            field.implicitHeight: 40
                            visible: anotherFixationTypeCheckBox.checked
                            Behavior on visible {
                                AppearanceAnimation{
                                    target: anotherFixationTypeField
                                }
                            }

                        }

                        ComboBoxWithLabel{
                            id: tuckersComboBox
                            label.text: "Тип такеров" + Properties.redPointer;
                            Layout.minimumWidth: 320
                            comboBox.model: dbWorker.tuckers();
                            visible: ((fixationTypeComboBox.comboBox.currentText == "Такеры") &&
                                      !anotherFixationTypeCheckBox.checked)
                            enabled: !anotherTuckersCheckBox.checked
                            Behavior on visible {
                                AppearanceAnimation{
                                    target: tuckersComboBox
                                }
                            }
                        }

                        CheckBox{
                            id: anotherTuckersCheckBox
                            text: "Другой тип такеров"
                            font.pixelSize: 16
                            visible: tuckersComboBox.visible
                            Behavior on visible {
                                AppearanceAnimation{
                                    target: anotherTuckersCheckBox
                                }
                            }
                        }

                        TextFieldWithLabel{
                            id: anotherTuckersField
                            label.text: "Укажите тип такеров" + Properties.redPointer;
                            Layout.minimumWidth: 320
                            field.implicitHeight: 40
                            visible: anotherTuckersCheckBox.checked && anotherTuckersCheckBox.visible
                            Behavior on visible {
                                AppearanceAnimation{
                                    target: anotherTuckersField
                                }
                            }
                        }
                    }  // конец колонки для фиксации


                    ComboBoxWithLabel{
                        id: peritoneumClosureComboBox
                        label.text: "Закрытие брюшины" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        comboBox.model: dbWorker.peritoneumClosures();
                        visible: meshImplantRepairTechniqueComboBox.comboBox.currentText ==
                                 "TAPP"
                        Behavior on visible {
                            AppearanceAnimation{
                                target: peritoneumClosureComboBox
                            }
                        }
                    }

                    CheckBox{
                        id: drainageCheckBox
                        text: "Дренаж"
                        font.pixelSize: 16
                    }

                }// конец колонки для ненатяжного способа

                Label{
                    text: "Осложнения"
                    font.pixelSize: 20
                    font.bold: true
                }

                CheckBox{
                    id: intraOperativeComplicationsCheckBox
                    text: "Интраоперационные осложнения"
                    font.pixelSize: 16
                }

                ColumnLayout{       // Для интраоперационных осложнений
                    id: intraOperativeLayout
                    Layout.leftMargin: 30
                    width: parent.width
                    visible: intraOperativeComplicationsCheckBox.checked
                    Behavior on visible {
                        AppearanceAnimation{
                            target: intraOperativeLayout
                        }
                    }

                    CheckBox{
                        id: hemorrhageCheckBox
                        text: "Кровотечение"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: nerveDamageCheckBox
                        text: "Повреждение нервных стволов"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: cordInjuryCheckBox
                        text: "Ранение элементов семенного канатика"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: bowelInjuryCheckBox
                        text: "Повреждение кишки и других внутренних органов"
                        font.pixelSize: 16
                    }

                } // Конец колонки для интраоперационных осложнений



                CheckBox{
                    id: earlyPostOperativeComplicationsCheckBox
                    text: "Ранние послеоперационные осложнения"
                    font.pixelSize: 16
                }

                ColumnLayout{   // Для ранних послеоперационных осложнений
                    id: earlyPostOperativeComplicationsLayout
                    width: parent.width
                    Layout.leftMargin: 30
                    visible: earlyPostOperativeComplicationsCheckBox.checked
                    Behavior on visible {
                        AppearanceAnimation{
                            target: earlyPostOperativeComplicationsLayout
                        }
                    }

                    CheckBox{
                        id: woundInfectionCheckBox
                        text: "Раневая инфекция (инфильтраты, нагноение)"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: seromaCheckBox
                        text: "Серома"
                        font.pixelSize: 16
                    }

                    ComboBoxWithLabel{
                        id: seromaSizeComboBox
                        label.text: "Размер серомы" + Properties.redPointer;
                        Layout.minimumWidth: 320
                        comboBox.model: dbWorker.seromaSizes();
                        visible: seromaCheckBox.checked
                        Behavior on visible {
                            AppearanceAnimation{
                                target: seromaSizeComboBox
                            }
                        }
                    }

                    CheckBox{
                        id: hematomaCheckBox
                        text: "Гематома"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: cordSwellingCheckBox
                        text: "Отек семенного канатика и яичка"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: orchiepididymitisCheckBox
                        text: "Орхоэпидидимит/орхит"
                        font.pixelSize: 16
                    }

                } // конец колонки для ранних послеоперационых осложнений

                // ---------

                CheckBox{
                    id: latePostOperativeComplicationsCheckBox
                    text: "Поздние послеоперационные осложнения"
                    font.pixelSize: 16
                }

                ColumnLayout{   // Для поздних послеоперационных осложнений
                    id: latePostOperativeComplicationsLayout
                    width: parent.width
                    Layout.leftMargin: 30
                    visible: latePostOperativeComplicationsCheckBox.checked
                    Behavior on visible {
                        AppearanceAnimation{
                            target: latePostOperativeComplicationsLayout
                        }
                    }

                    CheckBox{
                        id: fistulasCheckBox
                        text: "Свищи"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: meshRejectionCheckBox
                        text: "Отторжение и сморщивание сетчатого имплантата"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: chronicNeuralgiaCheckBox
                        text: "Хроническая пахово-генитальная невралгия"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: testicularAtrophyCheckBox
                        text: "Атрофия яичка"
                        font.pixelSize: 16
                    }

                    CheckBox{
                        id: diseaseRecurrenceCheckBox
                        text: "Рецидив заболевания​​​​​​​"
                        font.pixelSize: 16
                    }


                } // конец колонки для поздних послеоперационых осложнений


                EarlyPostOperativePainLayout{
                    id: earlyPainAfter1Day
                    title: "Боль (1 сутки после операции)"
                }

                EarlyPostOperativePainLayout{
                    id: earlyPainAfter3Days
                    title: "Боль (3 суток после операции)"
                }

                EarlyPostOperativePainLayout{
                    id: earlyPainAfter7Days
                    title: "Боль (7 суток после операции)"
                }



                CheckBox{
                    id: nerveInjuryCheckBox
                    text: "Травма нерва"
                    font.pixelSize: 16
                }

                CheckBox{
                    id: chronicPostoperativePainCheckBox
                    text: "Хроническая послеоперационная боль (⩾ 3 месяцев)"
                    font.pixelSize: 16
                }

                ColumnLayout{               // Для хронической послеоперационной боли
                    id: chronicPostoperativePainLayout
                    width: parent.width
                    Layout.leftMargin: 30
                    visible: chronicPostoperativePainCheckBox.checked
                    Behavior on visible {
                        AppearanceAnimation{
                            target: chronicPostoperativePainLayout
                        }
                    }
                    PainLayout{
                        id: chronicPostoperativeInRestPainLayout
                        width: parent.width
                        checkBox.text: "В покое"
                        label.text: "Степень боли в покое"
                    }

                    PainLayout{
                        id: chronicPostoperativeInMotionPainLayout
                        width: parent.width
                        checkBox.text: "В движении"
                        label.text: "Степень боли в движении"
                    }
                } // конец колонки для хронической послеоперационной боли

            } // конец колонки для операции

            Label{
                text: "Изображения"
                font.pixelSize: 20
                font.bold: true
            }

            ImageLoader{
                id: imageLoader
                Layout.minimumWidth: 320
                Layout.fillWidth: true
            }

            Item{
                height: 10
            }

            CustomButton{
                id: finishButton
                Layout.fillWidth: true
                Layout.minimumWidth: 320
                Layout.maximumWidth: 450
                rectangle.implicitHeight: 40
                text: root.editMode ? "Сохранить изменения" : "Завершить"
                color: Properties.buttonColor;
                hoverColor: Properties.buttonHoverColor;
                font.pixelSize: Properties.buttonFontPixelSize;
                rectangle.radius: height / 2
                enabled: root.formIsReady();
                onClicked: {
                    if(root.checkFields())
                    {
                        if(!root.editMode)
                        {
                            if(root.addHernia() !== 0)
                            {
                                messageDialog.showInformationMessage("Информация", "Грыжа добавлена в карту");
                                root.reset();
                                root.finished();
                            }

                            else
                                messageDialog.showCriticalMessage("Ошибка", "Не удалось добавить грыжу");
                        }

                        else
                        {
                            if(root.saveChanges())
                            {
                                messageDialog.showInformationMessage("Информация", "Изменения сохранены");
                                root.reset();
                                root.editingFinished()
                            }
                            else
                                messageDialog.showCriticalMessage("Ошибка", "Не удалось сохранить изменения");
                        }



                    }
                    else
                        console.log("Некорректный ввод");
                }
            }



        }

    }

        CustomMessageDialog{
            id: messageDialog
        }
}
