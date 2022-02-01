#ifndef DBWORKER_H
#define DBWORKER_H
#include <QSqlDatabase>
#include <QDate>
#include <QSqlQuery>
#include <QObject>
#include "treeviewmodel.h"
#include "imageprovider.h"

#define STATUS_ADMIN 1
#define STATUS_DOCTOR 2
#define STATUS_DOCTOR_REQUEST 3
#define STATUS_ORDINARY_USER 4

//namespace UserStatus
//{
//    //Q_NAMESPACE
//    enum userStatus
//    {
//        admin,
//        doctor,
//        doctorRequest,
//        ordinaryUser
//    };
//    //Q_ENUM_NS(userStatus)
//}

class DBWorker: public QObject
{
    Q_OBJECT
public:

//    enum userStatus
//    {
//        admin,
//        doctor,
//        doctorRequest,
//        ordinaryUser
//    };

    DBWorker(QObject *parent = 0);
    virtual ~DBWorker();
    QSqlDatabase &database();
    void setImageProvider(ImageProvider *provider);

    Q_INVOKABLE void clearImageProvider();
    void setTreeViewModel(TreeViewModel *treeViewModel);
    void createTables();
    bool createTable(const QString& title, const QString& fields);
    bool successConnection();
    bool tableIsEmpty(const QString& tableName);
    void fillReferenceTables();

    void fillRegionsTable();
    void fillUserStatusesTable();
    //void fillDiseaseDescriptionsTable();

    void fillHerniaTypesTable();
    void fillVentralHerniaTypesTable();
    void fillVentralMidlineHerniaTypesTable();
    void fillVentralLateralHerniaTypesTable();
    void fillVentralHerniaWidthsTable();
    void fillGroinHerniaTypesTable();
    void fillGroinHerniaExaminationsTable();
    void fillSidesTable();
//    void fillRecurrentOperationSpecificationsTable();
//    void fillHernialHoleSizesTable();
//    void fillHernialSacSizesTable();
    void fillTissueRepairTechniquesTable();
    void fillMeshImplantRepairTechniquesTable();
    void fillMeshesTable();
    void fillFixationTypesTable();
    void fillTuckersTable();
    void fillPeritoneumClosuresTable();
    void fillSeromaSizesTable();
    void fillOperationTechniquesTable();
    void fillDiagnosticMethodsTable();

    void fillOccupationsTable();
    void fillSportActivitiesTable();
    void fillSmokingHistoriesTable();


    // Для отображения списка пациентов ********************************************

    // все карты пациентов либо те, с которыми пользователь может работать
    Q_INVOKABLE QList<QObject*> getAllCardsModel(int userID);
    Q_INVOKABLE QList<QObject*> getAllAvailableCardsModel(int userID);

    // Выдача карты по номеру СНИЛСа. Последний параметр отвечает за выдачу только доступных пользователю карт
    // Хотя снилс уникален для каждой карты, выдача производится списком (пустым, либо с одним элементом)
    // Это нужно для упрощения написания вкладки поиска - фактически в ней используется тот же ListView,
    // что и во вкладке со списком пациентов (копипаст), но отображается результат в виде одной карты, либо в виде ничего

    Q_INVOKABLE QList<QObject*> getCardBySnils(int userID, const QString& snils, bool availableCarsOnly = false);


    Q_INVOKABLE QList<QObject*> getAllCardsForStatistics();     // выдача всех карт базы для статистики
    Q_INVOKABLE QList<QObject*> getStatisticsResults(bool strict);    // выдача удовлетворяющих заданным критериям карт для статистики
                                                                      // strict - true для поиска "И"



    Q_INVOKABLE QList<QObject*> getRegistrationRequests();

    Q_INVOKABLE QList<QObject*> getHerniasModel(int cardId);



    // Выдача строк по id из справочных таблиц

    Q_INVOKABLE bool riskFactorsArePresent(int cardId);

    Q_INVOKABLE QString getOccupationById(int id);
    Q_INVOKABLE QString getSportActivitiesById(int id);
    Q_INVOKABLE QString getSmokingHistoriesById(int id);

