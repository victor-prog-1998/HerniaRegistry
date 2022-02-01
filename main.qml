import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

Window {
    id: programRoot
    visible: true
    width: 800
    height: 600

    function resize(width, height)
    {
        programRoot.width = width;
        programRoot.height = height;
    }

    // ****** Функции для вызова из других файлов *****

    function popStackView()
    {
        stackView.pop();
    }

    function openRiskFactorsPage(cardId, edit)
    {
        riskFactorsPage.cardId = cardId;
        riskFactorsPage.editMode = edit;
        stackView.push(riskFactorsPage);
    }

    function openStatisticsPage()
    {
        stackView.push(statisticsPage)
    }

    function openViewHerniaPage(herniaId, editIsAvailable, cardId, userId)
    {
        viewHerniaPage.herniaId = herniaId
        viewHerniaPage.editIsAvailable = editIsAvailable
        viewHerniaPage.cardId = cardId;
        viewHerniaPage.userId = userId;
        stackView.push(viewHerniaPage)
    }

    function openEditHerniaPage(herniaId, cardId, userId)
    {
        herniaPage.editHerniaId = herniaId;
        herniaPage.cardId = cardId;
        herniaPage.userId = userId;
        herniaPage.editMode = true;
        herniaPage.meshChanged = false;
        herniaPage.setOldInfo();
        stackView.push(herniaPage);

    }

    // ************************************************

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: authorizationPage
    }

    AuthorizationPage{
        id: authorizationPage
        onAuthClicked: {
            if(dbWorker.userExists(login, password))
            {
                var id = dbWorker.getUserID(login,password);
                var status = dbWorker.getUserStatus(id);
                authorizationPage.clearFields();
                switch(status)
                {
                case STATUS_ADMIN:

                    adminMainPage.userFio = dbWorker.getUserFIO(id);
                    adminMainPage.userID = id;
                    stackView.push(adminMainPage);
                    break;
                case STATUS_DOCTOR:
                    doctorMainPage.userFio = dbWorker.getUserFIO(id);
                    doctorMainPage.userID = id;
                    stackView.push(doctorMainPage);
                    break;
                case STATUS_DOCTOR_REQUEST:

                    messageDialog.showInformationMessage("Учётная запись временно недействительна","Вы подали ранее<br>
                                                      заявку на регистрацию себя в качестве врача.<br>
                                                      Пожалуйста, дождитесь подтверждения её администратором, <br>
                                                      чтобы получить доступ к системе.")
                    break;
                case STATUS_ORDINARY_USER:
                    ordinaryUserMainPage.userFio = dbWorker.getUserFIO(id);
                    ordinaryUserMainPage.userID = id;
                    stackView.push(ordinaryUserMainPage);
                    break;
                }
            }
            else
            {

                messageDialog.showCriticalMessage("Ошибка авторизации","Неверный логин или пароль");
            }
        }
        onRegistrationClicked: {
            stackView.push(registrationSelectPage);
        }
    }

    Page{
        id: welcomePage
        visible: false
        property int userID: 0
        ColumnLayout{
            spacing: 20
            Label{
                font.pixelSize: 20
                text: " Добро пожаловать!<br>Ваш id: " + welcomePage.userID;
            }
            Button{
                text: "Выйти"
                onClicked: stackView.re
            }
        }


    }

    CustomMessageDialog{
        id: messageDialog
    }

    RegistrationSelectPage{
        id: registrationSelectPage
        visible: false
        onBackClicked: {
            stackView.pop();
        }
        onUserRegistrationClicked: {
            stackView.push(userRegistrationPage);
        }

        onDoctorRegistrationClicked: {
            stackView.push(doctorRegistrationPage);
        }
    }

    UserRegistrationPage{
        id: userRegistrationPage
        visible: false
        onBackClicked: stackView.pop();
        onUserRegistrationFailed: {
            messageDialog.showCriticalMessage("Ошибка регистрации","Не удалось внести учетную запись в базу")
        }
        onUserRegistered: {
            messageDialog.showInformationMessage("Информация", "Вы успешно зарегистрировались в системе")
            stackView.pop(null);
        }
    }

    DoctorRegistrationPage{
        id: doctorRegistrationPage
        visible: false
        onBackClicked: {stackView.pop(); }
        onRequestFailed: {
            messageDialog.showCriticalMessage("Ошибка", "Не удалось подать заявку на регистрацию");
        }
        onRequestSubmitted: {
            messageDialog.showInformationMessage("Информация","Ваша заявка на регистрацию подана.<br>
                                        Дождитесь подтверждения её администратором, чтобы войти в систему.")
            stackView.pop(null);
        }
    }

    AdminMainPage{
        id: adminMainPage
        visible: false
        onExitClicked: {
            stackView.pop(null)
        }
        onOpenCardFromListClicked: {
            viewCardPage.userId = userId
            viewCardPage.cardId = cardId
            viewCardPage.editIsAvailable = true
            stackView.push(viewCardPage)
        }
    }

    OrdinaryUserMainPage{
        id: ordinaryUserMainPage
        visible: false
        onExitClicked: {
            stackView.pop(null)
        }
        onOpenCardAfterAddingClicked: {
            viewCardPage.userId = userId
            viewCardPage.cardId = cardId
            viewCardPage.editIsAvailable = true
            stackView.push(viewCardPage)
            console.log("open after adding")
        }
        onOpenCardFromListClicked: {
            viewCardPage.userId = userId
            viewCardPage.cardId = cardId
            viewCardPage.editIsAvailable = false
            stackView.push(viewCardPage)
        }
    }

    DoctorMainPage{
        id: doctorMainPage
        visible: false
        onExitClicked: {
            stackView.pop(null)
        }
        onOpenCardAfterAddingClicked: {
            viewCardPage.userId = userId
            viewCardPage.cardId = cardId
            viewCardPage.editIsAvailable = true
            stackView.push(viewCardPage)
            console.log("open after adding")
        }
        onOpenCardFromListClicked: {
            viewCardPage.userId = userId
            viewCardPage.cardId = cardId
            viewCardPage.editIsAvailable = true
            stackView.push(viewCardPage)
        }
    }

    ViewCardPage{
        id: viewCardPage
        visible: false
        onCloseCardClicked: stackView.pop();
        onEditMainInfoClicked: {
            editMainCardInfoPage.cardId = cardId;
            stackView.push(editMainCardInfoPage);
        }
        onAddHerniaClicked: {
            herniaPage.cardId = cardId;
            herniaPage.userId = userId;
            stackView.push(herniaPage);
        }
    }

    EditMainCardInfoPage{
        id: editMainCardInfoPage
        visible: false
        onExitClicked: stackView.pop();
        onChangesSaved: {
            viewCardPage.updateMainInfo();
//            ordinaryUserMainPage.updatePatientListTabs();
//            doctorMainPage.updatePatientListTabs();

            stackView.pop();
        }
    }

    HerniaPage{
        id: herniaPage
        visible: false
        onExitClicked: {
            stackView.pop();
        }

        onFinished: {
            stackView.pop();
            // + обновление списка
            viewCardPage.updateHernias();
        }

        onEditingFinished: {
            // Возвращаемся к странице с просмотром карты
            stackView.pop();
            stackView.pop();
            // следующие две функции - те же, что вызываются при закрытии страницы просмотра грыжи пользователем
            viewHerniaPage.reset();
            dbWorker.clearImageProvider();
            // ****************************************************************************
            viewCardPage.updateHernias();
        }
    }

//    RiskFactorsPage{
//        id: riskFactorsPage
//        visible: false
//        onExitClicked: {
//            stackView.pop();
//        }
//    }

    RiskFactorsPage{
        id: riskFactorsPage
        visible: false
        onExitClicked: {
            stackView.pop();
        }
        onFinished: {
            stackView.pop();
            viewCardPage.showRiskFactorsTab.setRiskFactorsInfo();
        }
    }

    StatisticsPage{
        id: statisticsPage
        visible: false
        onExitClicked: stackView.pop()
        onShowDistributionClicked: {
            distributionPage.findDistribution(cardList, feature);
            stackView.push(distributionPage);
        }
    }

    DistributionPage{
        id: distributionPage
        visible: false
        onExitClicked: stackView.pop();

    }

    ViewHerniaPage{
        id: viewHerniaPage
        visible: false
        onExitClicked: stackView.pop()
    }




}