    QString getSideById(int id);

    QString getHerniaType(int herniaId);
    QString getVentralHerniaType(int herniaId);
    QString getVentralHerniaSubtype(int herniaId);
    QString getGroinHerniaType(int herniaId);

    QString getOperationMethod(int herniaId);
    QString getOperationTechnique(int herniaId);

    QString getMeshById(int id);


    // Выдача id данных из справочных таблиц



    int getOccupationId(const QString& occupation);
    int getSportActivitiesId(const QString& sportActivities);
    int getSmokingHistoryId(const QString& smokingHistory);

    int getSideId(const QString& side);

    int getVentralHerniaTypeId(const QString& ventralHerniaType);
    int getVentralMidlineHerniaTypeId(const QString& ventralMidlineHerniaType);
    int getVentralLateralHerniaTypeId(const QString& ventralLateralHerniaType);
    int getVentralHerniaWidthId(const QString& ventralHerniaWidth);

    int getGroinHerniaTypeId(const QString& groinHerniaType);
    int getGroinHerniaExaminationId(const QString& examination);

    int getDiagnosticMethodId(const QString& method);

    int getMeshId(const QString& mesh);
    int getTuckersId(const QString& tuckers);
    int getFixationTypeId(const QString& fixation);

    int getPeritoneumClosureId(const QString& peritoneumClosure);

    int getOperationTechniqueId(const QString& technique);
    int getTissueRepairTechniqueId(const QString& technique);
    int getMeshImplantRepairTechniqueId(const QString& technique);

    int getSeromaSizeId(const QString& seromaSize);

    int insertNewMesh(const QString& mesh);
    int insertNewFixationType(const QString& fixation);
    int insertNewTuckers(const QString& tuckers);




    // *****************************************************************************

    // Для выдачи большого количества информации из карты

    Q_INVOKABLE QObject* getMainCardInfo(int cardId);
    Q_INVOKABLE QObject* getRiskFactorsInfo(int cardId);

    Q_INVOKABLE QObject* getHerniaInfo(int herniaId);



    // ********************************************************************************

    Q_INVOKABLE bool passportExists(const QString& passport);
    Q_INVOKABLE bool snilsExists(const QString& snils);
    Q_INVOKABLE bool polisExists(const QString& polisType, const QString& polisNumber);




    Q_INVOKABLE bool registerUser(int userStatus,const QString& FIO,
                                  const QDate& birthDate, const QString& email,
                                  const QString& login, const QString& password);


    Q_INVOKABLE bool makeDoctorRegRequest(const QString& FIO,
                        const QDate& birthDate,
                        int experience,
                        const QString& region,
                        const QString& locality,
                        const QString& work_main,
                        const QString& work_extra,
                        const QString& specialty,
                        const QString& certificate,
                        const QString& email,
                        const QString& login,
                        const QString& password);

 //Сделать заявку на регистрацию нового врача. Создается запись в таблице Doctors, но не в таблице Users (поле для внешнего ключа
    // из таблицы Users остается пустым.



    QString getFieldDataByID(const QString& tableName, const QString& fieldName, int id);
    int getIDByFieldData(const QString& tableName, const QString& fieldName, const QString& fieldData);

    bool recordExists(const QString& tableName, const QString& fieldName, const QVariant& data);
    Q_INVOKABLE bool userExists(const QString& login, const QString& password);
    Q_INVOKABLE int getUserID(const QString& login, const QString& password); // NEW METHOD
    Q_INVOKABLE bool loginExists(const QString& login);
    bool emailExists(const QString& email);
    Q_INVOKABLE bool certificateExists(const QString& certificate);
    bool patientPassportExists(const QString& passportSeries, const QString& passportNumber);
    //QString getUserStatus(int userID);
    Q_INVOKABLE int getUserStatus(int userID);
    int maxID(const QString& tableName);
    int getIDForInsert(const QString& tableName);
    Q_INVOKABLE QString getUserFIO(int id);
    Q_INVOKABLE QString getRegionByID(int id);
    int getRegionID(const QString& regionName);
//    QString getDiseaseDescriptionByID(int id);
//    int getIdOfDiseaseDescription(const QString& description);
    QHash<int, QString> getDoctorsRequests();
    Q_INVOKABLE bool acceptRequest(int doctorId);
    Q_INVOKABLE bool rejectRequest(int doctorId);
    int getCardIdByNumber(const QString& cardNumber);
    bool cardAvailable(int userID, int cardID);

    bool patientExists(const QString& cardNumber, const QString& passportSeries, const QString& passportNumber,
                       const QString& snils, const QString& polisNumber);

    int getNewHerniaNumber(int cardID);

    Q_INVOKABLE int getCardIdBySnils(const QString& snils);

    // --- Списки строк из справочных таблиц ---------------------
    Q_INVOKABLE QStringList regions();

    Q_INVOKABLE QStringList herniaTypes();
    Q_INVOKABLE QStringList ventralHerniaTypes();
    Q_INVOKABLE QStringList ventralMidlineHerniaTypes();
    Q_INVOKABLE QStringList ventralLateralHerniaTypes();
    Q_INVOKABLE QStringList ventralHerniaWidths();
    Q_INVOKABLE QStringList groinHerniaTypes();
    Q_INVOKABLE QStringList groinHerniaExaminations();
    Q_INVOKABLE QStringList sides();
//    Q_INVOKABLE QStringList recurrentOperationSpecifications();
//    Q_INVOKABLE QStringList hernialHoleSizes();
//    Q_INVOKABLE QStringList hernialSacSizes();
    Q_INVOKABLE QStringList tissueRepairTechniques();
    Q_INVOKABLE QStringList meshImplantRepairTechniques();
    Q_INVOKABLE QStringList meshes(int userId = 0);
    Q_INVOKABLE QStringList fixationTypes();
    Q_INVOKABLE QStringList tuckers();
    Q_INVOKABLE QStringList peritoneumClosures();
    Q_INVOKABLE QStringList seromaSizes();
    Q_INVOKABLE QStringList operationTechniques();

    Q_INVOKABLE QStringList occupations();
    Q_INVOKABLE QStringList sportActivities();
    Q_INVOKABLE QStringList smokingHistories();

    Q_INVOKABLE QStringList diagnosticMethods();


    //-----------   Inserts ---------------------------------------------------------------
    void insertAvailableCard(int userID, int cardID);


    Q_INVOKABLE bool insertPatientCard(int userID, const QString& fio, const QDate& birthDate, const QString& sex,
                           const QString& phone, const QString& region, const QString& district,
                           const QString& locality, const QString& street, const QString& house, const QString& flat,
                           const QString& passport, const QString& snils,
                           const QString& polisType, const QString& polisNumber, const QString& bloodType,
                           const QString& rhesusFactor, const QString& weight, const QString& height,
                           const QString& complaints);




    Q_INVOKABLE bool insertRiskFactors(int cardId, int occupationId, int sportActivitiesId, int smokingHistoryId,
                           const QString& cigsPerDay, const QString& yearsOfSmoking,
                           bool diabetesI, bool diabetesII, bool hobl, bool hypertension,
                           bool heartDisease, bool kidneyDisease, bool gastritis, bool ulcer, bool aorticAneurysm,
                           bool immunosuppression, bool coagulopathy, bool plateletAggregationInhibitors,
                           const QString& otherFactors);


    // методы, служащие для добавления грыжи (каждый работает с разными таблицами)

    Q_INVOKABLE int insertHernia(int cardId, const QString& side,
                                 bool recurrence, int preoperativePainInRestDegree,
                                 int preoperativePainInMotionDegree);

    Q_INVOKABLE bool insertVentralHernia(int herniaId, const QString& type, const QString& subtype,
                                         const QString& width, const QString& length);

    Q_INVOKABLE bool insertGroinHernia(int herniaId, const QString& type, const QString& examination);

    Q_INVOKABLE bool insertDiagnostics(int herniaId, const QString& method,
                                       const QString& ringWidth, const QString& sacWidth,
                                       const QString& sacLength);



    Q_INVOKABLE bool insertOperation(int herniaId, const QString& side, const QString& ringWidth, const QString& sacWidth, const QString& sacLength,
                                     const QString& method, const QString& technique, bool intraoperativeComplications,
                                     bool hemorrage, bool nerveDamage, bool spermaticCordInjury, bool bowelInjury,
                                     bool earlyComplications, bool woundInfection, bool seroma, const QString& seromaSize,
                                     bool hematoma, bool spermaticCordSwelling, bool orchiepididymitis,
                                     bool lateComplications, bool fistulas, bool meshRejection, bool chronicNeuralgia,
                                     bool testicularAtrophy, bool recurrence, bool nerveInjury,
                                     int chronicPainInRest, int chronicPainInMotion);

    Q_INVOKABLE bool insertNonTensionOperation(int herniaId, const QString& mesh, const QString& meshWidth,
                                               const QString& meshLength, const QString& fixation, const QString& tuckers,
                                               const QString& peritoneumClosure, bool drainage);


    Q_INVOKABLE bool insertEarlyPostOperativePain(int herniaId, int daysAfterOperation, int painInRest, int painInMotion,
                                                  bool analgesics, const QString& analgesicsDays,
                                                  bool orally, const QString& orallyDays,
                                                  bool injections, const QString& injectionsDays);

    Q_INVOKABLE bool insertHerniaImages(int herniaId, const QStringList& sources, const QStringList& descriptions);

    // ----------------- Удаление записей, связанных с грыжей ------------------------------
    // в качестве параметра передается id записи из таблицы "Грыжи"


    Q_INVOKABLE void deleteHerniaRecords(int herniaId);


    Q_INVOKABLE void changeHerniaId(int oldId, int newId);


    //---------------------------   QSqlQueries   ------------------------------------------

    QSqlQuery patientCardQuery(int cardID);

    QSqlQuery riskFactorsQuery(int cardID);
    QSqlQuery herniaQuery(int cardID, int herniaNumber);


    bool deleteRecords(const QString& tableName, const QString& conditionField, const QVariant& value);

    //------------------------------    Updates    -----------------------------------------

    Q_INVOKABLE bool updatePatientCard(int cardId, const QString& fio, const QDate& birthDate, const QString& sex,
                           const QString& phone, const QString& region, const QString& district,
                           const QString& locality, const QString& street, const QString& house, const QString& flat,
                           const QString& passport, const QString& snils,
                           const QString& polisType, const QString& polisNumber, const QString& bloodType,
                           const QString& rhesusFactor, const QString& weight, const QString& height,
                           const QString& complaints);




    Q_INVOKABLE bool updateRiskFactors(int cardId, int occupationId, int sportActivitiesId, int smokingHistoryId,
                           const QString& cigsPerDay, const QString& yearsOfSmoking,
                           bool diabetesI, bool diabetesII, bool hobl, bool hypertension,
                           bool heartDisease, bool kidneyDisease, bool gastritis, bool ulcer, bool aorticAneurysm,
                           bool immunosuppression, bool coagulopathy, bool plateletAggregationInhibitors,
                           const QString& otherFactors);



    //----------------------------------    For statistics  --------------------------------------------
//    QHash<QString, int> regionsStatistics(const QList<int>& cardIDs);
//    QHash<QString, int> sexStatistics(const QList<int>& cardIDs);

    Q_INVOKABLE QList<QObject*> regionsDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> sexDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> operationMethodsDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> tensionOperationsDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> nonTensionOperationsDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> meshesDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> fixationDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> tuckersDistribution(const QList<int>& cardIDs);
    Q_INVOKABLE QList<QObject*> complicationsDistribution(const QList<int>& cardIDs);

    // --------------------------------
    Q_INVOKABLE void addMeshToLastAdded(int userId, const QString &mesh);


private:
    QSqlDatabase m_db;
    TreeViewModel *m_treeViewModel;
    ImageProvider *m_imageProvider;
    bool m_successConnection;
};

#endif // DBWORKER_H
