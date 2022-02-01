#include "dbworker.h"
//#include <QMessageBox>
#include <QDebug>
#include "patientlistelement.h"
#include "maincardinfo.h"
#include "riskfactorsinfo.h"
#include "myfunctions.h"
#include "statisticslistelement.h"
#include "requestinfo.h"
#include "hernialistelement.h"
#include "distributionelement.h"
#include "herniainfo.h"
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QPixmap>
#include <QFileInfo>

DBWorker::DBWorker(QObject *parent): QObject(parent)
{
//---------------------------   For SQLite  -----------------------------------
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("hernia_db_qml");
//-----------------------------------------------------------------------------

//---------------------------   For MySQL   -----------------------------------
//    m_db = QSqlDatabase::addDatabase("QMYSQL");
//    m_db.setHostName("localhost");
//    m_db.setDatabaseName("hernia_db_qml");
//    m_db.setUserName("root");
//    m_db.setPassword("1111");
//-----------------------------------------------------------------------------


    if(!m_db.open())
    {
        qDebug()<<"QMYSQL driver not loaded";
        //QMessageBox::critical(0, "", "Не удалось подключиться к базе данных");
        this->m_successConnection = false;
    }
    else
    {
        this->m_successConnection = true;
        this->createTables();
        this->fillReferenceTables();
        if(this->tableIsEmpty("Users"))
            this->registerUser(STATUS_ADMIN, "Администратор", QDate(1990,1,1), "admin@hernia.ru", "admin", "111");
    }
}

DBWorker::~DBWorker()
{

}

QSqlDatabase &DBWorker::database()
{
    return this->m_db;
}

void DBWorker::setImageProvider(ImageProvider *provider)
{
    this->m_imageProvider = provider;
}

void DBWorker::clearImageProvider()
{
    this->m_imageProvider->clear();
}

void DBWorker::setTreeViewModel(TreeViewModel *treeViewModel)
{
    this->m_treeViewModel = treeViewModel;
}

void DBWorker::createTables()
{
    //--------------------  Пользователи    --------------------------------------------------------

    if(createTable("Users", "id INTEGER UNIQUE PRIMARY KEY, "
                   "statusId TINYINT, "
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "email VARCHAR(40), "
                   "login VARCHAR(40), "
                   "password VARCHAR(40)"))
        qDebug() << "Таблица \"Пользователи\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Пользователи\"");
        qDebug() << "Ошибка при создании таблицы \"Пользователи\"";


    //--------------------  Регионы    --------------------------------------------------------

    if(createTable("Regions", "id TINYINT UNIQUE PRIMARY KEY, name VARCHAR(40)"))
        qDebug() << "Таблица \"Регионы\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Регионы\"");
        qDebug() << "Ошибка при создании таблицы \"Регионы\"";


    //--------------------  Статусы пользователей    -------------------------------------------------

    if(createTable("UserStatuses", "id TINYINT UNIQUE PRIMARY KEY, status VARCHAR(40)"))
        qDebug() << "Таблица \"Статусы пользователей\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Статусы пользователей\"");
        qDebug() << "Ошибка при создании таблицы \"Статусы пользователей\"";


    //--------------------   Врачи   --------------------------------------------------------

    if(createTable("Doctors",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "user_id INTEGER, "
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "experience TINYINT, "
                   "region_id TINYINT, "
                   "locality VARCHAR(50), "
                   "work_main VARCHAR(120), "
                   "work_extra VARCHAR(120), "
                   "specialty VARCHAR(100), "
                   "certificate VARCHAR(30), "
                   "email VARCHAR(40)"))
        qDebug() << "Таблица \"Врачи\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Врачи\"");
        qDebug() << "Ошибка при создании таблицы \"Врачи\"";


//    //--------------------  Сеансы пользователей    ---------------------------------------------------

//    if(createTable("UserSessions", "id INTEGER UNIQUE PRIMARY KEY, user_id INTEGER, begin DATETIME, end DATETIME"))
//        qDebug() << "Таблица \"Сеансы пользователей\" создана";
//    else
//        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Сеансы пользователей\"");
//        qDebug() << "Ошибка при создании таблицы \"Сеансы пользователей\"";


    //--------------------  Карты пациентов    --------------------------------------------------------

    if(createTable("PatientCards",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "sex VARCHAR(1), "
                   "phone VARCHAR(16), "
                   "region_id TINYINT, "
                   "district VARCHAR(60), "
                   "locality VARCHAR(50), "
                   "street VARCHAR(60), "
                   "house VARCHAR(30), "
                   "flat SMALLINT, "
                   "passport VARCHAR(11), "
                   "snils VARCHAR(14), "
                   "polis_type VARCHAR(3), "
                   "polis_number VARCHAR(16), "
                   "blood_type VARCHAR(3), "
                   "rhesus_factor VARCHAR(1), "
                   "weight SMALLINT, "
                   "height SMALLINT, "
                   "complaints VARCHAR(300)"))
        qDebug() << "Таблица \"Карты пациентов\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Карты пациентов\"");
        qDebug() << "Ошибка при создании таблицы \"Карты пациентов\"";


    //--------------------  Описания заболеваний    -------------------------------------------------
//    if(createTable("DiseaseDescriptions",
//                   "id TINYINT UNIQUE PRIMARY KEY, "
//                   "description VARCHAR(30)"))
//        qDebug() << "Таблица \"Описания заболеваний\" создана";
//    else
//        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Описания заболеваний\"");
//        qDebug() << "Ошибка при создании таблицы \"Описания заболеваний\"";

    //--------------------  Коморбидности    --------------------------------------------------------


    //--------------------  Факторы риска    --------------------------------------------------------


    if(createTable("RiskFactors",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "card_id INTEGER UNSIGNED, "
                   "occupation_id TINYINT UNSIGNED,"
                   "sporting_activities_id TINYINT UNSIGNED, "
                   "smoking_history_id TINYINT UNSIGNED, "
                   "cigs_per_day TINYINT UNSIGNED, "
                   "years_of_smoking TINYINT UNSIGNED, "
                   "diabetes_I BOOLEAN, "
                   "diabetes_II BOOLEAN, "
                   "hobl BOOLEAN, "
                   "hypertension BOOLEAN, "
                   "heart_disease BOOLEAN, "
                   "kidney_disease BOOLEAN, "
                   "gastritis BOOLEAN, "
                   "ulcer BOOLEAN, "
                   "aortic_aneurysm BOOLEAN, "
                   "immunosuppression BOOLEAN, "
                   "coagulopathy BOOLEAN, "
                   "platelet_aggregation_inhibitors BOOLEAN, "
                   "other_factors VARCHAR(300)"
                   ))
        qDebug() << "Таблица \"Факторы риска\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Факторы риска\"";

    // ||||||||||||||||||||||| Таблицы связанные с грыжами |||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // ------ Грыжи ----------------
    if(createTable("Hernias",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "card_id INTEGER UNSIGNED, "
                   "side_id TINYINT UNSIGNED,"
                   "recurrence BOOLEAN, "
                   "preoperation_pain_in_rest_degree TINYINT UNSIGNED, "
                   "preoperation_pain_in_motion_degree TINYINT UNSIGNED"
                   ))
        qDebug() << "Таблица \"Грыжи\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Грыжи\"";

    // ----------- Вентральные грыжи ---------------------
    if(createTable("VentralHernias",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "type_id TINYINT UNSIGNED, "
                   "subtype_id TINYINT UNSIGNED, "
                   "width_id TINYINT UNSIGNED, "
                   "length TINYINT UNSIGNED"))
        qDebug() << "Таблица \"Вентральные грыжи\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Вентральные грыжи\"";

    // ----------- Паховые грыжи -----------------------------
    if(createTable("GroinHernias",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "type_id TINYINT UNSIGNED, "
                   "examination_id TINYINT UNSIGNED"
                   ))
        qDebug() << "Таблица \"Паховые грыжи\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Паховые грыжи\"";

    // ---------- Ненатяжные операции -------------------------
    if(createTable("NonTensionOperations",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "mesh_id SMALLINT UNSIGNED, "
                   "mesh_width TINYINT UNSIGNED, "
                   "mesh_length TINYINT UNSIGNED, "
                   "fixation_id TINYINT UNSIGNED, "
                   "tuckers_id SMALLINT UNSIGNED, "
                   "peritoneum_closure_id TINYINT UNSIGNED, "
                   "drainage BOOLEAN"))
        qDebug() << "Таблица \"Ненатяжные операции\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Ненатяжные операции\"";

    // -------------- Диагностики ----------------------------
    if(createTable("Diagnostics",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "method_id TINYINT UNSIGNED, "
                   "ring_width TINYINT UNSIGNED, "
                   "sac_width TINYINT UNSIGNED, "
                   "sac_length TINYINT UNSIGNED"))
        qDebug() << "Таблица \"Диагностики\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Диагностики\"";

    // -------------- Ранняя послеоперационная боль ----------------
    if(createTable("EarlyPostoperativePain",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "days_after_operation TINYINT UNSIGNED, "
                   "pain_in_rest_degree TINYINT UNSIGNED, "
                   "pain_in_motion_degree TINYINT UNSIGNED, "
                   "analgesics BOOLEAN, "
                   "days_of_medication TINYINT UNSIGNED, "
                   "orally BOOLEAN, "
                   "days_of_medication_orally TINYINT UNSIGNED, "
                   "injections BOOLEAN, "
                   "days_of_medication_injections TINYINT UNSIGNED"))
        qDebug() << "Таблица \"Ранняя послеоперационная боль\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Ранняя послеоперационная боль\"";

    // ------------------ Операции ---------------------------------------
    if(createTable("Operations",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "side_id TINYINT UNSIGNED, "
                   "ring_width TINYINT UNSIGNED, "
                   "sac_width TINYINT UNSIGNED, "
                   "sac_length TINYINT UNSIGNED, "
                   "method_id TINYINT UNSIGNED, "
                   "technique_id TINYINT UNSIGNED, "
                   "intraoperative_complications BOOLEAN, "
                   "hemorrhage BOOLEAN, "
                   "nerve_damage BOOLEAN, "
                   "spermatic_cord_injury BOOLEAN, "
                   "bowel_injury BOOLEAN, "
                   "early_complications BOOLEAN, "
                   "wound_infection BOOLEAN, "
                   "seroma BOOLEAN, "
                   "seroma_size_id TINYINT UNSIGNED, "
                   "hematoma BOOLEAN, "
                   "spermatic_cord_swelling BOOLEAN, "
                   "orchiepididymitis BOOLEAN, "
                   "late_complications BOOLEAN, "
                   "fistulas BOOLEAN, "
                   "mesh_rejection BOOLEAN, "
                   "chronic_inguinal_neuralgia BOOLEAN, "
                   "testicular_atrophy BOOLEAN, "
                   "recurrence BOOLEAN, "
                   "nerve_injury BOOLEAN, "
                   "chronic_pain_in_rest_degree TINYINT UNSIGNED, "
                   "chronic_pain_in_motion_degree TINYINT UNSIGNED"))
        qDebug() << "Таблица \"Операции\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Операции\"";

    // ------ Изображения ----------
    if(createTable("HerniaImages",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "image MEDIUMBLOB, "
                   "description VARCHAR(300)"
                   ))
        qDebug() << "Таблица \"Изображения грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Изображения грыж\"";





    //||||||||||||||||||||||||||||  Справочные таблицы по грыжам    |||||||||||||||||||||||||||||||||||||||||||||||
    // -типы грыж (послеоперационная вентральная, паховая, итд)
    // - типы срединных грыж (для послеоперационных)
    // - типы латеральных грыж (для послеоперационных)
    // - ширины (для послеоперационных)
    // - типы паховых грыж(латеральная, медиальная, бедренная)
    // - паховые грыжи : исследование
    // *** Раздел с операцией ***
    // - стороны
    // - характеристика при рецидивной операции
    // - размер грыжевого отверстия
    // - длина грыжевого мешка
    // - техники операции
    // - техники при восстановлении тканями
    // - техники при восстановлении сетчатым имплантом (в одной таблице с подписями доступа)
    // - тип сетки
    // - тип фиксации
    // - тип такеров
    // - закрытие перитонеума (TAPP)
    // - размеры серомы
    // ********************************************8

    // ---------------- Типы грыж ---------------------------------------------------
    if(createTable("HerniaTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(50)"))
        qDebug() << "Таблица \"Типы грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы грыж\"";



    // ---------------- Типы срединных вентральных грыж -----------------------------
    if(createTable("VentralMidlineHerniaTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(30)"))
        qDebug() << "Таблица \"Типы срединных вентральных грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы срединных вентральных грыж\"";

    // ---------------- Типы латеральных вентральных грыж -----------------------------
    if(createTable("VentralLateralHerniaTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(30)"))
        qDebug() << "Таблица \"Типы латеральных вентральных грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы латеральных вентральных грыж\"";

    // ---------------- Ширины вентральных грыж -----------------------------
    if(createTable("VentralHerniaWidths", "id INTEGER UNIQUE PRIMARY KEY, width VARCHAR(15)"))
        qDebug() << "Таблица \"Ширины вентральных грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Ширины вентральных грыж\"";

    // ---------------- Типы паховых грыж -----------------------------
    if(createTable("GroinHerniaTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(25)"))
        qDebug() << "Таблица \"Типы паховых грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы паховых грыж\"";

    // ---------------- Исследования паховых грыж -----------------------------
    if(createTable("GroinHerniaExaminations", "id INTEGER UNIQUE PRIMARY KEY, examination VARCHAR(50)"))
        qDebug() << "Таблица \"Исследования паховых грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Исследования паховых грыж\"";

    // ---------------- Стороны -----------------------------
    if(createTable("Sides", "id INTEGER UNIQUE PRIMARY KEY, side VARCHAR(20)"))
        qDebug() << "Таблица \"Стороны\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Стороны\"";

    // ---------------- Характеристики при рецидивной операции -----------------------------
//    if(createTable("RecurrentOperationSpecifications", "id INTEGER UNIQUE PRIMARY KEY, specification VARCHAR(70)"))
//        qDebug() << "Таблица \"Характеристики при рецидивной операции\" создана";
//    else
//        qDebug() << "Ошибка при создании таблицы \"Характеристики при рецидивной операции\"";

//    // ---------------- Размеры грыжевого отверстия -----------------------------
//    if(createTable("HernialHoleSizes", "id INTEGER UNIQUE PRIMARY KEY, size VARCHAR(15)"))
//        qDebug() << "Таблица \"Размеры грыжевого отверстия\" создана";
//    else
//        qDebug() << "Ошибка при создании таблицы \"Размеры грыжевого отверстия\"";

//    // ---------------- Размеры грыжевого мешка -----------------------------
//    if(createTable("HernialSacSizes", "id INTEGER UNIQUE PRIMARY KEY, size VARCHAR(15)"))
//        qDebug() << "Таблица \"Размеры грыжевого мешка\" создана";
//    else
//        qDebug() << "Ошибка при создании таблицы \"Размеры грыжевого мешка\"";

    // ---------------- Техники восстановления тканями -----------------------------
    if(createTable("TissueRepairTechniques", "id INTEGER UNIQUE PRIMARY KEY, technique VARCHAR(15)"))
        qDebug() << "Таблица \"Техники восстановления тканями\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Техники восстановления тканями\"";

    // ---------------- Техники восстановления сетчатым имплантом -----------------------------
    if(createTable("MeshImplantRepairTechniques", "id INTEGER UNIQUE PRIMARY KEY, technique VARCHAR(60)"))
        qDebug() << "Таблица \"Техники восстановления сетчатым имплантом\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Техники восстановления сетчатым имплантом\"";

    // ---------------- Сетки -----------------------------
    if(createTable("Meshes", "id INTEGER UNIQUE PRIMARY KEY, mesh VARCHAR(90)"))
        qDebug() << "Таблица \"Сетки\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Сетки\"";

    // ---------------- Типы фиксации -----------------------------
    if(createTable("FixationTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(40)"))
        qDebug() << "Таблица \"Типы фиксации\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы фиксации\"";

    // ---------------- Такеры -----------------------------
    if(createTable("Tuckers", "id INTEGER UNIQUE PRIMARY KEY, tucker VARCHAR(50)"))
        qDebug() << "Таблица \"Такеры\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Такеры\"";

    // ---------------- Закрытия перитонеума -----------------------------
    if(createTable("PeritoneumClosures", "id INTEGER UNIQUE PRIMARY KEY, closure VARCHAR(15)"))
        qDebug() << "Таблица \"Закрытия перитонеума\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Закрытия перитонеума\"";

    // ---------------- Размеры серомы -----------------------------
    if(createTable("SeromaSizes", "id INTEGER UNIQUE PRIMARY KEY, size VARCHAR(9)"))
        qDebug() << "Таблица \"Размеры серомы\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Размеры серомы\"";

    // ---------------- Техники операции ---------------------------
    if(createTable("OperationTechniques", "id INTEGER UNIQUE PRIMARY KEY, technique VARCHAR(35)"))
        qDebug() << "Таблица \"Техники операции\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Техники операции\"";

    // --------------------- Методы диагностики -------------------------------------
    if(createTable("DiagnosticMethods", "id INTEGER UNIQUE PRIMARY KEY, method VARCHAR(50)"))
        qDebug() << "Таблица \"Методы диагностики\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Методы диагностики\"";

    // -------------------- Типы вентральных грыж --------------------------------------
    if(createTable("VentralHerniaTypes", "id INTEGER UNIQUE PRIMARY KEY, type VARCHAR(20)"))
        qDebug() << "Таблица \"Типы вентральных грыж\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Типы вентральных грыж\"";

    // ***************** Справочные таблицы для факторов риска ***************************************

    // Роды реятельности
    if(createTable("Occupations", "id INTEGER UNIQUE PRIMARY KEY, occupation VARCHAR(50)"))
        qDebug() << "Таблица \"Роды деятельности\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Роды деятельности\"";

    // Занятия спортом
    if(createTable("SportActivities", "id INTEGER UNIQUE PRIMARY KEY, activity VARCHAR(50)"))
        qDebug() << "Таблица \"Занятия спортом\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Занятия спортом\"";

    // Истории курения
    if(createTable("SmokingHistories", "id INTEGER UNIQUE PRIMARY KEY, history VARCHAR(50)"))
        qDebug() << "Таблица \"Истории курения\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Истории курения\"";





    //-------------------- Доступные карты пациентов    ------------------------------------------------------

    if(createTable("AvailablePatientCards", "id INTEGER UNIQUE PRIMARY KEY, user_id INTEGER, patient_card_id INTEGER"))
        qDebug() << "Таблица \"Доступные карты пациентов\" создана";
    else
        //QMessageBox::critical(0, "", "Ошибка при создании таблицы \"Доступные карты пациентов\"");
        qDebug() << "Ошибка при создании таблицы \"Доступные карты пациентов\"";

    // ------------------- Последние добавленные пользователем сетки ------------------------------------------
    // (без первичного ключа)
    if(createTable("LastAddedMeshes", "user_id INTEGER, mesh_id INTEGER"))
        qDebug() << "Таблица \"Последние добавленные пользователем сетки\" создана";
    else
        qDebug() << "Ошибка при создании таблицы \"Последние добавленные пользователем сетки\"";


}

bool DBWorker::createTable(const QString &title, const QString &fields)
{
    QString query = "CREATE TABLE IF NOT EXISTS " + title + " (" + fields + ')';
    QSqlQuery q(this->m_db);
    q.prepare(query);
    return q.exec();
}

bool DBWorker::successConnection()
{
    return this->m_successConnection;
}

bool DBWorker::tableIsEmpty(const QString &tableName)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT COUNT(*) FROM " + tableName);
    if(!q.exec())
    {
        qDebug() << "Ошибка при проверке пустоты таблицы " + tableName;
        return false;
    }
    q.next();
    return (q.value(0).toInt() == 0);
}

void DBWorker::fillReferenceTables()
{
    if(tableIsEmpty("Regions"))
        this->fillRegionsTable();
    if(tableIsEmpty("UserStatuses"))
        this->fillUserStatusesTable();
//    if(tableIsEmpty("DiseaseDescriptions"))
//        this->fillDiseaseDescriptionsTable();

    if(tableIsEmpty("HerniaTypes"))
        this->fillHerniaTypesTable();
    if(tableIsEmpty("VentralHerniaTypes"))
        this->fillVentralHerniaTypesTable();
    if(tableIsEmpty("VentralMidlineHerniaTypes"))
        this->fillVentralMidlineHerniaTypesTable();
    if(tableIsEmpty("VentralLateralHerniaTypes"))
        this->fillVentralLateralHerniaTypesTable();
    if(tableIsEmpty("VentralHerniaWidths"))
        this->fillVentralHerniaWidthsTable();
    if(tableIsEmpty("GroinHerniaTypes"))
        this->fillGroinHerniaTypesTable();
    if(tableIsEmpty("GroinHerniaExaminations"))
        this->fillGroinHerniaExaminationsTable();
    if(tableIsEmpty("Sides"))
        this->fillSidesTable();
//    if(tableIsEmpty("RecurrentOperationSpecifications"))
//        this->fillRecurrentOperationSpecificationsTable();
//    if(tableIsEmpty("HernialHoleSizes"))
//        this->fillHernialHoleSizesTable();
//    if(tableIsEmpty("HernialSacSizes"))
//        this->fillHernialSacSizesTable();
    if(tableIsEmpty("TissueRepairTechniques"))
        this->fillTissueRepairTechniquesTable();
    if(tableIsEmpty("MeshImplantRepairTechniques"))
        this->fillMeshImplantRepairTechniquesTable();
    if(tableIsEmpty("Meshes"))
        this->fillMeshesTable();
    if(tableIsEmpty("FixationTypes"))
        this->fillFixationTypesTable();
    if(tableIsEmpty("Tuckers"))
        this->fillTuckersTable();
    if(tableIsEmpty("PeritoneumClosures"))
        this->fillPeritoneumClosuresTable();
    if(tableIsEmpty("SeromaSizes"))
        this->fillSeromaSizesTable();
    if(tableIsEmpty("OperationTechniques"))
        this->fillOperationTechniquesTable();

    if(tableIsEmpty("Occupations"))
        this->fillOccupationsTable();
    if(tableIsEmpty("SportActivities"))
        this->fillSportActivitiesTable();
    if(tableIsEmpty("SmokingHistories"))
        this->fillSmokingHistoriesTable();
    if(tableIsEmpty("DiagnosticMethods"))
        this->fillDiagnosticMethodsTable();
}

void DBWorker::fillRegionsTable()
{
    QStringList regionNames =
    {
        "Москва",
        "Санкт-Петербург",
        "Алтайский край",
        "Амурская область",
        "Архангельская область",
        "Астраханская область",
        "Белгородская область",
        "Брянская область",
        "Владимирская область",
        "Волгоградская область",
        "Вологодская область",
        "Воронежская область",
        "Еврейская автономная область",
        "Забайкальский край",
        "Ивановская область",
        "Иркутская область",
        "Кабардино-Балкарская Республика",
        "Калининградская область",
        "Калужская область",
        "Камчатский край",
        "Карачаево-Черкесская Республика",
        "Кемеровская область",
        "Кировская область",
        "Костромская область",
        "Краснодарский край",
        "Красноярский край",
        "Курганская область",
        "Курская область",
        "Ленинградская область",
        "Липецкая область",
        "Магаданская область",
        "Московская область",
        "Мурманская область",
        "Ненецкий автономный округ",
        "Нижегородская область",
        "Новгородская область",
        "Новосибирская область",
        "Омская область",
        "Оренбургская область",
        "Орловская область",
        "Пензенская область",
        "Пермский край",
        "Приморский край",
        "Псковская область",
        "Республика Адыгея",
        "Республика Алтай",
        "Республика Башкортостан",
        "Республика Бурятия",
        "Республика Дагестан",
        "Республика Ингушетия",
        "Республика Калмыкия",
        "Республика Карелия",
        "Республика Коми",
        "Республика Крым",
        "Республика Марий Эл",
        "Республика Мордовия",
        "Республика Саха (Якутия)",
        "Республика Северная Осетия - Алания",
        "Республика Татарстан",
        "Республика Тыва",
        "Республика Хакасия",
        "Ростовская область",
        "Рязанская область",
        "Самарская область",
        "Саратовская область",
        "Сахалинская область",
        "Свердловская область",
        "Севастополь",
        "Смоленская область",
        "Ставропольский край",
        "Тамбовская область",
        "Тверская область",
        "Томская область",
        "Тульская область",
        "Тюменская область",
        "Удмуртская Республика",
        "Ульяновская область",
        "Хабаровский край",
        "Ханты-Мансийский автономный округ - Югра",
        "Челябинская область",
        "Чеченская Республика",
        "Чувашская Республика - Чувашия",
        "Чукотский автономный округ",
        "Ямало-Ненецкий автономный округ",
        "Ярославская область"
    };

    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: regionNames)
    {
        q.prepare("INSERT INTO Regions (id, name) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillUserStatusesTable()
{
    QSqlQuery q(this->m_db);
    QStringList statuses =
    {
        "Администратор",
        "Врач",
        "Заявка на регистрацию врача",
        "Рядовой пользователь"
    };
    for(int i = 0; i < statuses.size(); ++i)
    {
        q.prepare("INSERT INTO UserStatuses (id, status) VALUES(?,?)");
        q.addBindValue(i + 1);
        q.addBindValue(statuses[i]);
        q.exec();
    }
}

//void DBWorker::fillDiseaseDescriptionsTable()
//{
//    QSqlQuery q(this->m_db);
//    QStringList discriptions =
//    {
//        "Без симптомов",
//        "Менее 4 обострений в год",
//        "Более 4 обострений в год",
//        "Прогрессирующее заболевание"
//    };
//    for(int i = 0; i < discriptions.size(); ++i)
//    {
//        q.prepare("INSERT INTO DiseaseDescriptions (id, description) VALUES(?,?)");
//        q.addBindValue(i + 1);
//        q.addBindValue(discriptions[i]);
//        q.exec();
//    }
//}

QList<QObject*> DBWorker::getAllCardsModel(int userID)
{
    QList<QObject*> modelList;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id, fio, sex, birth_date, snils, region_id FROM PatientCards");
    q.exec();
    qDebug() << "getAllCardsModel: userID = " << userID;
    while(q.next())
    {
        int id = q.value(0).toInt();
        QString fio = q.value(1).toString();
        QString sex = q.value(2).toString();
        QString birthDate = q.value(3).toString();
        QString snils = q.value(4).toString();
        QString region = this->getRegionByID(q.value(5).toInt());
        int status = this->getUserStatus(userID);
        bool view = (status == STATUS_ADMIN) ? true : cardAvailable(userID, id);
        bool edit = (status == STATUS_ADMIN) ? true : (status == STATUS_DOCTOR) ? cardAvailable(userID, id) : false;
        modelList.push_back(new PatientListElement(id, fio, sex, birthDate, snils, region, view, edit, this));
    }
    return modelList;
}

QList<QObject *> DBWorker::getAllAvailableCardsModel(int userID)
{
    QList<QObject*> modelList;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id, fio, sex, birth_date, snils, region_id FROM PatientCards WHERE id IN (SELECT patient_card_id "
              "FROM AvailablePatientCards"
              " WHERE user_id = ?)");
    q.addBindValue(userID);
    q.exec();
    while(q.next())
    {
        int id = q.value(0).toInt();
        QString fio = q.value(1).toString();
        QString sex = q.value(2).toString();
        QString birthDate = q.value(3).toString();
        QString snils = q.value(4).toString();
        QString region = this->getRegionByID(q.value(5).toInt());
        int status = this->getUserStatus(userID);
        // В коде окна админа этот метод не вызывается, а вызывается либо для рядового пользователя, либо для врача
        bool view = true;
        bool edit = (status == STATUS_DOCTOR);
        modelList.push_back(new PatientListElement(id, fio, sex, birthDate, snils, region, view, edit, this));
    }
    return modelList;
}

QList<QObject *> DBWorker::getCardBySnils(int userID, const QString &snils, bool availableCarsOnly)
{
    QList<QObject*> modelList;
    QSqlQuery q(this->m_db);
    if(availableCarsOnly)
    {
        q.prepare("SELECT id, fio, sex, birth_date, region_id FROM PatientCards WHERE (snils = ? AND id IN (SELECT patient_card_id "
                  "FROM AvailablePatientCards"
                  " WHERE user_id = ?))");
        q.addBindValue(snils);
        q.addBindValue(userID);
        q.exec();
        if(q.next())  // карта с указанным снилсом заведомо либо одна, либо не существует
        {
            int id = q.value(0).toInt();
            QString fio = q.value(1).toString();
            QString sex = q.value(2).toString();
            QString birthDate = q.value(3).toString();
            QString region = this->getRegionByID(q.value(4).toInt());
            int status = this->getUserStatus(userID);
            bool view = true;
            bool edit = (status == STATUS_DOCTOR);
            modelList.push_back(new PatientListElement(id, fio, sex, birthDate, snils, region, view, edit, this));

        }
    }
    else
    {
        q.prepare("SELECT id, fio, sex, birth_date, region_id FROM PatientCards WHERE snils = ?");
        q.addBindValue(snils);
        q.exec();
        if(q.next())
        {
            int id = q.value(0).toInt();
            QString fio = q.value(1).toString();
            QString sex = q.value(2).toString();
            QString birthDate = q.value(3).toString();
            QString region = this->getRegionByID(q.value(4).toInt());
            int status = this->getUserStatus(userID);
            bool view = (status == STATUS_ADMIN) ? true : cardAvailable(userID, id);
            bool edit = (status == STATUS_ADMIN) ? true : (status == STATUS_DOCTOR) ? cardAvailable(userID, id) : false;
            modelList.push_back(new PatientListElement(id, fio, sex, birthDate, snils, region, view, edit, this));
        }
    }
    return modelList;
}

QList<QObject *> DBWorker::getAllCardsForStatistics()
{
    QList<QObject*> list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id, sex, birth_date, region_id FROM PatientCards");
    q.exec();
    while(q.next())
    {
        int id = q.value(0).toInt();
        QString sex = q.value(1).toString();
        QString birthDate = q.value(2).toString();
        QString region = this->getRegionByID(q.value(3).toInt());
        list.push_back(new StatisticsListElement(id, sex, birthDate, region, this));
    }
    return list;
}

QList<QObject *> DBWorker::getStatisticsResults(bool strict)
{
    QList<QObject*> results;

    /* Признаки, для которых заданность всех признаков эквивалентно тому, что ни один признак не выбран
     * (это обязательные при добавлении карты признаки и которые не могут одновременно сосуществовать у одного
     * и того же пациента):
    - Пол
    - Регион
    */

    QStringList conditionsList;



    if(m_treeViewModel->childrenAreChecked("Пол") && !m_treeViewModel->allChildrenAreChecked("Пол"))
    {
        qDebug() << "Пол задан";
        QString sex = m_treeViewModel->getCheckedChildren("Пол")[0]; // В этом списке может быть только один элемент
        qDebug() << "---" << sex;
        QString sexCondition = "(sex = \'" + sex[0] + "\')"; // Пол в базе хранится как "М" либо "Ж"
        conditionsList.push_back(sexCondition);
        qDebug() << sexCondition;
    }

    if(m_treeViewModel->childrenAreChecked("Регион") && !m_treeViewModel->allChildrenAreChecked("Регион"))
    {
        qDebug() << "Регион задан";
        QStringList regionsList = this->m_treeViewModel->getCheckedChildren("Регион");
        for(auto str: regionsList)
            qDebug() << "---" << str;
        QList<int> regionsIdList;
        for(auto region: regionsList)
            regionsIdList.push_back(this->getRegionID(region));
        QString regionCondition = "(";
        for(int i = 0; i < regionsIdList.size(); ++i)
        {
            if(i != 0)
                regionCondition += "OR ";
            regionCondition += "region_id = " + QString::number(regionsIdList[i]) + " ";
        }
        regionCondition += ")";
        conditionsList.push_back(regionCondition);
        qDebug() << regionCondition;
    }

    QStringList riskFactorsConditions;

    if(m_treeViewModel->childrenAreChecked("Род деятельности"))
    {
        qDebug() << "Род деятельности задан";
        QStringList occupationList = this->m_treeViewModel->getCheckedChildren("Род деятельности");
        for(auto str: occupationList)
            qDebug() << "---" << str;
        QList<int> occupationIdList;
        for(auto str: occupationList)
            occupationIdList.push_back(this->getOccupationId(str));

        QString occupationCondition = "(";
        for(int i = 0; i < occupationIdList.size(); ++i)
        {
            if(i != 0)
                occupationCondition += "OR ";
            occupationCondition += "occupation_id = " + QString::number(occupationIdList[i]) + " ";
        }
        occupationCondition += ")";
        riskFactorsConditions.push_back(occupationCondition);
        qDebug() << occupationCondition;
    }

    if(m_treeViewModel->childrenAreChecked("Занятия спортом"))
    {
        qDebug() << "Занятия спортом заданы";
        QStringList sportList = this->m_treeViewModel->getCheckedChildren("Занятия спортом");
        for(auto str: sportList)
            qDebug() << "---" << str;
        QList<int> sportIdList;
        for(auto str: sportList)
            sportIdList.push_back(this->getSportActivitiesId(str));
        QString sportCondition = "(";
        for(int i = 0; i < sportIdList.size(); ++i)
        {
            if(i != 0)
                sportCondition += "OR ";
            sportCondition += "sporting_activities_id = " + QString::number(sportIdList[i]) + " ";
        }
        sportCondition += ")";
        riskFactorsConditions.push_back(sportCondition);
        qDebug() << sportCondition;
    }

    if(m_treeViewModel->childrenAreChecked("Курение"))
    {
        qDebug() << "Курение задано";
        QStringList smokingList = this->m_treeViewModel->getCheckedChildren("Курение");
        for(auto str: smokingList)
            qDebug() << "---" << str;
        QList<int> smokingIdList;
        for(auto str: smokingList)
            smokingIdList.push_back(this->getSmokingHistoryId(str));
        QString smokingCondition = "(";
        for(int i = 0; i < smokingIdList.size(); ++i)
        {
            if(i != 0)
                smokingCondition += "OR ";
            smokingCondition += "smoking_history_id = " + QString::number(smokingIdList[i]) + " ";
        }
        smokingCondition += ")";
        riskFactorsConditions.push_back(smokingCondition);
        qDebug() << smokingCondition;
    }

    if(m_treeViewModel->childrenAreChecked("Другие факторы"))
    {
        qDebug() << "Другие факторы заданы";
        QStringList otherFactorsList = this->m_treeViewModel->getCheckedChildren("Другие факторы");
        for(auto str: otherFactorsList)
            qDebug() << "---" << str;
        QHash<QString, QString> tableFields;

        tableFields["Сахарный диабет I типа"] = "diabetes_I";
        tableFields["Сахарный диабет II типа"] = "diabetes_II";
        tableFields["ХОБЛ"] = "hobl";
        tableFields["Гипертония"] = "hypertension";
        tableFields["Сердечное заболевание"] = "heart_disease";
        tableFields["Заболевание почек"] = "kidney_disease";
        tableFields["Гастрит"] = "gastritis";
        tableFields["Пептическая язва"] = "ulcer";
        tableFields["Аневризмы аорты"] = "aortic_aneurysm";
        tableFields["Иммуносупрессия"] = "immunosuppression";
        tableFields["Коагулопатия"] = "coagulopathy";
        tableFields["Ингибиторы агрегации тромбоцитов"] = "platelet_aggregation_inhibitors";

        QString otherFactorsCondition = "(";
        for(int i = 0; i < otherFactorsList.size(); ++i)
        {
            if(i != 0)
                otherFactorsCondition += strict ? "AND " : "OR ";
            otherFactorsCondition += tableFields[otherFactorsList[i]] + " = true ";
        }
        otherFactorsCondition += ")";
        riskFactorsConditions.push_back(otherFactorsCondition);
        qDebug() << otherFactorsCondition;
    }

    if(!riskFactorsConditions.isEmpty())
    {
        QString riskFactorsCondition = "(id IN (SELECT card_id FROM RiskFactors WHERE (";
        for(int i = 0; i < riskFactorsConditions.size(); ++i)
        {
            if(i != 0)
                riskFactorsCondition += "AND ";
            riskFactorsCondition += riskFactorsConditions[i] + " ";
        }
        riskFactorsCondition += ")))";
        conditionsList.push_back(riskFactorsCondition);
    }



    // Добавление в список conditionsList остальных критериев поиска (грыжи итд)

    // Если заданы критерии по грыжам (в т.ч. и по операциям): (сложность в том, что у пациента может быть несколько грыж)
    // 1) Для каждого критерия выдаем множество карт, в которых есть грыжа с указанным критерием
    // 2) В зависимости от типа поиска находим объединение или пересечение множеств



//    QString ventralHerniaConditionTemplate = "(id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM VentralHernias "
//                                             "WHERE type_id = %1 AND subtype_id = %2)))";
//    QString groinHerniaConditionTemplate = "(id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM GroinHernias "
//                                             "WHERE type_id = %1)))";

    QStringList herniaTypeConditions;
    QStringList ventralHerniaConditions;
    QStringList groinHerniaConditions;

    if(this->m_treeViewModel->childrenAreChecked("Срединная"))
    {
        int type_id = this->getVentralHerniaTypeId("Срединная");
        QString conditionTemplate = "(type_id = %1 AND subtype_id = %2)";
        QStringList list = this->m_treeViewModel->getCheckedChildren("Срединная");
        for(auto str: list)
        {
            int subtype_id = this->getVentralMidlineHerniaTypeId(str);
            ventralHerniaConditions.push_back(conditionTemplate.arg(type_id).arg(subtype_id));
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Латеральная"))
    {
        int type_id = this->getVentralHerniaTypeId("Латеральная");
        QString conditionTemplate = "(type_id = %1 AND subtype_id = %2)";
        QStringList list = this->m_treeViewModel->getCheckedChildren("Латеральная");
        for(auto str: list)
        {
            int subtype_id = this->getVentralLateralHerniaTypeId(str);
            ventralHerniaConditions.push_back(conditionTemplate.arg(type_id).arg(subtype_id));
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Паховая"))
    {
        QStringList list = this->m_treeViewModel->getCheckedChildren("Паховая");
        QString conditionTemplate = "type_id = %1";
        for(auto str: list)
        {
            int type_id = this->getGroinHerniaTypeId(str);
            groinHerniaConditions.push_back(conditionTemplate.arg(type_id));
        }
    }

    if(!ventralHerniaConditions.isEmpty())
    {
        QString condition;
        for(int i = 0; i < ventralHerniaConditions.size(); ++i)
        {
            if(i != 0) condition += " OR ";
            condition += ventralHerniaConditions[i];
        }
        condition = "(id IN (SELECT hernia_id FROM VentralHernias WHERE " + condition + "))";
        herniaTypeConditions.push_back(condition);
    }

    if(!groinHerniaConditions.isEmpty())
    {
        QString condition;
        for(int i = 0; i < groinHerniaConditions.size(); ++i)
        {
            if(i != 0) condition += " OR ";
            condition += groinHerniaConditions[i];
        }
        condition = "(id IN (SELECT hernia_id FROM GroinHernias WHERE " + condition + "))";
        herniaTypeConditions.push_back(condition);
    }

    QStringList herniaConditions;

    if(!herniaTypeConditions.isEmpty())
    {
        if(herniaTypeConditions.size() == 1) // только паховая или только вентральная
            herniaConditions.push_back(herniaTypeConditions[0]);
        else  // и паховая, и вентральная
        {
            herniaConditions.push_back('(' + herniaTypeConditions[0] + " OR " + herniaTypeConditions[1] + ')');
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Сторона"))
    {
        // Не проверяем, указаны ли все 3 стороны (как это делалось с полом, когда указаны оба пола),
        // так как в случае, если в разделе "Грыжи" указаны ТОЛЬКО стороны,
        // то придется выдать пациентов с грыжами, а не игнорировать это условие
        QString sideCondition;
        QStringList sideConditions = this->m_treeViewModel->getCheckedChildren("Сторона");
        for(int i = 0; i < sideConditions.size(); ++i)
        {
            if(i != 0) sideCondition += " OR ";
            sideCondition += "side_id = " + QString::number(this->getSideId(sideConditions[i]));
        }
        if(sideConditions.size() > 1)
            sideCondition = '(' + sideCondition + ')';
        herniaConditions.push_back(sideCondition);
    }

    if(this->m_treeViewModel->elementIsChecked("Рецидив"))
        herniaConditions.push_back("recurrence = true");

    // Добавление в общий список условий критериев по грыжам

    if(!herniaConditions.isEmpty())
    {
        QString condition;
        for(int i = 0; i < herniaConditions.size(); ++i)
        {
            if(i != 0) condition += " AND ";
            condition += herniaConditions[i];
        }
        condition = "id IN (SELECT card_id FROM Hernias WHERE " + condition + ')';
        qDebug() << "Hernia condition";
        qDebug() << condition;
        conditionsList.push_back(condition);
    }


    // Операции

    // в списке условий все условия (техника, сетки, и т д) объединяются логическим "И"
    // внутри каждого условия используется "ИЛИ" (например, техника == Bassini ИЛИ техника == Lichtenstein)
    QStringList operationConditions;

    QStringList operationTechniqueConditions;

    if(this->m_treeViewModel->childrenAreChecked("Техника натяжного способа"))
    {
        int tensionMethodId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");
        QStringList tensionTechniques = this->m_treeViewModel->getCheckedChildren("Техника натяжного способа");
        QString tensionTechniqueCondition;

        if(!this->m_treeViewModel->allChildrenAreChecked("Техника натяжного способа"))
        {
            for(int i = 0; i < tensionTechniques.size(); ++i)
            {
                if(i > 0) tensionTechniqueCondition += " OR ";
                int techId = this->getTissueRepairTechniqueId(tensionTechniques[i]);
                tensionTechniqueCondition += "technique_id = " + QString::number(techId);
            }
        }

        /*
         * id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM Operations
         * WHERE method_id = tensionMethodId AND (tensionTechniqueCondition)))
         *
         *
         * */

        QString tensionOperationCondition;

        if(tensionTechniqueCondition.isEmpty())
        {
            tensionOperationCondition = QString("(id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM Operations "
                                                "WHERE method_id = %1)))").arg(tensionMethodId);
        }

        else
        {
            tensionOperationCondition = QString("(id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM Operations "
                                                "WHERE method_id = %1 AND (%2))))").arg(tensionMethodId).arg(tensionTechniqueCondition);
        }


        operationTechniqueConditions.push_back(tensionOperationCondition);
    }

    if(this->m_treeViewModel->childrenAreChecked("Техника ненатяжного способа"))
    {
        int nonTensionMethodId = getIDByFieldData("OperationTechniques", "technique", "Ненатяжной способ");
        QStringList nonTensionTechniques = this->m_treeViewModel->getCheckedChildren("Техника ненатяжного способа");
        QString nonTensionTechniqueCondition;

        if(!this->m_treeViewModel->allChildrenAreChecked("Техника ненатяжного способа"))
        {
            for(int i = 0; i < nonTensionTechniques.size(); ++i)
            {
                if(i > 0) nonTensionTechniqueCondition += " OR ";
                int techId = this->getMeshImplantRepairTechniqueId(nonTensionTechniques[i]);
                nonTensionTechniqueCondition += "technique_id = " + QString::number(techId);
            }
        }

        QString nonTensionOperationCondition;

        if(nonTensionTechniqueCondition.isEmpty())
        {
            nonTensionOperationCondition = QString("(id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM Operations "
                                                "WHERE method_id = %1)))").arg(nonTensionMethodId);
        }

        else
        {
            nonTensionOperationCondition = QString("(id IN (SELECT card_id FROM Hernias WHERE id IN "
                                                "(SELECT hernia_id FROM Operations "
                                                "WHERE method_id = %1 "
                                                "AND (%2))))").arg(nonTensionMethodId).arg(nonTensionTechniqueCondition);
        }

        operationTechniqueConditions.push_back(nonTensionOperationCondition);
    }

    // объединяем условия для ненатяжного и натяжного способа логическим ИЛИ


    if(!operationTechniqueConditions.isEmpty())
    {
        QString operationTechniqueCondition = operationTechniqueConditions.join(" OR ");
        operationTechniqueCondition.push_front("(");
        operationTechniqueCondition.push_back(")");
        operationConditions.push_back(operationTechniqueCondition);
    }



    if(this->m_treeViewModel->childrenAreChecked("Тип сетки"))
    {
        if(!this->m_treeViewModel->allChildrenAreChecked("Тип сетки"))
        {
            QStringList meshesConditions;
            for(auto mesh: this->m_treeViewModel->getCheckedChildren("Тип сетки"))
            {
                int meshId = this->getMeshId(mesh);
                QString cond = "mesh_id = " + QString::number(meshId);
                meshesConditions.push_back(cond);
            }
            QString meshesCondition = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                                      "(SELECT hernia_id FROM"
                                      " NonTensionOperations WHERE %1)))";
            meshesCondition = meshesCondition.arg(meshesConditions.join(" OR "));
            operationConditions.push_back(meshesCondition);
        }

        else
        {
            QString cond = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                           "(SELECT hernia_id FROM NonTensionOperations)))";
            operationConditions.push_back(cond);
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Тип фиксации"))
    {
        if(!this->m_treeViewModel->allChildrenAreChecked("Тип фиксации"))
        {
            QStringList fixConditions;
            for(auto fix: this->m_treeViewModel->getCheckedChildren("Тип фиксации"))
            {
                if(fix == "Сетка не фиксировалась")
                    fixConditions.push_back("fixation_id IS NULL");
                else
                {
                    int fixId = this->getFixationTypeId(fix);
                    QString cond = "fixation_id = " + QString::number(fixId);
                    fixConditions.push_back(cond);
                }
            }
            QString fixCondition = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                                      "(SELECT hernia_id FROM"
                                      " NonTensionOperations WHERE %1)))";
            fixCondition = fixCondition.arg(fixConditions.join(" OR "));
            operationConditions.push_back(fixCondition);
        }
        else
        {
            QString cond = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                           "(SELECT hernia_id FROM NonTensionOperations)))";
            operationConditions.push_back(cond);
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Тип такеров"))
    {
        if(!this->m_treeViewModel->allChildrenAreChecked("Тип такеров"))
        {
            QStringList tuckersConditions;
            for(auto tucker: this->m_treeViewModel->getCheckedChildren("Тип такеров"))
            {
                int tuckerId = this->getTuckersId(tucker);
                QString cond = "tuckers_id = " + QString::number(tuckerId);
                tuckersConditions.push_back(cond);
            }

            QString tuckersCondition = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                                      "(SELECT hernia_id FROM"
                                      " NonTensionOperations WHERE %1)))";
            tuckersCondition = tuckersCondition.arg(tuckersConditions.join(" OR "));
            operationConditions.push_back(tuckersCondition);
        }
        else
        {
            QString cond = "(id IN (SELECT card_id FROM Hernias WHERE id IN "
                           "(SELECT hernia_id FROM NonTensionOperations WHERE tuckers_id IS NOT NULL)))";
            operationConditions.push_back(cond);
        }
    }

    if(this->m_treeViewModel->childrenAreChecked("Осложнения"))
    {
        QStringList complicationsConditions;
        for(auto comp: this->m_treeViewModel->getCheckedChildren("Осложнения"))
        {
            if(comp == "Интраоперационные")
                complicationsConditions.push_back("intraoperative_complications = true");
            else if(comp == "Ранние послеоперационные")
                complicationsConditions.push_back("early_complications = true");
            else if(comp == "Поздние послеоперационные")
                complicationsConditions.push_back("late_complications = true");
        }
        QString complicationsCondition = "id IN (SELECT card_id FROM Hernias WHERE id IN (SELECT hernia_id FROM Operations WHERE %1))";
        complicationsCondition = complicationsCondition.arg(complicationsConditions.join(" OR "));
        operationConditions.push_back(complicationsCondition);
    }



    if(!operationConditions.isEmpty())
    {
        QString operationCondition = operationConditions.join(" AND ");
        operationCondition.push_front("(");
        operationCondition.push_back(")");
//        qDebug() << "Условие по операциям: ";
//        qDebug() << operationCondition;
//        qDebug() << "";
        conditionsList.push_back(operationCondition);
    }


    // *************************************************************************

    if(!conditionsList.isEmpty())
    {
        QString query = "SELECT id, sex, birth_date, region_id FROM PatientCards WHERE ";
        for(int i = 0; i < conditionsList.size(); ++i)
        {
            if(i != 0)
                query += "AND ";
            query += conditionsList[i] + " ";
        }
        qDebug() << query;
        QSqlQuery q(this->m_db);
        q.prepare(query);
        q.exec();
        while(q.next())
        {
            int id = q.value(0).toInt();
            QString sex = q.value(1).toString();
            QString birthDate = q.value(2).toString();
            QString region = this->getRegionByID(q.value(3).toInt());
            results.push_back(new StatisticsListElement(id, sex, birthDate, region, this));
        }
    }

    return results;
}

QList<QObject *> DBWorker::getRegistrationRequests()
{
  QList<QObject*> requests;
  QSqlQuery q(this->m_db);
  q.prepare("SELECT * FROM Doctors WHERE user_id IN (SELECT id FROM Users WHERE statusId = ?)");
  q.addBindValue(STATUS_DOCTOR_REQUEST);
  q.exec();

  while(q.next())
  {
      int doctorId = q.value(0).toInt();
      QString fio = q.value(2).toString();
      QString birthDate = MyFunctions::dateToNormalFormat(q.value(3).toString());
      int experience = q.value(4).toInt();
      QString region = this->getRegionByID(q.value(5).toInt());
      QString locality = q.value(6).toString();
      QString mainWork = q.value(7).toString();
      QString extraWork = q.value(8).toString();
      QString speciality = q.value(9).toString();
      QString certificate = q.value(10).toString();
      QString email = q.value(11).toString();

      QObject* request = new RequestInfo(doctorId, fio, birthDate, experience, region, locality,
                                         mainWork,extraWork,speciality,certificate,email,this);
      requests.push_back(request);
  }
  return requests;

  /*
   * if(createTable("Doctors",
                 "id INTEGER UNIQUE PRIMARY KEY, "
                 "user_id INTEGER"
                 "fio VARCHAR(60), "
                 "birth_date DATE, "
                 "experience INTEGER, "
                 "region_id INTEGER, "
                 "locality VARCHAR(50), "
                 "work_main VARCHAR(120), "
                 "work_extra VARCHAR(120), "
                 "specialty VARCHAR(100), "
                 "certificate VARCHAR(30), "
                 "email VARCHAR(40)"));
                 */

}

QList<QObject *> DBWorker::getHerniasModel(int cardId)
{
    /*explicit HerniaInfo(int id, const QString& type, const QString& typeInfo, const QString& side, bool operation,
                        const QString& operationInfo, bool recurrence, QObject *parent = nullptr);*/
    QList<QObject*> list;
    QSqlQuery q(this->m_db);

    q.prepare("SELECT id, side_id, recurrence FROM Hernias WHERE card_id = ? ORDER BY id");
    q.addBindValue(cardId);
    q.exec();
    int number = 1;
    while(q.next())
    {
        int herniaId = q.value(0).toInt();
        QString side = this->getSideById(q.value(1).toInt());
        bool recurrence = q.value(2).toBool();
        QString type = this->getHerniaType(herniaId);
        QString typeInfo;
        if(type == "Паховая")
        {
            typeInfo = this->getGroinHerniaType(herniaId);
        }
        else if(type == "Послеоперационная вентральная")
        {
            typeInfo = this->getVentralHerniaType(herniaId) + ", " + this->getVentralHerniaSubtype(herniaId);
        }

        QSqlQuery q(this->m_db);
        q.prepare("SELECT * FROM Operations WHERE hernia_id = ?");
        q.addBindValue(herniaId);
        q.exec();
        bool operation = q.next();
        QString operationInfo;
        if(operation)
        {
            operationInfo = this->getOperationMethod(herniaId) + ", " + this->getOperationTechnique(herniaId);
        }

        list.push_back(new HerniaListElement(herniaId, number, type, typeInfo,
                                             side, operation, operationInfo, recurrence, this));
        ++number;
    }

    return list;
}



bool DBWorker::riskFactorsArePresent(int cardId)
{
    return this->recordExists("RiskFactors", "card_id", cardId);
}

QString DBWorker::getOccupationById(int id)
{
    return this->getFieldDataByID("Occupations", "occupation", id);
}

QString DBWorker::getSportActivitiesById(int id)
{
    return this->getFieldDataByID("SportActivities", "activity", id);
}

QString DBWorker::getSmokingHistoriesById(int id)
{
    return this->getFieldDataByID("SmokingHistories", "history", id);
}

QString DBWorker::getSideById(int id)
{
    return this->getFieldDataByID("Sides", "side", id);
}

QString DBWorker::getHerniaType(int herniaId)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM VentralHernias WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next())  // Если грыжа вентральная
    {
        return QString("Послеоперационная вентральная");
    }
    return QString("Паховая");
}

QString DBWorker::getVentralHerniaType(int herniaId)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM VentralHerniaTypes WHERE id IN (SELECT type_id FROM VentralHernias WHERE hernia_id = ?)");
    q.addBindValue(herniaId);
    if(!q.exec())
        return "";
    if(!q.next())
        return "";
    return q.value(0).toString();
}

QString DBWorker::getVentralHerniaSubtype(int herniaId)
{
    QString type = this->getVentralHerniaType(herniaId);
    if(type == "Срединная")
    {
        QSqlQuery q(this->m_db);
        q.prepare("SELECT type FROM VentralMidlineHerniaTypes WHERE id IN (SELECT subtype_id FROM VentralHernias WHERE hernia_id = ?)");
        q.addBindValue(herniaId);
        if(!q.exec())
            return "";
        if(!q.next())
            return "";
        return q.value(0).toString();
    }
    else if(type == "Латеральная")
    {
        QSqlQuery q(this->m_db);
        q.prepare("SELECT type FROM VentralLateralHerniaTypes WHERE id IN (SELECT subtype_id FROM VentralHernias WHERE hernia_id = ?)");
        q.addBindValue(herniaId);
        if(!q.exec())
            return "";
        if(!q.next())
            return "";
        return q.value(0).toString();
    }
    return "";
}

QString DBWorker::getGroinHerniaType(int herniaId)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM GroinHerniaTypes WHERE id IN "
              "(SELECT type_id FROM GroinHernias WHERE hernia_id = ?)");
    q.addBindValue(herniaId);
    if(!q.exec())
        return "";
    if(!q.next())
        return "";
    return q.value(0).toString();
}

QString DBWorker::getOperationMethod(int herniaId)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT technique FROM OperationTechniques WHERE id IN "
              "(SELECT method_id FROM Operations WHERE hernia_id = ?)");
    q.addBindValue(herniaId);
    if(!q.exec())
        return "";
    if(!q.next())
        return "";
    return q.value(0).toString();
}

QString DBWorker::getOperationTechnique(int herniaId)
{
    QString method = this->getOperationMethod(herniaId);
    if(method == "Натяжной способ")
    {
        QSqlQuery q(this->m_db);
        q.prepare("SELECT technique FROM TissueRepairTechniques WHERE id IN "
                  "(SELECT technique_id FROM Operations WHERE hernia_id = ?)");
        q.addBindValue(herniaId);
        if(!q.exec())
            return "";
        if(!q.next())
            return "";
        return q.value(0).toString();
    }
    else if(method == "Ненатяжной способ")
    {
        QSqlQuery q(this->m_db);
        q.prepare("SELECT technique FROM MeshImplantRepairTechniques WHERE id IN "
                  "(SELECT technique_id FROM Operations WHERE hernia_id = ?)");
        q.addBindValue(herniaId);
        if(!q.exec())
            return "";
        if(!q.next())
            return "";
        return q.value(0).toString();
    }
    return "";
}

QString DBWorker::getMeshById(int id)
{
    return this->getFieldDataByID("Meshes", "mesh", id);
}



int DBWorker::getOccupationId(const QString &occupation)
{
    return this->getIDByFieldData("Occupations", "occupation", occupation);
}

int DBWorker::getSportActivitiesId(const QString &sportActivities)
{
    return this->getIDByFieldData("SportActivities", "activity", sportActivities);
}

int DBWorker::getSmokingHistoryId(const QString &smokingHistory)
{
    return this->getIDByFieldData("SmokingHistories", "history", smokingHistory);
}

int DBWorker::getSideId(const QString &side)
{
    return this->getIDByFieldData("Sides", "side", side);
}

int DBWorker::getVentralHerniaTypeId(const QString &ventralHerniaType)
{
    return this->getIDByFieldData("VentralHerniaTypes", "type", ventralHerniaType);
}

int DBWorker::getVentralMidlineHerniaTypeId(const QString &ventralMidlineHerniaType)
{
    return this->getIDByFieldData("VentralMidlineHerniaTypes", "type", ventralMidlineHerniaType);
}

int DBWorker::getVentralLateralHerniaTypeId(const QString &ventralLateralHerniaType)
{
    return this->getIDByFieldData("VentralLateralHerniaTypes", "type", ventralLateralHerniaType);
}

int DBWorker::getVentralHerniaWidthId(const QString &ventralHerniaWidth)
{
    return this->getIDByFieldData("VentralHerniaWidths", "width", ventralHerniaWidth);
}

int DBWorker::getGroinHerniaTypeId(const QString &groinHerniaType)
{
    return this->getIDByFieldData("GroinHerniaTypes", "type", groinHerniaType);
}

int DBWorker::getGroinHerniaExaminationId(const QString &examination)
{
    return this->getIDByFieldData("GroinHerniaExaminations", "examination", examination);
}

int DBWorker::getDiagnosticMethodId(const QString &method)
{
    return this->getIDByFieldData("DiagnosticMethods", "method", method);
}

int DBWorker::getMeshId(const QString &mesh)
{
    return this->getIDByFieldData("Meshes", "mesh", mesh);
}

int DBWorker::getTuckersId(const QString &tuckers)
{
    return this->getIDByFieldData("Tuckers", "tucker", tuckers);
}

int DBWorker::getFixationTypeId(const QString &fixation)
{
    return this->getIDByFieldData("FixationTypes", "type", fixation);
}

int DBWorker::getPeritoneumClosureId(const QString &peritoneumClosure)
{
    return this->getIDByFieldData("PeritoneumClosures", "closure", peritoneumClosure);
}

int DBWorker::getOperationTechniqueId(const QString &technique)
{
    return this->getIDByFieldData("OperationTechniques", "technique", technique);
}

int DBWorker::getTissueRepairTechniqueId(const QString &technique)
{
    return this->getIDByFieldData("TissueRepairTechniques", "technique", technique);
}

int DBWorker::getMeshImplantRepairTechniqueId(const QString &technique)
{
    return this->getIDByFieldData("MeshImplantRepairTechniques", "technique", technique);
}

int DBWorker::getSeromaSizeId(const QString &seromaSize)
{
    return this->getIDByFieldData("SeromaSizes", "size", seromaSize);
}

int DBWorker::insertNewMesh(const QString &mesh)
{
    int id = this->getIDForInsert("Meshes");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO Meshes (id, mesh) VALUES (?,?)");
    q.addBindValue(id);
    q.addBindValue(mesh);
    if(!q.exec()) return -1;
    return id;
}

int DBWorker::insertNewFixationType(const QString &fixation)
{
    int id = this->getIDForInsert("FixationTypes");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO FixationTypes (id, type) VALUES (?,?)");
    q.addBindValue(id);
    q.addBindValue(fixation);
    if(!q.exec()) return -1;
    return id;
}

int DBWorker::insertNewTuckers(const QString &tuckers)
{
    int id = this->getIDForInsert("Tuckers");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO Tuckers (id, tucker) VALUES (?,?)");
    q.addBindValue(id);
    q.addBindValue(tuckers);
    if(!q.exec()) return -1;
    return id;
}

QObject *DBWorker::getMainCardInfo(int cardId)
{
    QSqlQuery q = this->patientCardQuery(cardId);

    /*
     *  if(createTable("PatientCards",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "sex VARCHAR(1), "
                   "phone VARCHAR(16), "
                   "region_id TINYINT, "
                   "district VARCHAR(60), "
                   "locality VARCHAR(50), "
                   "street VARCHAR(60), "
                   "house VARCHAR(30), "
                   "flat SMALLINT, "
                   "passport VARCHAR(11), "
                   "snils VARCHAR(14), "
                   "polis_type VARCHAR(3), "
                   "polis_number VARCHAR(16), "
                   "blood_type VARCHAR(3), "
                   "rhesus_factor VARCHAR(1), "
                   "weight SMALLINT, "
                   "height SMALLINT, "
                   "complaints VARCHAR(300)")) */


    QString fio = q.value(1).toString();
    QString birthDate = MyFunctions::dateToNormalFormat(q.value(2).toString());
    QString sex = q.value(3).toString();
    QString phone = q.value(4).toString();
    int regionId = q.value(5).toInt();
    QString district = q.value(6).toString();
    QString locality = q.value(7).toString();
    QString street = q.value(8).toString();
    QString house = q.value(9).toString();
    QString flat = q.value(10).toString();
    QString passport = q.value(11).toString();
    QString snils = q.value(12).toString();
    QString polisType = q.value(13).toString();
    QString polisNumber = q.value(14).toString();
    QString bloodType = q.value(15).toString();
    QString rhesusFactor = q.value(16).toString();
    int weight = q.value(17).toInt();
    int height = q.value(18).toInt();
    QString complaints = q.value(19).toString();

    QObject *mainCardInfo = new MainCardInfo(fio,birthDate,sex,phone,regionId,district,locality,
                                             street,house,flat,passport,snils, polisType, polisNumber,
                                             bloodType, rhesusFactor, weight, height, complaints, this);

    /*
     * explicit MainCardInfo(const QString& fio, const QString& birthDate,const QString& sex, const QString& phone,
                          int regionId, const QString& district, const QString& locality, const QString& street,
                          const QString& house,int flat,const QString& passport,const QString& snils,
                          const QString& polisType, const QString& polisNumber, const QString& bloodType,
                          const QString& rhesusFactor, int weight,int height,
                          const QString& complaints, QObject *parent = nullptr);*/


    return mainCardInfo;

}

QObject *DBWorker::getRiskFactorsInfo(int cardId)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM RiskFactors WHERE card_id = ?");
    q.addBindValue(cardId);
    q.exec();
    q.next();

    int occupationId = q.value(2).toInt();
    int sportActivitiesId = q.value(3).toInt();
    int smokingHistoryId = q.value(4).toInt();
    int cigsPerDay = q.value(5).toInt();
    int yearsOfSmoking = q.value(6).toInt();
    bool diabetesI = q.value(7).toBool();
    bool diabetesII = q.value(8).toBool();
    bool hobl = q.value(9).toBool();
    bool hypertension = q.value(10).toBool();
    bool heartDisease = q.value(11).toBool();
    bool kidneyDisease = q.value(12).toBool();
    bool gastritis = q.value(13).toBool();
    bool ulcer = q.value(14).toBool();
    bool aorticAneurism = q.value(15).toBool();
    bool immunosuppression = q.value(16).toBool();
    bool coagulopathy = q.value(17).toBool();
    bool plateletAggregationInhibitors = q.value(18).toBool();
    QString otherFactors = q.value(19).toString();

    QObject *info = new RiskFactorsInfo(occupationId,sportActivitiesId,smokingHistoryId,cigsPerDay,yearsOfSmoking,
                                        diabetesI,diabetesII,hobl,hypertension,heartDisease,kidneyDisease,
                                        gastritis,ulcer,aorticAneurism,immunosuppression,coagulopathy,
                                        plateletAggregationInhibitors,otherFactors,this);
    return info;
}

QObject *DBWorker::getHerniaInfo(int herniaId)
{


    QString herniaType = this->getHerniaType(herniaId);
    QSqlQuery q(this->m_db);
    q.prepare("SELECT side_id, recurrence FROM Hernias WHERE id = ?");
    q.addBindValue(herniaId);
    q.exec(); q.next();
    QString side = this->getSideById(q.value(0).toInt());
    bool recurrence = q.value(1).toBool();

    /*explicit HerniaInfo(const QString& herniaType, const QString& herniaSide, bool recurrence,
                        QObject *parent = nullptr);*/
    QObject* info = new HerniaInfo(herniaType, side, recurrence, this);
    HerniaInfo* herniaInfo = qobject_cast<HerniaInfo*>(info); // чтобы можно было вызывать методы для добавления информации
    if(herniaType == "Послеоперационная вентральная")
    {
        /*void setVentralHerniaInfo(const QString& ventralHerniaType, const QString& ventralHerniaSubtype,
         *                  const QString& ventralHerniaWidth,
                              int ventralHerniaLength);*/
        QString ventralHerniaType = this->getVentralHerniaType(herniaId);
        QString ventralHerniaSubtype = this->getVentralHerniaSubtype(herniaId);
        q.prepare("SELECT width_id, length FROM VentralHernias WHERE hernia_id = ?");
        q.addBindValue(herniaId);
        q.exec(); q.next();
        int widthId = q.value(0).toInt();
        int length = q.value(1).toInt();
        QString width = this->getFieldDataByID("VentralHerniaWidths", "width", widthId);
        herniaInfo->setVentralHerniaInfo(ventralHerniaType, ventralHerniaSubtype, width, length);
    }
    else if(herniaType == "Паховая")
    {
        //void setGroinHerniaInfo(const QString& groinHerniaType, const QString& groinHerniaExamination);
        QString groinHerniaType = this->getGroinHerniaType(herniaId);
        q.prepare("SELECT examination FROM GroinHerniaExaminations WHERE id IN "
                  "(SELECT examination_id FROM GroinHernias WHERE hernia_id = ?)");
        q.addBindValue(herniaId);
        q.exec(); q.next();
        QString examination = q.value(0).toString();
        herniaInfo->setGroinHerniaInfo(groinHerniaType, examination);
    }

    q.prepare("SELECT method_id, ring_width, sac_width, sac_length FROM Diagnostics WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    QList<int> clinicalExamination;
    QList<int> uziDorsal;
    QList<int> uziStanding;
    QList<int> kt;
    QList<int> mrt;
    while(q.next())
    {
        int methodId = q.value(0).toInt();
        int ringWidth = q.value(1).toInt();
        int sacWidth = q.value(2).toInt();
        int sacLength = q.value(3).toInt();
        switch(methodId)
        {
        case 1:
            clinicalExamination.push_back(ringWidth);
            clinicalExamination.push_back(sacWidth);
            clinicalExamination.push_back(sacLength);
            break;

        case 2:
            uziDorsal.push_back(ringWidth);
            uziDorsal.push_back(sacWidth);
            uziDorsal.push_back(sacLength);
            break;
        case 3:
            uziStanding.push_back(ringWidth);
            uziStanding.push_back(sacWidth);
            uziStanding.push_back(sacLength);
            break;
        case 4:
            kt.push_back(ringWidth);
            kt.push_back(sacWidth);
            kt.push_back(sacLength);
            break;
        case 5:
            mrt.push_back(ringWidth);
            mrt.push_back(sacWidth);
            mrt.push_back(sacLength);
            break;
        }
    }
    /*void setDiagnosticsInfo(const QList<int>& clinicalExamination, const QList<int>& uziDorsal, const QList<int>& uziStanding,
                        const QList<int>& kt, const QList<int>& mrt);*/
    if(!clinicalExamination.isEmpty() || !uziDorsal.isEmpty() ||
            !uziStanding.isEmpty() || !kt.isEmpty() || !mrt.isEmpty())
        herniaInfo->setDiagnosticsInfo(clinicalExamination, uziDorsal, uziStanding, kt, mrt);

    q.prepare("SELECT preoperation_pain_in_rest_degree, preoperation_pain_in_motion_degree FROM Hernias "
              "WHERE id = ?");
    q.addBindValue(herniaId);
    q.exec(); q.next();
    if(!q.value(0).isNull())
    {
        int degree = q.value(0).toInt();
        // void setPreoperativePainInRestInfo(int degree);
        herniaInfo->setPreoperativePainInRestInfo(degree);
    }
    if(!q.value(1).isNull())
    {
        int degree = q.value(1).toInt();
        // void setPreoperativePainInMotionInfo(int degree);
        herniaInfo->setPreoperativePainInMotionInfo(degree);
    }

//    void setOperationInfo(const QString& operationSide, int ringWidth, int sacWidth, int sacLength,
//                            const QString& method, const QString& tecnique,
//                             bool nerveInjury);
    q.prepare("SELECT side_id, ring_width, sac_width, sac_length, nerve_injury FROM Operations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next())
    {
        QString operationSide;

        if(!q.value(0).isNull())
            operationSide = this->getSideById(q.value(0).toInt());
        int ringWidth = q.value(1).toInt();
        int sacWidth = q.value(2).toInt();
        int sacLength = q.value(3).toInt();
        bool nerveInjury = q.value(4).toBool();
        QString method = this->getOperationMethod(herniaId);
        QString technique = this->getOperationTechnique(herniaId);
        herniaInfo->setOperationInfo(operationSide, ringWidth, sacWidth, sacLength, method, technique, nerveInjury);
    }



    q.prepare("SELECT mesh_id, mesh_width, mesh_length, fixation_id, tuckers_id, "
              "peritoneum_closure_id, drainage FROM NonTensionOperations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next())
    {
        int meshId = q.value(0).toInt();
        int meshWidth = q.value(1).toInt();
        int meshLength = q.value(2).toInt();
        bool drainage = q.value(6).toBool();
        QString mesh, fixation, tuckers, peritoneumClosure;
        //if(meshId != 0)
        mesh = this->getFieldDataByID("Meshes", "mesh", meshId);
        if(!q.value(3).isNull())
            fixation = this->getFieldDataByID("FixationTypes", "type", q.value(3).toInt());
        if(!q.value(4).isNull())
            tuckers = this->getFieldDataByID("Tuckers", "tucker", q.value(4).toInt());
        if(!q.value(5).isNull())
            peritoneumClosure = this->getFieldDataByID("PeritoneumClosures", "closure", q.value(5).toInt());
        //    void setNonTensionOperationInfo(const QString& mesh, int meshWidth, int meshLength,
        //                                    const QString& fixationType, const QString& tuckers,
        //                                    const QString& peritoneumClosure, bool drainage);
        herniaInfo->setNonTensionOperationInfo(mesh, meshWidth, meshLength, fixation, tuckers, peritoneumClosure, drainage);
    }


    q.prepare("SELECT intraoperative_complications, hemorrhage, nerve_damage, spermatic_cord_injury, "
              "bowel_injury FROM Operations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next() && q.value(0).toBool())
    {
        bool hemorrhage = q.value(1).toBool();
        bool nerveDamage = q.value(2).toBool();
        bool cordInjury = q.value(3).toBool();
        bool bowelInjury = q.value(4).toBool();
        //void setIntraoperativeComplicationsInfo(bool hemorrhage, bool nerveDamage, bool cordInjury, bool bowelInjury);
        herniaInfo->setIntraoperativeComplicationsInfo(hemorrhage, nerveDamage, cordInjury, bowelInjury);
    }

    /*void setEarlyPostoperativeComplicationsInfo(bool woundInfection, bool seroma, const QString& seromaSize,
                                                bool hematoma, bool cordSwelling, bool orchiepididymitis);*/
    q.prepare("SELECT early_complications, wound_infection, seroma, seroma_size_id, hematoma, spermatic_cord_swelling, "
              "orchiepididymitis FROM Operations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next() && q.value(0).toBool())
    {
        bool woundInfection = q.value(1).toBool();
        bool seroma = q.value(2).toBool();
        bool hematoma = q.value(4).toBool();
        bool cordSwelling = q.value(5).toBool();
        bool orchiepididymitis = q.value(6).toBool();
        QString seromaSize;
        if(seroma)
            seromaSize = this->getFieldDataByID("SeromaSizes", "size", q.value(3).toInt());
        herniaInfo->setEarlyPostoperativeComplicationsInfo(woundInfection, seroma, seromaSize,
                                                           hematoma, cordSwelling, orchiepididymitis);
    }


    q.prepare("SELECT late_complications, fistulas, mesh_rejection, "
              "chronic_inguinal_neuralgia, testicular_atrophy, recurrence FROM Operations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next() && q.value(0).toBool())
    {
        bool fistulas = q.value(1).toBool();
        bool meshRejection = q.value(2).toBool();
        bool chronicNeuralgia = q.value(3).toBool();
        bool testicularAtrophy = q.value(4).toBool();
        bool diseaseRecurrence = q.value(5).toBool();
        /*void setLatePostoperativeComplicationsInfo(bool fistulas, bool meshRejection, bool chronicNeuralgia,
                                               bool testicularAtrophy, bool diseaseRecurrence);*/
        herniaInfo->setLatePostoperativeComplicationsInfo(fistulas, meshRejection,
                                                          chronicNeuralgia, testicularAtrophy, diseaseRecurrence);
    }



    QList<bool> inRestList = {false, false, false} ;
    QList<int> inRestDegreeList = {0, 0, 0};

    QList<bool> inMotionList = {false, false, false} ;
    QList<int> inMotionDegreeList = {0, 0, 0};

    QList<bool> analgesicsList = {false, false, false} ;

    QList<int> analgesicsDaysList = {0, 0, 0};

    QList<bool> analgesicsOrallyList = {false, false, false} ;
    QList<int> orallyDaysList = {0, 0, 0};

    QList<bool> analgesicsInjectionsList = {false, false, false} ;
    QList<int> injectionsDaysList = {0, 0, 0};

    q.prepare("SELECT days_after_operation, pain_in_rest_degree, pain_in_motion_degree, "
              "analgesics, days_of_medication, "
              "orally, days_of_medication_orally, injections, "
              "days_of_medication_injections FROM EarlyPostOperativePain WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    while(q.next())
    {

        int daysAfterOperation = q.value(0).toInt();
        QVariant inRestDegree = q.value(1);
        QVariant inMotionDegree = q.value(2);
        bool analgesics = q.value(3).toBool();
        QVariant analgesicsDays = q.value(4);
        bool analgesicsOrally = q.value(5).toBool();
        QVariant orallyDays = q.value(6);
        bool analgesicsInjections = q.value(7).toBool();
        QVariant injectionsDays = q.value(8);

        int index = (daysAfterOperation == 1) ? 0 : (daysAfterOperation == 3) ? 1 : 2;
        if(!inRestDegree.isNull())
        {
            inRestList[index] = true;
            inRestDegreeList[index] = inRestDegree.toInt();
        }
        if(!inMotionDegree.isNull())
        {
            inMotionList[index] = true;
            inMotionDegreeList[index] = inMotionDegree.toInt();
        }
        if(analgesics)
        {
            analgesicsList[index] = true;
            analgesicsDaysList[index] = analgesicsDays.toInt();
            if(analgesicsOrally)
            {
                analgesicsOrallyList[index] = true;
                orallyDaysList[index] = orallyDays.toInt();
            }

            if(analgesicsInjections)
            {
                analgesicsInjectionsList[index] = true;
                injectionsDaysList[index] = injectionsDays.toInt();
            }
        }
    }

    herniaInfo->setEarlyPainInfo(inRestList, inRestDegreeList, inMotionList, inMotionDegreeList,
                                 analgesicsList, analgesicsDaysList,
                                 analgesicsOrallyList,
                                 orallyDaysList,
                                 analgesicsInjectionsList, injectionsDaysList);


    /*
     *
    void setChronicInRestPainInfo(int degree);
    void setChronicInMotionPainInfo(int degree);
    */

    q.prepare("SELECT chronic_pain_in_rest_degree, chronic_pain_in_motion_degree FROM Operations WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    if(q.next())
    {
        if(!q.value(0).isNull())
            herniaInfo->setChronicInRestPainInfo(q.value(0).toInt());
        if(!q.value(1).isNull())
            herniaInfo->setChronicInMotionPainInfo(q.value(1).toInt());
    }

    QStringList sources;
    QStringList descriptions;
    q.prepare("SELECT image, description FROM HerniaImages WHERE hernia_id = ?");
    q.addBindValue(herniaId);
    q.exec();
    int counter = 0;
    while(q.next())
    {
        ++counter;
//        if(counter == 1) // если есть хотя бы 1 изображение, то удаляем старое содержимое провайдера
//            this->m_imageProvider->clear();

        QByteArray byteArray = q.value(0).toByteArray();
        QString description = q.value(1).toString();
        QImage image;
        image.loadFromData(byteArray);
        QString imageId = "image_" + QString::number(counter);
        QString source = "image://provider/" + imageId;
        this->m_imageProvider->add(imageId, image, byteArray);
        sources.push_back(source);
        descriptions.push_back(description);
    }

    if(!sources.isEmpty())
        herniaInfo->setImages(sources, descriptions);





    return info;
}



bool DBWorker::passportExists(const QString &passport)
{
    return this->recordExists("PatientCards", "passport", passport);
}

bool DBWorker::snilsExists(const QString &snils)
{
    return this->recordExists("PatientCards", "snils", snils);
}

bool DBWorker::polisExists(const QString &polisType, const QString &polisNumber)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM PatientCards WHERE polis_type = ? AND polis_number = ?");
    q.addBindValue(polisType);
    q.addBindValue(polisNumber);
    if(!q.exec())
    {
        qDebug() << "Не удалось проверить существование полиса";
        return true;
    }
    return q.next();
}


bool DBWorker::registerUser(int userStatus, const QString& FIO, const QDate& birthDate, const QString& email,
                                    const QString& login, const QString& password)
{
    int statusID = userStatus;
//    switch(status)
//    {
//    case UserStatus::userStatus::Admin:
//        statusID = 1;
//        break;
//    case UserStatus::userStatus::Doctor:
//        statusID = 2;
//        break;
//    case UserStatus::userStatus::DoctorRequest:
//        statusID = 3;
//        break;
//    case UserStatus::userStatus::OrdinaryUser:
//        statusID = 4;
//        break;
//    }
    int userID = this->getIDForInsert("Users");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO Users (id, statusId, FIO, birth_date, email, login, password) VALUES (?,?,?,?,?,?,?)");
    q.addBindValue(userID);
    q.addBindValue(statusID);
    q.addBindValue(FIO);
    q.addBindValue(birthDate);
    q.addBindValue(email.toLower());
    q.addBindValue(login);
    q.addBindValue(password);
    if(!q.exec())
    {
        qDebug() << "Ошибка при добавлении пользователя в таблицу Users";
        return false;
    }
    return true;
}

bool DBWorker::makeDoctorRegRequest(const QString &FIO,
                              const QDate &birthDate,
                              int experience,
                              const QString &region, const QString &locality,
                              const QString &work_main,
                              const QString &work_extra,
                              const QString &specialty,
                              const QString &certificate,
                              const QString &email,
                              const QString &login,
                              const QString &password)
{
    if(!this->registerUser(STATUS_DOCTOR_REQUEST, FIO, birthDate, email, login, password))
        return false;

    int regionID = this->getIDByFieldData("Regions", "name", region);
    int doctorID = this->getIDForInsert("Doctors");
    int userID = this->maxID("Users");
    /*
     * if(createTable("Doctors",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "user_id INTEGER"
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "carier_start DATE, "
                   "experience INTEGER, "
                   "region_id INTEGER, "
                   "locality VARCHAR(50), "
                   "work_main VARCHAR(120), "
                   "work_extra VARCHAR(120), "
                   "specialty VARCHAR(100), "
                   "certificate VARCHAR(30), "
                   "email VARCHAR(40)"));
                   */
    QSqlQuery q;
    q.prepare("INSERT INTO Doctors (id, user_id, fio, birth_date, experience, region_id, locality, "
              "work_main, work_extra, "
               "specialty, certificate, email) VALUES (?,?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(doctorID);
    q.addBindValue(userID);
    //q.addBindValue(QVariant(QVariant::Int));
    q.addBindValue(FIO);
    q.addBindValue(birthDate);
    //q.addBindValue(carierStart);
    q.addBindValue(experience);
    q.addBindValue(regionID);
    q.addBindValue(locality);
    q.addBindValue(work_main);
    if(work_extra.isEmpty())
        q.addBindValue(QVariant(QVariant::String));
    else
        q.addBindValue(work_extra);
    q.addBindValue(specialty);
    q.addBindValue(certificate);
    q.addBindValue(email.toLower());
    if(!q.exec())
        return false;
    return true;
}

//void DBWorker::insertUserSession(int userID, const QDateTime &begin, const QDateTime &end)
//{
//    QSqlQuery q(this->m_db);
//    q.prepare("INSERT INTO UserSessions (id, user_id, begin, end) VALUES(?,?,?,?)");
//    q.addBindValue(this->getIDForInsert("UserSessions"));
//    q.addBindValue(userID);
//    q.addBindValue(begin);
//    q.addBindValue(end);
//    if(!q.exec())
//        qDebug() << "Не удалось добавить сессию пользователя";
//}

void DBWorker::insertAvailableCard(int userID, int cardID)
{
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO AvailablePatientCards (id, user_id, patient_card_id) VALUES(?,?,?)");
    q.addBindValue(this->getIDForInsert("AvailablePatientCards"));
    q.addBindValue(userID);
    q.addBindValue(cardID);
    if(!q.exec())
        qDebug() << "Не удалось добавить запись в таблицу \"Доступные карты пациентов\"";
}

bool DBWorker::insertPatientCard(
        int userID,
        const QString &fio,
        const QDate &birthDate,
        const QString &sex,
        const QString &phone,
        const QString &region,
        const QString &district,
        const QString &locality,
        const QString &street,
        const QString &house,
        const QString &flat,
        const QString &passport,
        const QString &snils,
        const QString &polisType,
        const QString &polisNumber,
        const QString &bloodType,
        const QString &rhesusFactor,
        const QString &weight,
        const QString &height,
        const QString &complaints)
{
    /*
    if(createTable("PatientCards",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "fio VARCHAR(60), "
                   "birth_date DATE, "
                   "sex VARCHAR(1), "
                   "phone VARCHAR(16), "
                   "region_id TINYINT, "
                   "district VARCHAR(60), "
                   "locality VARCHAR(50), "
                   "street VARCHAR(60), "
                   "house VARCHAR(30), "
                   "flat SMALLINT, "
                   "passport VARCHAR(11), "
                   "snils VARCHAR(14), "
                   "polis_type VARCHAR(3), "
                   "polis_number VARCHAR(16), "
                   "blood_type VARCHAR(3), "
                   "rhesus_factor VARCHAR(1), "
                   "weight SMALLINT, "
                   "height SMALLINT, "
                   "complaints VARCHAR(300)"))
                   */
    int id = this->getIDForInsert("PatientCards");
    int regionID = this->getIDByFieldData("Regions", "name", region);
    QString sex_insert = (sex == "Мужской") ? "М" : "Ж";\

    QString rhesusFactor_insert;
    if(rhesusFactor == "Rh+")
        rhesusFactor_insert = "+";
    else if(rhesusFactor == "Rh-")
        rhesusFactor_insert = "-";
    // иначе это будет пустая строка

//    int passportSeries_insert = passportSeries.toInt();
//    int passportNumber_insert = passportNumber.toInt();
//    int weight_insert = weight.toInt();
//    int height_insert = height.toInt();

    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO PatientCards ("
              "id, fio, birth_date, sex, phone, region_id, district, locality, "
              "street, house, flat, passport, snils, polis_type, "
              "polis_number, blood_type, rhesus_factor, weight, height, complaints) "
              "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(fio);
    q.addBindValue(birthDate);
    q.addBindValue(sex_insert);
    q.addBindValue(phone);
    q.addBindValue(regionID);
    if(district.isEmpty())
        q.addBindValue(QVariant(QVariant::String));
    else
        q.addBindValue(district);
    q.addBindValue(locality);
    q.addBindValue(street);
    q.addBindValue(house);
    if(flat.isEmpty())
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(flat.toInt());
    q.addBindValue(passport);
    q.addBindValue(snils);
    q.addBindValue(polisType);
    q.addBindValue(polisNumber);
    q.addBindValue(bloodType);
    q.addBindValue(rhesusFactor_insert);
    q.addBindValue(weight);
    q.addBindValue(height);
    q.addBindValue(complaints);
    if(!q.exec())
        return false;
    this->insertAvailableCard(userID, id);
    return true;
}



bool DBWorker::insertRiskFactors(int cardId,
                                 int occupationId,
                                 int sportActivitiesId,
                                 int smokingHistoryId,
                                 const QString& cigsPerDay,
                                 const QString& yearsOfSmoking,
                                 bool diabetesI,
                                 bool diabetesII,
                                 bool hobl,
                                 bool hypertension,
                                 bool heartDisease,
                                 bool kidneyDisease,
                                 bool gastritis,
                                 bool ulcer,
                                 bool aorticAneurysm,
                                 bool immunosuppression,
                                 bool coagulopathy,
                                 bool plateletAggregationInhibitors,
                                 const QString& otherFactors)
{

    int id = this->getIDForInsert("RiskFactors");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO RiskFactors ("
              "id , "
              "card_id , "
              "occupation_id ,"
              "sporting_activities_id , "
              "smoking_history_id , "
              "cigs_per_day , "
              "years_of_smoking , "
              "diabetes_I , "
              "diabetes_II , "
              "hobl , "
              "hypertension , "
              "heart_disease , "
              "kidney_disease , "
              "gastritis , "
              "ulcer, "
              "aortic_aneurysm , "
              "immunosuppression , "
              "coagulopathy , "
              "platelet_aggregation_inhibitors , "
              "other_factors) "
              "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(cardId);
    q.addBindValue(occupationId);
    q.addBindValue(sportActivitiesId);
    q.addBindValue(smokingHistoryId);

    if(!cigsPerDay.isEmpty())
        q.addBindValue(cigsPerDay);
    else
        q.addBindValue(QVariant(QVariant::Int));

    if(!yearsOfSmoking.isEmpty())
        q.addBindValue(yearsOfSmoking);
    else
        q.addBindValue(QVariant(QVariant::Int));



    q.addBindValue(diabetesI);
    q.addBindValue(diabetesII);
    q.addBindValue(hobl);
    q.addBindValue(hypertension);
    q.addBindValue(heartDisease);
    q.addBindValue(kidneyDisease);
    q.addBindValue(gastritis);
    q.addBindValue(ulcer);
    q.addBindValue(aorticAneurysm);
    q.addBindValue(immunosuppression);
    q.addBindValue(coagulopathy);
    q.addBindValue(plateletAggregationInhibitors);
    q.addBindValue(otherFactors);

    return q.exec();
}

int DBWorker::insertHernia(int cardId,
                           const QString &side,
                           bool recurrence, int preoperativePainInRestDegree,
                           int preoperativePainInMotionDegree)
{
    int id = this->getIDForInsert("Hernias");
    int sideId = this->getSideId(side);
    QSqlQuery q(this->m_db);

    q.prepare("INSERT INTO Hernias (id, card_id, side_id, recurrence, "
              "preoperation_pain_in_rest_degree,preoperation_pain_in_motion_degree) "
              "VALUES(?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(cardId);
    q.addBindValue(sideId);
    q.addBindValue(recurrence);
    if(preoperativePainInRestDegree < 0)
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(preoperativePainInRestDegree);
    if(preoperativePainInMotionDegree < 0)
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(preoperativePainInMotionDegree);

    if(!q.exec())
        return 0;
    return id;
}

bool DBWorker::insertVentralHernia(int herniaId, const QString &type,
                                   const QString &subtype, const QString &width,
                                   const QString &length)
{
    /*if(createTable("VentralHernias",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "type_id TINYINT UNSIGNED, "
                   "subtype_id TINYINT UNSIGNED, "
                   "width_id TINYINT UNSIGNED, "
                   "length TINYINT UNSIGNED"))*/
    int id = this->getIDForInsert("VentralHernias");
    int typeId = this->getVentralHerniaTypeId(type);
    int subtypeId = (type == "Срединная") ?
                this->getVentralMidlineHerniaTypeId(subtype) : this->getVentralLateralHerniaTypeId(subtype);
    int widthId = this->getVentralHerniaWidthId(width);
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO VentralHernias "
              "(id, hernia_id, type_id, subtype_id, width_id, length) "
              "VALUES(?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);
    q.addBindValue(typeId);
    q.addBindValue(subtypeId);
    q.addBindValue(widthId);
    q.addBindValue(length);

    return q.exec();
}

bool DBWorker::insertGroinHernia(int herniaId, const QString &type, const QString &examination)
{
    /*if(createTable("GroinHernias",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "type_id TINYINT UNSIGNED, "
                   "examination_id TINYINT UNSIGNED"
                   ))*/
    int id = this->getIDForInsert("GroinHernias");
    int typeId = this->getGroinHerniaTypeId(type);
    int examinationId = this->getGroinHerniaExaminationId(examination);
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO GroinHernias (id, hernia_id, type_id, examination_id) VALUES (?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);
    q.addBindValue(typeId);
    q.addBindValue(examinationId);

    return q.exec();
}

bool DBWorker::insertDiagnostics(int herniaId, const QString &method,
                                 const QString &ringWidth, const QString &sacWidth,
                                 const QString &sacLength)
{
    int id = this->getIDForInsert("Diagnostics");
    int methodId = this->getDiagnosticMethodId(method);
    QSqlQuery q(this->m_db);
    /*if(createTable("Diagnostics",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "method_id TINYINT UNSIGNED, "
                   "ring_width TINYINT UNSIGNED, "
                   "sac_width TINYINT UNSIGNED, "
                   "sac_length TINYINT UNSIGNED"))*/
    q.prepare("INSERT INTO Diagnostics (id, hernia_id, method_id, ring_width, sac_width, sac_length) "
              "VALUES (?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);
    q.addBindValue(methodId);
    q.addBindValue(ringWidth);
    q.addBindValue(sacWidth);
    q.addBindValue(sacLength);
    return q.exec();

}

bool DBWorker::insertOperation(int herniaId, const QString& side, const QString &ringWidth, const QString &sacWidth,
                               const QString &sacLength, const QString &method, const QString &technique,
                               bool intraoperativeComplications, bool hemorrage, bool nerveDamage,
                               bool spermaticCordInjury, bool bowelInjury, bool earlyComplications,
                               bool woundInfection, bool seroma, const QString &seromaSize, bool hematoma,
                               bool spermaticCordSwelling, bool orchiepididymitis, bool lateComplications,
                               bool fistulas, bool meshRejection, bool chronicNeuralgia, bool testicularAtrophy,
                               bool recurrence, bool nerveInjury, int chronicPainInRest, int chronicPainInMotion)
{
    int id = this->getIDForInsert("Operations");

    int methodId = this->getOperationTechniqueId(method);
    int techniqueId = (method == "Натяжной способ") ? this->getTissueRepairTechniqueId(technique) :
                                                      this->getMeshImplantRepairTechniqueId(technique);
    int seromaSizeId = this->getSeromaSizeId(seromaSize);
    /*if(createTable("Operations",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "side_id TINYINY UNSIGNED, "
                   "ring_width TINYINT UNSIGNED, "
                   "sac_width TINYINT UNSIGNED, "
                   "sac_length TINYINT UNSIGNED, "
                   "method_id TINYINT UNSIGNED, "
                   "technique_id TINYINT UNSIGNED, "
                   "intraoperative_complications BOOLEAN, "
                   "hemorrhage BOOLEAN, "
                   "nerve_damage BOOLEAN, "
                   "spermatic_cord_injury BOOLEAN, "
                   "bowel_injury BOOLEAN, "
                   "early_complications BOOLEAN, "
                   "wound_infection BOOLEAN, "
                   "seroma BOOLEAN, "
                   "seroma_size_id TINYINT UNSIGNED, "
                   "hematoma BOOLEAN, "
                   "spermatic_cord_swelling BOOLEAN, "
                   "orchiepididymitis BOOLEAN, "
                   "late_complications BOOLEAN, "
                   "fistulas BOOLEAN, "
                   "mesh_rejection BOOLEAN, "
                   "chronic_inguinal_neuralgia BOOLEAN, "
                   "testicular_atrophy BOOLEAN, "
                   "recurrence BOOLEAN, "
                   "nerve_injury BOOLEAN, "
                   "chronic_pain_in_rest_degree TINYINT UNSIGNED, "
                   "chronic_pain_in_motion_degree TINYINT UNSIGNED"))*/
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO Operations (id, hernia_id, side_id, ring_width, sac_width, sac_length, method_id, technique_id, "
              "intraoperative_complications, hemorrhage, nerve_damage, spermatic_cord_injury, bowel_injury, "
              "early_complications, wound_infection, seroma, seroma_size_id, hematoma, spermatic_cord_swelling, "
              "orchiepididymitis, late_complications, fistulas, mesh_rejection, chronic_inguinal_neuralgia, "
              "testicular_atrophy, recurrence, nerve_injury, chronic_pain_in_rest_degree, chronic_pain_in_motion_degree) "
              "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);

    q.addBindValue(side.isEmpty() ? QVariant(QVariant::Int) : this->getSideId(side));

    q.addBindValue(ringWidth);
    q.addBindValue(sacWidth);
    q.addBindValue(sacLength);
    q.addBindValue(methodId);
    q.addBindValue(techniqueId);

    q.addBindValue(intraoperativeComplications);
    q.addBindValue(intraoperativeComplications ? hemorrage : false);
    q.addBindValue(intraoperativeComplications ? nerveDamage : false);
    q.addBindValue(intraoperativeComplications ? spermaticCordInjury : false);
    q.addBindValue(intraoperativeComplications ? bowelInjury : false);

    q.addBindValue(earlyComplications);
    q.addBindValue(earlyComplications ? woundInfection : false);
    q.addBindValue(earlyComplications ? seroma : false);
    q.addBindValue((earlyComplications && seroma) ? seromaSizeId : QVariant(QVariant::Int));
    q.addBindValue(earlyComplications ? hematoma : false);
    q.addBindValue(earlyComplications ? spermaticCordSwelling : false);
    q.addBindValue(earlyComplications ? orchiepididymitis : false);

    q.addBindValue(lateComplications);
    q.addBindValue(lateComplications ? fistulas : false);
    q.addBindValue(lateComplications ? meshRejection : false);
    q.addBindValue(lateComplications ? chronicNeuralgia : false);
    q.addBindValue(lateComplications ? testicularAtrophy : false);
    q.addBindValue(lateComplications ? recurrence : false);

    q.addBindValue(nerveInjury);
    q.addBindValue((chronicPainInRest < 0) ? QVariant(QVariant::Int) : chronicPainInRest);
    q.addBindValue((chronicPainInMotion < 0) ? QVariant(QVariant::Int) : chronicPainInMotion);
    return q.exec();
}

bool DBWorker::insertNonTensionOperation(int herniaId, const QString &mesh,
                                         const QString &meshWidth, const QString &meshLength,
                                         const QString &fixation, const QString &tuckers,
                                         const QString &peritoneumClosure, bool drainage)
{
    /*if(createTable("NonTensionOperations",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "mesh_id SMALLINT UNSIGNED, "
                   "mesh_width TINYINT UNSIGNED, "
                   "mesh_length TINYINT UNSIGNED, "
                   "fixation_id TINYINT UNSIGNED, "
                   "tuckers_id SMALLINT UNSIGNED, "
                   "peritoneum_closure_id TINYINT UNSIGNED, "
                   "drainage BOOLEAN"))*/
    int meshId = this->getMeshId(mesh);
    int fixationId, tuckersId;

    if(meshId == -1) // сетки нет в базе (введена вручную)
    {
        meshId = this->insertNewMesh(mesh);
    }

    if(!fixation.isEmpty())
    {
        fixationId = this->getFixationTypeId(fixation);
        if(fixationId == -1)
        {
            fixationId = this->insertNewFixationType(fixation);
        }
    }

    if(!tuckers.isEmpty())
    {
        tuckersId = this->getTuckersId(tuckers);
        if(tuckersId == -1)
        {
            tuckersId = this->insertNewTuckers(tuckers);
        }
    }

    int id = this->getIDForInsert("NonTensionOperations");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO NonTensionOperations "
              "(id, hernia_id, mesh_id, mesh_width, mesh_length, fixation_id, tuckers_id, peritoneum_closure_id, drainage) "
              "VALUES (?,?,?,?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);
    q.addBindValue(meshId);
    q.addBindValue(meshWidth);
    q.addBindValue(meshLength);
    if(!fixation.isEmpty())
        q.addBindValue(fixationId);
    else
        q.addBindValue(QVariant(QVariant::Int));

    if(!tuckers.isEmpty())
        q.addBindValue(tuckersId);
    else
        q.addBindValue(QVariant(QVariant::Int));

    if(!peritoneumClosure.isEmpty())
        q.addBindValue(this->getPeritoneumClosureId(peritoneumClosure));
    else
        q.addBindValue(QVariant(QVariant::Int));

    q.addBindValue(drainage);

    return q.exec();
}

bool DBWorker::insertEarlyPostOperativePain(int herniaId, int daysAfterOperation, int painInRest, int painInMotion,
                                            bool analgesics, const QString& analgesicsDays,
                                            bool orally, const QString& orallyDays,
                                            bool injections, const QString& injectionsDays)
{

    /*createTable("EarlyPostoperativePain",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "days_after_operation TINYINT UNSIGNED, "
                   "pain_in_rest_degree TINYINT UNSIGNED, "
                   "pain_in_motion_degree TINYINT UNSIGNED, "
                   "analgesics BOOLEAN, "
                   "days_of_medication TINYINT UNSIGNED, "
                   "orally BOOLEAN, "
                   "days_of_medication_orally TINYINT UNSIGNED, "
                   "injections BOOLEAN, "
                   "days_of_medication_injections TINYINT UNSIGNED")*/


    int id = this->getIDForInsert("EarlyPostoperativePain");
    QSqlQuery q(this->m_db);
    q.prepare("INSERT INTO EarlyPostoperativePain (id, hernia_id, days_after_operation, "
              "pain_in_rest_degree, pain_in_motion_degree, analgesics, days_of_medication, "
              "orally, days_of_medication_orally, "
              "injections, days_of_medication_injections) VALUES (?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(id);
    q.addBindValue(herniaId);
    q.addBindValue(daysAfterOperation);
    if(painInRest < 0)
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(painInRest);
    if(painInMotion < 0)
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(painInMotion);
    q.addBindValue(analgesics);

    if(analgesicsDays.isEmpty())
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(analgesicsDays);

    q.addBindValue(orally);
    if(orallyDays.isEmpty())
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(orallyDays);

    q.addBindValue(injections);
    if(injectionsDays.isEmpty())
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(injectionsDays);
    return q.exec();
}

bool DBWorker::insertHerniaImages(int herniaId, const QStringList &sources, const QStringList& descriptions)
{


    bool ok = true;
    for(int i = 0; i < sources.size(); ++i)
    {

        QString source = sources[i];
        QByteArray byteArray;

        if(!MyFunctions::imageIsFromProvider(source))
        {
            source.remove("file:///");
            QString ext;
            for(int ch = source.length() - 1;;--ch) // выделяем из строки source подстроку с форматом
            {
                if(source[ch] == '.') break;
                ext.push_front(source[ch]);
            }

            QImage image;
            if(!image.load(source))
            {
                qDebug() << "Ошибка при открытии изображения: " << source;
                ok = false;
                continue;
            }

            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            bool scs = image.save(&buffer, ext.toLocal8Bit().constData());
            qDebug() << "image [" << source << "], ext = " << ext << " : " << scs;
        }

        else
        {
            byteArray = this->m_imageProvider->getByteArray(source);
        }



        /*if(createTable("HerniaImages",
                   "id INTEGER UNIQUE PRIMARY KEY, "
                   "hernia_id INTEGER UNSIGNED, "
                   "image MEDIUMBLOB, "
                   "description VARCHAR(300)"
                   ))*/

        int id = this->getIDForInsert("HerniaImages");

        QSqlQuery q(this->m_db);
        q.prepare("INSERT INTO HerniaImages (id, hernia_id, image, description) VALUES (?,?,?,?)");
        q.addBindValue(id);
        q.addBindValue(herniaId);
        q.addBindValue(byteArray);
        q.addBindValue(descriptions[i]);
        if(!q.exec())
        {
            qDebug() << "Ошибка при добавлении записи в таблицу HerniaImages";
            ok = false;
        }
    }
    return ok;
}

void DBWorker::deleteHerniaRecords(int herniaId)
{
    this->deleteRecords("Hernias", "id", herniaId);
    this->deleteRecords("VentralHernias", "hernia_id", herniaId);
    this->deleteRecords("GroinHernias", "hernia_id", herniaId);
    this->deleteRecords("Diagnostics", "hernia_id", herniaId);
    this->deleteRecords("Operations", "hernia_id", herniaId);
    this->deleteRecords("NonTensionOperations", "hernia_id", herniaId);
    this->deleteRecords("EarlyPostoperativePain", "hernia_id", herniaId);
    this->deleteRecords("HerniaImages", "hernia_id", herniaId);
}

void DBWorker::changeHerniaId(int oldId, int newId)
{
    QStringList tablesList = {"Hernias", "VentralHernias", "GroinHernias", "Diagnostics",
                              "Operations", "NonTensionOperations", "EarlyPostoperativePain", "HerniaImages"};
    QStringList herniaIdFieldList;
    for(int i = 0; i < 8; ++i)
        herniaIdFieldList.push_back((i == 0) ? "id" : "hernia_id");

    QSqlQuery q(this->m_db);

    for(int i = 0; i < tablesList.size(); ++i)
    {
        q.prepare("UPDATE " + tablesList[i] + " SET " + herniaIdFieldList[i] + " = ? WHERE " + herniaIdFieldList[i] + " = ?");
        q.addBindValue(newId);
        q.addBindValue(oldId);
        if(q.exec())
            qDebug() << "Таблица " << tablesList[i] << ": id грыжи изменен с " << oldId << " на " << newId;
        else
            qDebug() << "Таблица " << tablesList[i] << ": не удалось изменить id грыжи с " << oldId << " на " << newId;
    }

}



QSqlQuery DBWorker::patientCardQuery(int cardID)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM PatientCards WHERE id = ?");
    q.addBindValue(cardID);
    if(!q.exec())
        qDebug() << "Не удалось получить карту пациента с id = " << cardID;
    q.next();
    return q;
}



QSqlQuery DBWorker::riskFactorsQuery(int cardID)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM RiskFactors WHERE patient_card_id = ?");
    q.addBindValue(cardID);
    if(!q.exec())
        qDebug() << "Не удалось получить факторы риска пациента с id карты = " << cardID;
    q.next();
    return q;
}

QSqlQuery DBWorker::herniaQuery(int cardID, int herniaNumber)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM Hernias WHERE patient_card_id = ? AND hernia_number = ?");
    q.addBindValue(cardID);
    q.addBindValue(herniaNumber);
    if(!q.exec())
        qDebug() << "Не удалось получить информацию о грыже № " << herniaNumber
                 << " у пациента с id карты = " << cardID;
    q.next();
    return q;
}

bool DBWorker::deleteRecords(const QString &tableName, const QString &conditionField, const QVariant &value)
{
    QSqlQuery q(this->m_db);
    q.prepare("DELETE FROM " + tableName + " WHERE " + conditionField + " = ?");
    q.addBindValue(value);
    if(q.exec())
    {
        qDebug() << "Записи из таблицы " << tableName << ", где " << conditionField << " = " << value << " удалены";
        return true;
    }
    qDebug() << "Не удалось удалить записи из таблицы " << tableName << ", где " << conditionField << " = " << value;
    return false;
}

bool DBWorker::updatePatientCard(int cardId,
                                 const QString& fio,
                                 const QDate& birthDate,
                                 const QString& sex,
                                 const QString& phone,
                                 const QString& region,
                                 const QString& district,
                                 const QString& locality,
                                 const QString& street,
                                 const QString& house,
                                 const QString& flat,
                                 const QString& passport,
                                 const QString& snils,
                                 const QString& polisType,
                                 const QString& polisNumber,
                                 const QString& bloodType,
                                 const QString& rhesusFactor,
                                 const QString& weight,
                                 const QString& height,
                                 const QString& complaints)
{
    int regionID = this->getIDByFieldData("Regions", "name", region);
    QString sex_insert = (sex == "Мужской") ? "М" : "Ж";

    QString rhesusFactor_insert;
    if(rhesusFactor == "Rh+")
        rhesusFactor_insert = "+";
    else if(rhesusFactor == "Rh-")
        rhesusFactor_insert = "-";

    QSqlQuery q(this->m_db);

    q.prepare("UPDATE PatientCards SET "
              "fio = ?, birth_date = ?, sex = ?, "
              "phone = ?, region_id = ?, district = ?, locality = ?, "
              "street = ?, house = ?, flat = ?, passport = ?, "
              "snils = ?, polis_type = ?, "
              "polis_number = ?, blood_type = ?, rhesus_factor = ?, "
              "weight = ?, height = ?, complaints = ? "
              "WHERE id = ?");

    q.addBindValue(fio);
    q.addBindValue(birthDate);
    q.addBindValue(sex_insert);
    q.addBindValue(phone);
    q.addBindValue(regionID);
    if(district.isEmpty())
        q.addBindValue(QVariant(QVariant::String));
    else
        q.addBindValue(district);
    q.addBindValue(locality);
    q.addBindValue(street);
    q.addBindValue(house);
    if(flat.isEmpty())
        q.addBindValue(QVariant(QVariant::Int));
    else
        q.addBindValue(flat.toInt());
    q.addBindValue(passport);
    q.addBindValue(snils);
    q.addBindValue(polisType);
    q.addBindValue(polisNumber);
    q.addBindValue(bloodType);
    q.addBindValue(rhesusFactor_insert);
    q.addBindValue(weight);
    q.addBindValue(height);
    q.addBindValue(complaints);
    q.addBindValue(cardId);
    return q.exec();
}



bool DBWorker::updateRiskFactors(int cardId,
                                 int occupationId,
                                 int sportActivitiesId,
                                 int smokingHistoryId,
                                 const QString &cigsPerDay,
                                 const QString &yearsOfSmoking,
                                 bool diabetesI,
                                 bool diabetesII,
                                 bool hobl,
                                 bool hypertension,
                                 bool heartDisease,
                                 bool kidneyDisease,
                                 bool gastritis,
                                 bool ulcer,
                                 bool aorticAneurysm,
                                 bool immunosuppression,
                                 bool coagulopathy,
                                 bool plateletAggregationInhibitors,
                                 const QString &otherFactors)
{
    QSqlQuery q(this->m_db);
    q.prepare("UPDATE RiskFactors SET "
              "occupation_id = ?,"
              "sporting_activities_id = ?, "
              "smoking_history_id = ?, "
              "cigs_per_day = ?, "
              "years_of_smoking = ?, "
              "diabetes_I = ?, "
              "diabetes_II = ?, "
              "hobl = ?, "
              "hypertension = ?, "
              "heart_disease = ?, "
              "kidney_disease = ?, "
              "gastritis = ?, "
              "ulcer = ?, "
              "aortic_aneurysm = ?, "
              "immunosuppression = ?, "
              "coagulopathy = ?, "
              "platelet_aggregation_inhibitors = ?, "
              "other_factors = ? "
              "WHERE card_id = ?");
    q.addBindValue(occupationId);
    q.addBindValue(sportActivitiesId);
    q.addBindValue(smokingHistoryId);
    if(!cigsPerDay.isEmpty())
        q.addBindValue(cigsPerDay);
    else
        q.addBindValue(QVariant(QVariant::Int));
    if(!yearsOfSmoking.isEmpty())
        q.addBindValue(yearsOfSmoking);
    else
        q.addBindValue(QVariant(QVariant::Int));
    q.addBindValue(diabetesI);
    q.addBindValue(diabetesII);
    q.addBindValue(hobl);
    q.addBindValue(hypertension);
    q.addBindValue(heartDisease);
    q.addBindValue(kidneyDisease);
    q.addBindValue(gastritis);
    q.addBindValue(ulcer);
    q.addBindValue(aorticAneurysm);
    q.addBindValue(immunosuppression);
    q.addBindValue(coagulopathy);
    q.addBindValue(plateletAggregationInhibitors);
    q.addBindValue(otherFactors);
    q.addBindValue(cardId);

    return q.exec();
}



QList<QObject *> DBWorker::regionsDistribution(const QList<int> &cardIDs)
{
    QString cardIdCondition;
    for(auto id: cardIDs)
    {
        if(!cardIdCondition.isEmpty()) cardIdCondition += " OR ";
        cardIdCondition += "id = " + QString::number(id);
    }

    QSqlQuery q(this->m_db);
    q.prepare("SELECT DISTINCT region_id FROM PatientCards WHERE " + cardIdCondition);
    if(!q.exec())
        qDebug() << "Ошибка при поиске уникальных регионов";

    QList<int> uniqueRegionIDs;
    while(q.next())
        uniqueRegionIDs.push_back(q.value(0).toInt());

    //std::sort(uniqueRegionIDs.begin(), uniqueRegionIDs.end());

    QList<int> countList;

    for(auto regionID: uniqueRegionIDs)
    {
        QSqlQuery query(this->m_db);
        query.prepare("SELECT COUNT(*) FROM PatientCards WHERE region_id = ? AND (" + cardIdCondition + ')');
        query.addBindValue(regionID);
        if(!query.exec())
            qDebug() << "Ошибка при получении количества карт с id региона " << regionID;
        query.next();

        int count = query.value(0).toInt();
        countList.push_back(count);
        //QString regionName = this->getRegionByID(regionID);
        //hash.insert(regionName, count);
    }

    QList<float> percentList;
    MyFunctions::calculatePercentList(countList, percentList);

    QList<QObject*> distList;
    for(int i = 0; i < uniqueRegionIDs.size(); ++i)
    {
        QString region = this->getRegionByID(uniqueRegionIDs[i]);
        distList.push_back(new DistributionElement(region, countList[i], percentList[i], this));
    }

    MyFunctions::sortDistributionList(distList);
    return distList;
}

QList<QObject *> DBWorker::sexDistribution(const QList<int> &cardIDs)
{

    QString cardIdCondition; // строка с условием отбора из базы только карт из списка
    for(auto id: cardIDs)
    {
        if(!cardIdCondition.isEmpty()) cardIdCondition += " OR ";
        cardIdCondition += "id = " + QString::number(id);
    }

    QSqlQuery q(this->m_db);
    q.prepare("SELECT DISTINCT sex FROM PatientCards WHERE " + cardIdCondition);
    if(!q.exec())
        qDebug() << "Ошибка при поиске уникальных полов пациентов";

    QStringList uniqueSex;
    while(q.next())
        uniqueSex.push_back(q.value(0).toString());



    QList<int> countList;

    for(auto sex: uniqueSex)
    {
        QSqlQuery query(this->m_db);
        query.prepare("SELECT COUNT(*) FROM PatientCards WHERE sex = ? AND (" + cardIdCondition + ')');
        query.addBindValue(sex);
        if(!query.exec())
            qDebug() << "Ошибка при получении количества карт с полом " << sex;
        query.next();

        int count = query.value(0).toInt();
        countList.push_back(count);
    }

    QList<float> percentList;
    MyFunctions::calculatePercentList(countList, percentList);

    QList<QObject*> distributionList;
    for(int i = 0; i < uniqueSex.size(); ++i)
    {
        QString sex = (uniqueSex[i] == "М") ? "Мужской" : "Женский";
        distributionList.push_back(new DistributionElement(sex, countList[i], percentList[i], this));
    }

    MyFunctions::sortDistributionList(distributionList);
    return distributionList;
}

QList<QObject *> DBWorker::operationMethodsDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
        for(auto cardId: cardIDs)
        {
            QSqlQuery q(this->m_db);
            q.prepare("SELECT DISTINCT method_id FROM Operations WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);
            if(!q.exec())
            {
                qDebug() << "operationMethodsDistribution: некорректный запрос";
                continue;
            }

            if(!q.next()) // операций не было
            {
                QString noOperationsString = "Операции не проводились";
                if(!countMap.contains(noOperationsString))
                    countMap[noOperationsString] = 1;
                else
                    ++countMap[noOperationsString];
            }

            else do
            {
                int methodId = q.value(0).toInt();
                QString methodString = getFieldDataByID("OperationTechniques", "technique", methodId);
                if(!countMap.contains(methodString))
                    countMap[methodString] = 1;
                else
                    ++countMap[methodString];
            }while(q.next());
        }

        QList<QObject*> distributionList;

        for(auto key: countMap.keys())
        {
            int count = countMap[key];
            float percent = static_cast<float>(count) * 100 / cardIDs.count();
            distributionList << new DistributionElement(key, count, percent);
        }

        MyFunctions::sortDistributionList(distributionList);
        return distributionList;
}

QList<QObject *> DBWorker::tensionOperationsDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
    int tensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");
    int nonTensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Ненатяжной способ");

        for(auto cardId: cardIDs)
        {
            bool nonTensionOperations = false;
            QSqlQuery q(this->m_db);

            // *********  Cначала проверяем, были ли у пациента ненатяжные операции *************
            q.prepare("SELECT id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(nonTensionTechniqueId);
            if(!q.exec())
            {
                qDebug() << "tensionOperationsDistribution: некорректный запрос";
                continue;
            }

            if(q.next())
            {
                nonTensionOperations = true;
                QString nonTensionString = "Операции ненатяжным способом";
                if(!countMap.contains(nonTensionString))
                    countMap[nonTensionString] = 1;
                else
                    ++countMap[nonTensionString];
            }

            // ********** Ищем натяжные операции ***********************************************

            // получаем уникальные техники натяжной операции для каждого пациента
            q.prepare("SELECT DISTINCT technique_id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(tensionTechniqueId);

            if(!q.exec())
            {
                qDebug() << "tensionOperationsDistribution: некорректный запрос";
                continue;
            }

            if(!q.next()) // были только ненатяжные операции или операций вообще не было
            {
                if(!nonTensionOperations) // значит операции вообще не проводились
                {
                    QString noOperationsString = "Операции не проводились";
                    if(!countMap.contains(noOperationsString))
                        countMap[noOperationsString] = 1;
                    else
                        ++countMap[noOperationsString];
                }
            }

            else do // натяжные операции проводились
            {
                int techniqueId = q.value(0).toInt();
                QString technique = getFieldDataByID("TissueRepairTechniques", "technique", techniqueId);
                if(!countMap.contains(technique))
                    countMap[technique] = 1;
                else
                    ++countMap[technique];

            } while(q.next());
        }

        QList<QObject*> distributionList;

        for(auto key: countMap.keys())
        {
            int count = countMap[key];
            float percent = static_cast<float>(count) * 100 / cardIDs.count();
            distributionList << new DistributionElement(key, count, percent);
        }

        MyFunctions::sortDistributionList(distributionList);
        return distributionList;
}

QList<QObject *> DBWorker::nonTensionOperationsDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
    int tensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");
    int nonTensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Ненатяжной способ");

        for(auto cardId: cardIDs)
        {
            bool tensionOperations = false;
            QSqlQuery q(this->m_db);

            // *********  Cначала проверяем, были ли у пациента натяжные операции *************
            q.prepare("SELECT id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(tensionTechniqueId);
            if(!q.exec())
            {
                qDebug() << "nonTensionOperationsDistribution: некорректный запрос";
                continue;
            }

            if(q.next())
            {
                tensionOperations = true;
                QString tensionString = "Операции натяжным способом";
                if(!countMap.contains(tensionString))
                    countMap[tensionString] = 1;
                else
                    ++countMap[tensionString];
            }

            // ********** Ищем ненатяжные операции ***********************************************

            // получаем уникальные техники ненатяжной операции для каждого пациента
            q.prepare("SELECT DISTINCT technique_id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(nonTensionTechniqueId);

            if(!q.exec())
            {
                qDebug() << "nonTensionOperationsDistribution: некорректный запрос";
                continue;
            }

            if(!q.next()) // были только натяжные операции или операций вообще не было
            {
                if(!tensionOperations) // значит операции вообще не проводились
                {
                    QString noOperationsString = "Операции не проводились";
                    if(!countMap.contains(noOperationsString))
                        countMap[noOperationsString] = 1;
                    else
                        ++countMap[noOperationsString];
                }
            }

            else do // ненатяжные операции проводились
            {
                int techniqueId = q.value(0).toInt();
                QString technique = getFieldDataByID("MeshImplantRepairTechniques", "technique", techniqueId);
                if(!countMap.contains(technique))
                    countMap[technique] = 1;
                else
                    ++countMap[technique];

            } while(q.next());
        }

        QList<QObject*> distributionList;

        for(auto key: countMap.keys())
        {
            int count = countMap[key];
            float percent = static_cast<float>(count) * 100 / cardIDs.count();
            distributionList << new DistributionElement(key, count, percent);
        }

        MyFunctions::sortDistributionList(distributionList);
        return distributionList;
}

QList<QObject *> DBWorker::meshesDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
    int tensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");

        for(auto cardId: cardIDs)
        {
            bool tensionOperations = false;
            QSqlQuery q(this->m_db);

            // *********  Cначала проверяем, были ли у пациента натяжные операции *************
            q.prepare("SELECT id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(tensionTechniqueId);
            if(!q.exec())
            {
                qDebug() << "meshesDistribution: некорректный запрос";
                continue;
            }

            if(q.next())
            {
                tensionOperations = true;
                QString tensionString = "Операции натяжным способом";
                if(!countMap.contains(tensionString))
                    countMap[tensionString] = 1;
                else
                    ++countMap[tensionString];
            }

            // ********** Ищем сетки ***********************************************

            // получаем уникальные сетки для каждого пациента
            q.prepare("SELECT DISTINCT mesh_id FROM NonTensionOperations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);

            if(!q.exec())
            {
                qDebug() << "meshesDistribution: некорректный запрос";
                continue;
            }

            if(!q.next()) // были только натяжные операции или операций вообще не было
            {
                if(!tensionOperations) // значит операции вообще не проводились
                {
                    QString noOperationsString = "Операции не проводились";
                    if(!countMap.contains(noOperationsString))
                        countMap[noOperationsString] = 1;
                    else
                        ++countMap[noOperationsString];
                }
            }

            else do // ненатяжные операции проводились
            {
                int meshId = q.value(0).toInt();
                QString mesh = this->getMeshById(meshId);
                if(!countMap.contains(mesh))
                    countMap[mesh] = 1;
                else
                    ++countMap[mesh];

            } while(q.next());
        }

        QList<QObject*> distributionList;

        for(auto key: countMap.keys())
        {
            int count = countMap[key];
            float percent = static_cast<float>(count) * 100 / cardIDs.count();
            distributionList << new DistributionElement(key, count, percent);
        }

        MyFunctions::sortDistributionList(distributionList);
        return distributionList;
}

QList<QObject *> DBWorker::fixationDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
    int tensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");

        for(auto cardId: cardIDs)
        {
            bool tensionOperations = false;
            QSqlQuery q(this->m_db);

            // *********  Cначала проверяем, были ли у пациента натяжные операции *************
            q.prepare("SELECT id FROM Operations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                      "AND method_id = ?");
            q.addBindValue(cardId);
            q.addBindValue(tensionTechniqueId);
            if(!q.exec())
            {
                qDebug() << "fixationDistribution: некорректный запрос";
                continue;
            }

            if(q.next())
            {
                tensionOperations = true;
                QString tensionString = "Операции натяжным способом";
                if(!countMap.contains(tensionString))
                    countMap[tensionString] = 1;
                else
                    ++countMap[tensionString];
            }

            // ********** Ищем сетки ***********************************************

            // получаем уникальные фиксации для каждого пациента
            q.prepare("SELECT DISTINCT fixation_id FROM NonTensionOperations "
                      "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);

            if(!q.exec())
            {
                qDebug() << "fixationDistribution: некорректный запрос";
                continue;
            }

            if(!q.next()) // были только натяжные операции или операций вообще не было
            {
                if(!tensionOperations) // значит операции вообще не проводились
                {
                    QString noOperationsString = "Операции не проводились";
                    if(!countMap.contains(noOperationsString))
                        countMap[noOperationsString] = 1;
                    else
                        ++countMap[noOperationsString];
                }
            }

            else do // ненатяжные операции проводились
            {
                if(q.value(0).isNull())
                {
                    QString noFixation = "Сетка не фиксировалась";
                    if(!countMap.contains(noFixation))
                        countMap[noFixation] = 1;
                    else
                        ++countMap[noFixation];
                }
                else
                {
                    int fixationId = q.value(0).toInt();
                    QString fixation = this->getFieldDataByID("FixationTypes", "type", fixationId);
                    if(!countMap.contains(fixation))
                        countMap[fixation] = 1;
                    else
                        ++countMap[fixation];
                }


            } while(q.next());
        }

        QList<QObject*> distributionList;

        for(auto key: countMap.keys())
        {
            int count = countMap[key];
            float percent = static_cast<float>(count) * 100 / cardIDs.count();
            distributionList << new DistributionElement(key, count, percent);
        }

        MyFunctions::sortDistributionList(distributionList);
        return distributionList;
}

QList<QObject *> DBWorker::tuckersDistribution(const QList<int> &cardIDs)
{
    /* остальные случаи:
     * 1) операции не проводились
     * 2) операции натяжным способом
     * 3) фиксации не было
     * 4) другой тип фиксации */

    QMap<QString, int> countMap;
    int tensionTechniqueId = getIDByFieldData("OperationTechniques", "technique", "Натяжной способ");

    for(auto cardId: cardIDs)
    {
        bool tensionOperations = false;
        QSqlQuery q(this->m_db);

        // *********  Cначала проверяем, были ли у пациента натяжные операции *************
        q.prepare("SELECT id FROM Operations "
                  "WHERE hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?) "
                  "AND method_id = ?");
        q.addBindValue(cardId);
        q.addBindValue(tensionTechniqueId);

        if(!q.exec())
        {
            qDebug() << "tuckersDistribution: некорректный запрос";
            continue;
        }

        if(q.next())
        {
            tensionOperations = true;
            QString tensionString = "Операции натяжным способом";
            if(!countMap.contains(tensionString))
                countMap[tensionString] = 1;
            else
                ++countMap[tensionString];
        }

        q.prepare("SELECT DISTINCT fixation_id FROM NonTensionOperations where hernia_id IN "
                  "(SELECT id FROM Hernias WHERE card_id = ?)");
        q.addBindValue(cardId);

        if(!q.exec())
        {
            qDebug() << "tuckersDistribution: некорректный запрос";
            continue;
        }

        if(!q.next()) // были только натяжные операции или операций вообще не было
        {
            if(!tensionOperations) // значит операции вообще не проводились
            {
                QString noOperationsString = "Операции не проводились";
                if(!countMap.contains(noOperationsString))
                    countMap[noOperationsString] = 1;
                else
                    ++countMap[noOperationsString];
            }
        }

        else do
        {
            if(q.value(0).isNull())
            {
                QString noFixation = "Сетка не фиксировалась";
                if(!countMap.contains(noFixation))
                    countMap[noFixation] = 1;
                else
                    ++countMap[noFixation];
            }
            else
            {
                QString fixation = this->getFieldDataByID("FixationTypes", "type", q.value(0).toInt());
                if(fixation != "Такеры")
                {
                    if(!countMap.contains(fixation))
                        countMap[fixation] = 1;
                    else
                        ++countMap[fixation];
                }
                else
                {
                    QSqlQuery tq(this->m_db);
                    tq.prepare("SELECT DISTINCT tuckers_id FROM NonTensionOperations WHERE tuckers_id IS NOT NULL "
                               "AND hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?)");
                    tq.addBindValue(cardId);
                    if(!tq.exec())
                    {
                        qDebug() << "tuckersDistribution: некорректный запрос";
                        continue;
                    }

                    // выборка не может быть пустой, так как тип фиксации в этом месте - точно такеры

                    while(tq.next())
                    {
                        int tuckerId = tq.value(0).toInt();
                        QString tucker = this->getFieldDataByID("Tuckers", "tucker", tuckerId);
                        if(!countMap.contains(tucker))
                            countMap[tucker] = 1;
                        else
                            ++countMap[tucker];
                    }

                }
            }
        } while(q.next());



    }

    QList<QObject*> distributionList;

    for(auto key: countMap.keys())
    {
        int count = countMap[key];
        float percent = static_cast<float>(count) * 100 / cardIDs.count();
        distributionList << new DistributionElement(key, count, percent);
    }

    MyFunctions::sortDistributionList(distributionList);
    return distributionList;
}

QList<QObject *> DBWorker::complicationsDistribution(const QList<int> &cardIDs)
{
    QMap<QString, int> countMap;
    for(auto cardId: cardIDs)
    {
        QSqlQuery q(this->m_db);

        // сначала проверим, были ли операции вообще

        q.prepare("SELECT id FROM Operations WHERE hernia_id IN "
                  "(SELECT id FROM Hernias WHERE card_id = ?)");
        q.addBindValue(cardId);
        if(!q.exec())
        {
            qDebug() << "DBWorker::complicationsDistribution: Некорректный запрос";
            continue;
        }
        if(!q.next()) // операции не проводились
        {
            QString noOperationsString = "Операции не проводились";
            if(!countMap.contains(noOperationsString))
                countMap[noOperationsString] = 1;
            else
                ++countMap[noOperationsString];
        }

        else
        {
            // cначала посмотрим, есть ли операции без осложнений
            q.prepare("SELECT id FROM Operations WHERE intraoperative_complications = false "
                      "AND early_complications = false AND late_complications = false AND "
                      "hernia_id IN (SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);
            if(!q.exec())
            {
                qDebug() << "DBWorker::complicationsDistribution: Некорректный запрос";
                continue;
            }
            if(q.next())
            {
                QString noComplicationsString = "Операции без осложнений";
                if(!countMap.contains(noComplicationsString))
                    countMap[noComplicationsString] = 1;
                else
                    ++countMap[noComplicationsString];
            }

            // Интраоперационные
            q.prepare("SELECT id FROM Operations WHERE intraoperative_complications = true AND hernia_id IN "
                      "(SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);
            if(!q.exec())
            {
                qDebug() << "DBWorker::complicationsDistribution: Некорректный запрос";
                continue;
            }
            if(q.next())
            {
                QString intraString = "Интраоперационные";
                if(!countMap.contains(intraString))
                    countMap[intraString] = 1;
                else
                    ++countMap[intraString];
            }

            // Ранние
            q.prepare("SELECT id FROM Operations WHERE early_complications = true AND hernia_id IN "
                      "(SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);
            if(!q.exec())
            {
                qDebug() << "DBWorker::complicationsDistribution: Некорректный запрос";
                continue;
            }
            if(q.next())
            {
                QString earlyString = "Ранние послеоперационные";
                if(!countMap.contains(earlyString))
                    countMap[earlyString] = 1;
                else
                    ++countMap[earlyString];
            }

            // Поздние
            q.prepare("SELECT id FROM Operations WHERE late_complications = true AND hernia_id IN "
                      "(SELECT id FROM Hernias WHERE card_id = ?)");
            q.addBindValue(cardId);
            if(!q.exec())
            {
                qDebug() << "DBWorker::complicationsDistribution: Некорректный запрос";
                continue;
            }
            if(q.next())
            {
                QString lateString = "Поздние послеоперационные";
                if(!countMap.contains(lateString))
                    countMap[lateString] = 1;
                else
                    ++countMap[lateString];
            }
        }
    }

    QList<QObject*> distributionList;

    for(auto key: countMap.keys())
    {
        int count = countMap[key];
        float percent = static_cast<float>(count) * 100 / cardIDs.count();
        distributionList << new DistributionElement(key, count, percent);
    }

    MyFunctions::sortDistributionList(distributionList);
    return distributionList;
}

void DBWorker::addMeshToLastAdded(int userId, const QString& mesh)
{
    int meshId = getMeshId(mesh);
    QSqlQuery q(this->m_db);
    // Проверка на существование
    q.prepare("SELECT * FROM LastAddedMeshes WHERE user_id = ? AND mesh_id = ?");
    q.addBindValue(userId);
    q.addBindValue(meshId);
    if(!q.exec())
        qDebug() << "DBWorker::addMeshToLastAdded: Не удалось проверить существование записи в таблице";
    if(q.next())
    {
        q.prepare("DELETE FROM LastAddedMeshes WHERE user_id = ? AND mesh_id = ?");
        q.addBindValue(userId);
        q.addBindValue(meshId);
        if(!q.exec())
            qDebug() << "DBWorker::addMeshToLastAdded: Не удалось удалить существующую запись";
    }
    // Добавление
    q.prepare("INSERT INTO LastAddedMeshes (user_id, mesh_id) VALUES (?,?)");
    q.addBindValue(userId);
    q.addBindValue(meshId);
    if(!q.exec())
        qDebug() << "DBWorker::addMeshToLastAdded: Не удалось добавить сетку в последние добавленные";
    else
        qDebug() << "DBWorker::addMeshToLastAdded: Сетка добавлена в последние добавленные";
}


QString DBWorker::getFieldDataByID(const QString &tableName, const QString &fieldName, int id)
{
    QSqlQuery q(this->m_db);
    QString idString;
    idString.setNum(id);
    q.prepare("SELECT " + fieldName + " FROM " + tableName + " WHERE (id = " + idString + ')');
    if(!q.exec())
    {
        qDebug() << "Ошибка при поиске значения поля по ID";
        return "";
    }
    if(!q.next())
    {
        qDebug() << "getFieldDataByID: запись не найдена (" << tableName << ", " << fieldName << ", id = " << id << ")";
        return "";
    }
    return q.value(0).toString();
}

int DBWorker::getIDByFieldData(const QString &tableName, const QString &fieldName, const QString &fieldData)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id FROM " + tableName + " WHERE (" + fieldName + " = ?)");
    q.addBindValue(fieldData);
    if(!q.exec())
    {
        qDebug() << "Ошибка при поиске ID по значению поля";
        return -1;
    }
    if(!q.next())
    {
        qDebug() << "getIDByFieldData: запись не найдена (" << tableName << ", " << fieldName << ": " << fieldData << ")";
        return -1;
    }
    return q.value(0).toInt();
}

QStringList DBWorker::regions()
{
    QStringList regionsList;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT name FROM Regions");
    if(!q.exec())
        qDebug() << "Ошибка при запросе списка регионов";

    else
        while(q.next())
            regionsList.push_back(q.value(0).toString());

    return regionsList;
}

bool DBWorker::recordExists(const QString &tableName, const QString &fieldName, const QVariant &data)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM " + tableName + " WHERE " + fieldName + " = ?");
    q.addBindValue(data);
    if(!q.exec())
    {
        qDebug() << "Ошибка при проверке существования записи в таблице " << tableName << ", где " <<
                    fieldName << " = " << data;
        return true;
    }
    return q.next();
}



bool DBWorker::userExists(const QString &login, const QString &password)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Users WHERE login = ? AND password = ?");
    q.addBindValue(login);
    q.addBindValue(password);
    if(!q.exec())
    {
        qDebug() << "Не удалось получить доступ к таблице пользователей";
        return false;
    }
    if(!q.next())
        return false;
    return true;
//    if(userId != nullptr)
//        *userId = q.value(0).toInt();
}

int DBWorker::getUserID(const QString &login, const QString &password)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM Users WHERE login = ? AND password = ?");
    q.addBindValue(login);
    q.addBindValue(password);
    q.exec();
    q.next();
    return q.value(0).toInt();
}

bool DBWorker::loginExists(const QString &login)
{
    return this->recordExists("Users", "login", login);
}

bool DBWorker::emailExists(const QString &email)
{
    return this->recordExists("Users", "email", email);
}

bool DBWorker::certificateExists(const QString &certificate)
{
    return this->recordExists("Doctors", "certificate", certificate);
}

bool DBWorker::patientPassportExists(const QString &passportSeries, const QString &passportNumber)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM PatientCards WHERE passport_series = ? AND passport_number = ?");
    q.addBindValue(passportSeries);
    q.addBindValue(passportNumber);
    if(!q.exec())
    {
        qDebug() << "Ошибка при проверке существования пациента с таким паспортом";
        return true;
    }
    return q.next();
}

int DBWorker::getUserStatus(int userID)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT statusId FROM Users WHERE id = ?");
    q.addBindValue(userID);
    if(!q.exec())
    {
        qDebug() << "Ошибка при извлечении статуса пользователя";
        return -1;
    }
    q.next();
    return q.value(0).toInt();
}

//QString DBWorker::getUserStatus(int userID)
//{
//    QSqlQuery q(this->m_db);
//    q.prepare("SELECT status FROM UserStatuses WHERE id IN(SELECT statusId FROM Users WHERE id = ?)");
//    q.addBindValue(userID);
//    if(!q.exec())
//    {
//        qDebug() << "Ошибка при извлечении статуса пользователя";
//        return "";
//    }
//    q.next();
//    return q.value(0).toString();
//}

int DBWorker::maxID(const QString &tableName)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT MAX(id) FROM " + tableName);
    if(!q.exec())
    {
        qDebug() << "Таблица " << tableName << ": ошибка при нахождении максимального id";
        return -1;
    }
    q.next();
    return q.value(0).toInt();
}

int DBWorker::getIDForInsert(const QString &tableName)
{
    if(tableIsEmpty(tableName))
        return 1;
    return maxID(tableName) + 1;
}

QString DBWorker::getUserFIO(int id)
{
    return this->getFieldDataByID("Users", "fio", id);
}

QString DBWorker::getRegionByID(int id)
{
    return this->getFieldDataByID("Regions", "name", id);
}

int DBWorker::getRegionID(const QString &regionName)
{
    return this->getIDByFieldData("Regions", "name", regionName);
}

//QString DBWorker::getDiseaseDescriptionByID(int id)
//{
//    return this->getFieldDataByID("DiseaseDescriptions", "description", id);
//}

//int DBWorker::getIdOfDiseaseDescription(const QString &description)
//{
//    return this->getIDByFieldData("DiseaseDescriptions", "description", description);
//}

QHash<int, QString> DBWorker::getDoctorsRequests()
{
    QHash<int, QString> requests;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id, fio FROM Doctors WHERE user_id IN(SELECT id FROM Users WHERE statusId = ?)");
    q.addBindValue(3);
    q.exec();
    while(q.next())
        requests.insert(q.value(0).toInt(), q.value(1).toString());

    return requests;
}

bool DBWorker::acceptRequest(int doctorId) // в таблице Users меняем статус пользователя на "Врач"
{
    QSqlQuery q(this->m_db);
    q.prepare("UPDATE Users SET statusId = 2 WHERE id IN(SELECT user_id FROM Doctors WHERE id = ?)");
    q.addBindValue(doctorId);
    return q.exec();
}

bool DBWorker::rejectRequest(int doctorId) // удаляем записи для данного пользователя из таблиц Users и Doctors
{
    QSqlQuery q(this->m_db);
    q.prepare("DELETE FROM Users WHERE id IN(SELECT user_id FROM Doctors WHERE id = ?)");
    q.addBindValue(doctorId);
    if(!q.exec())
        return false;
    q.prepare("DELETE FROM Doctors WHERE id = ?");
    q.addBindValue(doctorId);
    return q.exec();
}

int DBWorker::getCardIdByNumber(const QString &cardNumber)
{
    return this->getIDByFieldData("PatientCards", "card_number", cardNumber);
}

bool DBWorker::cardAvailable(int userID, int cardID)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT * FROM AvailablePatientCards WHERE user_id = ? AND patient_card_id = ?");
    q.addBindValue(userID);
    q.addBindValue(cardID);
    q.exec();
    return q.next();
}

bool DBWorker::patientExists(const QString &cardNumber, const QString &passportSeries,
                             const QString &passportNumber, const QString &snils, const QString &polisNumber)
{
    if(this->recordExists("PatientCards", "card_number", cardNumber))
    {
        //QMessageBox::critical(0, "Невозможно добавить карту", "Карта с наким номером уже существует");
        return true;
    }

    if(this->patientPassportExists(passportSeries, passportNumber))
    {
        //QMessageBox::critical(0, "Невозможно добавить карту", "Пациент с такими паспортными данными уже есть в базе");
        return true;
    }

    if(this->recordExists("PatientCards", "snils", snils))
    {
        //QMessageBox::critical(0, "Невозможно добавить карту", "Пациент с таким СНИЛСом уже есть в базе");
        return true;
    }

    if(this->recordExists("PatientCards", "polis_number", polisNumber))
    {
        //QMessageBox::critical(0, "Невозможно добавить карту", "Пациент с таким номером полиса уже есть в базе");
        return true;
    }

    return false;
}

int DBWorker::getNewHerniaNumber(int cardID)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT MAX(hernia_number) FROM Hernias WHERE patient_card_id = ?");
    q.addBindValue(cardID);
    q.exec();
    if(!q.next())
        return 1;
    return q.value(0).toInt() + 1;
}

int DBWorker::getCardIdBySnils(const QString &snils)
{
    QSqlQuery q(this->m_db);
    q.prepare("SELECT id FROM PatientCards WHERE snils = ?");
    q.addBindValue(snils);
    if(!q.exec())
        return -1;
    q.next();
    return q.value(0).toInt();
}


void DBWorker::fillHerniaTypesTable()
{
    QStringList list =
    {
        "Послеоперационная вентральная",
        "Паховая"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO HerniaTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillVentralHerniaTypesTable()
{
    QStringList list =
    {
        "Срединная",
        "Латеральная"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO VentralHerniaTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillVentralMidlineHerniaTypesTable()
{
    QStringList list =
    {
        "М1 - субксифоидальная",
        "М2 - эпигастральная",
        "М3 - пупочная",
        "М4 - инфраумбиликальная",
        "М5 - надлобковая"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO VentralMidlineHerniaTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillVentralLateralHerniaTypesTable()
{
    QStringList list =
    {
        "L1 - подрёберная",
        "L2 - боковая",
        "L3 - подвздошная",
        "L4 - поясничная"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO VentralLateralHerniaTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillVentralHerniaWidthsTable()
{
    QStringList list =
    {
        "W1 (< 4 см)",
        "W2 (⩾ 4-10 см)",
        "W3 (⩾ 10 см)"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO VentralHerniaWidths (id, width) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillGroinHerniaTypesTable()
{
    QStringList list =
    {
        "L - латеральная/косая",
        "M - медиальная/прямая",
        "F - бедренная"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO GroinHerniaTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillGroinHerniaExaminationsTable()
{
    QStringList list =
    {
        "0 - грыжа не определяется",
        "1 - ⩽ 1.5 см (один палец)",
        "2 - 1.5-3 см (два пальца)",
        "3 - > 3 см (более двух пальцев)",
        "X - исследование не проводилось"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO GroinHerniaExaminations (id, examination) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillSidesTable()
{
    QStringList list =
    {
        "Правосторонняя",
        "Левосторонняя",
        "Двусторонняя"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO Sides (id, side) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

//void DBWorker::fillRecurrentOperationSpecificationsTable()
//{
//    QStringList list =
//    {
//        "После ушивания дефекта",
//        "После установки сетчатого имплантата открытым доступом",
//        "После установки сетчатого имплантата эндоскопическим доступом"
//    };
//    QSqlQuery q(this->m_db);

//    int id = 1;
//    for(auto str: list)
//    {
//        q.prepare("INSERT INTO RecurrentOperationSpecifications (id, specification) VALUES(?,?)");
//        q.addBindValue(id);
//        q.addBindValue(str);
//        q.exec();
//        ++id;
//    }
//}

//void DBWorker::fillHernialHoleSizesTable()
//{
//    QStringList list =
//    {
//        "I - < 1.5 см",
//        "II - 1.5-3 см",
//        "III - > 3 см"
//    };
//    QSqlQuery q(this->m_db);

//    int id = 1;
//    for(auto str: list)
//    {
//        q.prepare("INSERT INTO HernialHoleSizes (id, size) VALUES(?,?)");
//        q.addBindValue(id);
//        q.addBindValue(str);
//        q.exec();
//        ++id;
//    }
//}

//void DBWorker::fillHernialSacSizesTable()
//{
//    QStringList list =
//    {
//        "I - < 3 см",
//        "II - 3-5 см",
//        "III - > 5 см"
//    };
//    QSqlQuery q(this->m_db);

//    int id = 1;
//    for(auto str: list)
//    {
//        q.prepare("INSERT INTO HernialSacSizes (id, size) VALUES(?,?)");
//        q.addBindValue(id);
//        q.addBindValue(str);
//        q.exec();
//        ++id;
//    }
//}

void DBWorker::fillTissueRepairTechniquesTable()
{
    QStringList list =
    {
        "Bassini",
        "Postempsky",
        "Shouldice"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO TissueRepairTechniques (id, technique) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillMeshImplantRepairTechniquesTable()
{
//    QStringList list =
//    {
//        "Открытый передний доступ (Lichtenstein)",
//        "Открытый передний доступ (Plug and Patch)",
//        "Открытый передний доступ (PHS)",
//        "Открытый закрытый доступ (Rives)",
//        "Открытый закрытый доступ (TiPP)",
//        "Открытый закрытый доступ (Stoppa)",
//        "Эндоскопический предбрюшинный доступ (TAPP)",
//        "Эндоскопический предбрюшинный доступ (TEP)"
//    };
    QStringList list =
    {
        "Lichtenstein",
        "Stoppa",
        "TIPP",
        "TAPP",
        "TEP"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO MeshImplantRepairTechniques (id, technique) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillMeshesTable()
{
    QStringList list =
    {
        "Angimesh 0 Plug P7",
        "Angimesh 1 Plug P5",
        "Angimesh 9 Plug P5",
        "Angimesh 9 Plug P7",
        "Angimesh Pre 8 (D) – Thick Mesh ",
        "Angimesh Pre 9 (D) – Standard Mesh ",
        "Angimesh Pre 5 (D) – Half-thick Mesh ",
        "Angimesh R2",
        "Combi Mesh",
        "Combi Mesh Pro",
        "Repol Angimesh 0 – Ultra Light Mesh",
        "Repol Angimesh 1 – Light Mesh",
        "Repol Angimesh 8 – Thick Mesh",
        "Repol Angimesh 9 – Standard Mesh",
        "Repol Angimesh A9-XCO – Standard Mesh",
        "Repol Angimesh A5-XCO – Half-thick Mesh",
        "Repol Plug Cap",
        "Repol Plug Flower",
        "Wings Mesh",
        "Surgimesh 1 & 2",
        "Surgimesh Easyplug Standard",
        "Surgimesh PET 2D",
        "Surgimesh PET 3D",
        "Surgimesh XB",
        "Surgimesh XB TintraP",
        "Surgimesh XD",
        "Surgimesh XLIGHT",
        "Surgimesh WN",
        "Surgimesh WN Easyplug",
        "Surgimesh WN Easyplug No Touch	",
        "C-Qur Edge Mesh",
        "C-Qur Lite Mesh",
        "C-Qur Mesh",
        "C-Qur V-Patch",
        "ProLite Mesh",
        "ProLite Ultra Mesh",
        "ProLite Ultra Mesh Self-Forming Plug",
        "ProLoop Mesh	",
        "3DMax Mesh",
        "3DMax Light Mesh",
        "CK Parastomal Hernia Patch",
        "Composix Kugel Patch",
        "CollaMend Implantat",
        "Composix Mesh",
        "Composix E/X Mesh",
        "Composix L/P Mesh",
        "CruraSoft Patch",
        "Dulex Mesh",
        "Flat Mesh / Preshapes Hernia Patch",
        "Kugel Hernia Patch",
        "Modified Kugel Hernia Patch",
        "PerFix Light Plug Mesh",
        "PerFix Plug Mesh",
        "PolySoft Hernia Patch",
        "Sepramesh IP Composite",
        "SoftMesh",
        "Ventralex Hernia Patch",
        "Ventrio Hernia Patch	",
        "Omyra Mesh",
        "Optilene Mesh",
        "Optilene Mesh Elastic",
        "Optilene Mesh LP",
        "Premilene Mesh",
        "Premilene Mesh Plug",
        "Safil Mesh",
        "Biodesign – Surgisis Hernia Graft",
        "Biodesign – Surgisis Hiatal Hernia Graft",
        "Biodesign – Surgisis Inguinal Hernia Graft",
        "Biodesign – Surgisis 8-Layer Tissue Graft",
        "Parietene Composite Polypropylene Mesh",
        "Parietene ProGrip Self-Fixating Mesh",
        "Parietene Standard Polypropylene Mesh",
        "Parietene Light Polypropylene Mesh",
        "Parietex Anatomical Mesh",
        "Parietex Anatomical Mesh, lateral slit",
        "Parietex Anatomical Mesh, lat. slit & self grip",
        "Parietex Anatomical No-Touch",
        "Parietex Composite Mesh",
        "Parietex Composite Hiatal Mesh",
        "Parietex Composite Parastomal Mesh",
        "Parietex Composite Skirted Mesh",
        "Parietex EaseGrip Mesh",
        "Parietex Folding Mesh",
        "Parietex Folding Mesh, slit",
        "Parietex Folding Mesh No-Touch",
        "Parietex Plug",
        "Parietex ProGrip Self-Fixating Mesh",
        "Parietex Rigid No-Touch",
        "Parietex Three Dimensional Mesh",
        "Parietex Two Dimensional Mesh",
        "Parietex Two Dimensional Mesh Rigid",
        "Permacol Biological Implant",
        "Surgipro Monofilament Mesh",
        "Surgipro Open Weave Mesh",
        "Surgipro Polypropylene Mesh",
        "DynaMesh-IPOM",
        "DynaMesh-PP Light",
        "DynaMesh-PP Standard",
        "DynaMesh-IPST	",
        "Endoroll Prolene Mesh",
        "Mersilene Mesh",
        "Proceed Mesh",
        "Proceed Ventral Patch (PVP) ",
        "Prolene Mesh",
        "Prolene 3D Patch",
        "Prolene Hernia System (PHS)",
        "Ultrapro Mesh",
        "Ultrapro Hernia System (UHS)",
        "Ultrapro Plug",
        "Vicryl Mesh",
        "Vicryl Membrane",
        "Vypro Mesh",
        "Vypro Blue Mesh",
        "Vypro visor Mesh",
        "Vypro ll Mesh	",
        "TiLene Guard light",
        "TiLene Guard dual-weight",
        "TiLene Guard Set",
        "TiLene Plug dual-weight",
        "TiLene Plug Set",
        "TiLene Strip light",
        "TiLene Strip strong",
        "TiMesh extralight",
        "TiMesh light",
        "TiMesh strong",
        "TiPatch light",
        "TiPatch strong",
        "TiPlug System light",
        "TiSure light",
        "TiSure strong  	",
        "BIO-A Hernia Plug",
        "BIO-A Tissue Reinforcement",
        "DualMesh Biomaterial",
        "DualMesh Plus Biomaterial",
        "GORE-TEX Soft Tissue Patch",
        "Infinit Mesh",
        "Mycromesh Biomaterial",
        "Mycromesh Plus Biomaterial		",
        "AlloDerm Regenerative Tissue Matrix",
        "Strattice Reconstructive Tissue Matrix",
        "Seramesh LE",
        "Seramesh PA",
        "Seramesh SE",
        "Seramesh SO",
        "Tutomesh"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO Meshes (id, mesh) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillFixationTypesTable()
{
    QStringList list =
    {
        "Самофиксация",
        "Не абсорбированный шовный материал",
        "Абсорбированный шовный материал",
        "Такеры"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO FixationTypes (id, type) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillTuckersTable()
{
    QStringList list =
    {
        "Bard – PermaSorb Disposable Fixat. System",
        "Bard – SorbaFix Absorbable Fixation System",
        "Covidien – AbsorbaTack Fixation Device",
        "Covidien – Endo Universal Stapler",
        "Covidien – I-Clip Fixation Device",
        "Covidien – Multifire Endo Hernia Stapler",
        "Covidien – Covidien – ProTack Fixation Device",
        "Covidien – StatTack Fixation Device",
        "Covidien – Tacker Fixation Device",
        "Covidien – VersaTack Stapler",
        "Ethicon – EMS Stapler",
        "Ethicon – EndoAnchor"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO Tuckers (id, tucker) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillPeritoneumClosuresTable()
{
    QStringList list =
    {
        "Клей",
        "Шов",
        "Такеры"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO PeritoneumClosures (id, closure) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillSeromaSizesTable()
{
    QStringList list =
    {
        "< 3 мм",
        "3 - 6 мм",
        "> 6 мм"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO SeromaSizes (id, size) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillOperationTechniquesTable()
{
    QStringList list =
    {
        "Натяжной способ",
        "Ненатяжной способ"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO OperationTechniques (id, technique) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillOccupationsTable()
{
    QStringList list =
    {
        "Тяжелый физический труд",
        "Умеренный физический труд",
        "Сидячая работа",
        "Безработный"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO Occupations (id, occupation) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillSportActivitiesTable()
{
    QStringList list =
    {
        "Не занимающийся спортом",
        "Случайные занятия спортом (1 раз / мес.)",
        "Умеренные занятия спортом (1 раз / нед.)",
        "Интенсивные занятия спортом (>1 раз / нед.)"

    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO SportActivities (id, activity) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}





void DBWorker::fillSmokingHistoriesTable()
{
    QStringList list =
    {
        "Никогда не куривший",
        "Бывший курильщик (бросил >12 мес. назад)",
        "Курит изредка",
        "Постоянный курильщик"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO SmokingHistories (id, history) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

void DBWorker::fillDiagnosticMethodsTable()
{
    QStringList list =
    {
        "Клиническое обследование",
        "УЗИ (положение на спине)",
        "УЗИ (положение стоя)",
        "КТ обследование",
        "МРТ обследование"
    };
    QSqlQuery q(this->m_db);

    int id = 1;
    for(auto str: list)
    {
        q.prepare("INSERT INTO DiagnosticMethods (id, method) VALUES(?,?)");
        q.addBindValue(id);
        q.addBindValue(str);
        q.exec();
        ++id;
    }
}

QStringList DBWorker::herniaTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM HerniaTypes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::ventralHerniaTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM VentralHerniaTypes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::ventralMidlineHerniaTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM VentralMidlineHerniaTypes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::ventralLateralHerniaTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM VentralLateralHerniaTypes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::ventralHerniaWidths()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT width FROM VentralHerniaWidths");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::groinHerniaTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM GroinHerniaTypes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::groinHerniaExaminations()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT examination FROM GroinHerniaExaminations");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::sides()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT side FROM Sides");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

//QStringList DBWorker::recurrentOperationSpecifications()
//{
//    QStringList list;
//    QSqlQuery q(this->m_db);
//    q.prepare("SELECT specification FROM RecurrentOperationSpecifications");
//    q.exec();
//    while(q.next())
//        list.push_back(q.value(0).toString());
//    return list;
//}

//QStringList DBWorker::hernialHoleSizes()
//{
//    QStringList list;
//    QSqlQuery q(this->m_db);
//    q.prepare("SELECT size FROM HernialHoleSizes");
//    q.exec();
//    while(q.next())
//        list.push_back(q.value(0).toString());
//    return list;
//}

//QStringList DBWorker::hernialSacSizes()
//{
//    QStringList list;
//    QSqlQuery q(this->m_db);
//    q.prepare("SELECT size FROM HernialSacSizes");
//    q.exec();
//    while(q.next())
//        list.push_back(q.value(0).toString());
//    return list;
//}

QStringList DBWorker::tissueRepairTechniques()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT technique FROM TissueRepairTechniques");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::meshImplantRepairTechniques()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT technique FROM MeshImplantRepairTechniques");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::meshes(int userId)
{
    // В первую очередь ищутся сетки из таблицы LastAddedMeshes для пользоваьеля с id = userId
    QStringList lastAddedMeshes;
    QSqlQuery q(this->m_db);

    if(userId > 0)
    {
        q.prepare("SELECT mesh_id FROM LastAddedMeshes WHERE user_id = ?");
        q.addBindValue(userId);
        if(!q.exec())
            qDebug() << "DBWorker::meshes: ошибка при нахождении последних добавленных сеток";
        else
        {
            while(q.next())
            {
                int meshId = q.value(0).toInt();
                QString mesh = this->getMeshById(meshId);
                lastAddedMeshes.push_front(mesh);
            }
        }
    }

    QStringList otherMeshes;

    q.prepare("SELECT mesh FROM Meshes ORDER BY mesh");
    q.exec();
    while(q.next())
    {
        QString mesh = q.value(0).toString();
        if(userId > 0)
        {
            if(!lastAddedMeshes.contains(mesh))
                otherMeshes.push_back(mesh);
        }
        else
            otherMeshes.push_back(mesh);
    }
    if(userId > 0)
        return lastAddedMeshes << otherMeshes;
    return  otherMeshes;
}

QStringList DBWorker::fixationTypes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT type FROM FixationTypes ORDER BY type");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::tuckers()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT tucker FROM Tuckers ORDER BY tucker");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::peritoneumClosures()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT closure FROM PeritoneumClosures");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::seromaSizes()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT size FROM SeromaSizes");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::operationTechniques()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT technique FROM OperationTechniques");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::occupations()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT occupation FROM Occupations");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::sportActivities()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT activity FROM SportActivities");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::smokingHistories()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT history FROM SmokingHistories");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}

QStringList DBWorker::diagnosticMethods()
{
    QStringList list;
    QSqlQuery q(this->m_db);
    q.prepare("SELECT method FROM DiagnosticMethods");
    q.exec();
    while(q.next())
        list.push_back(q.value(0).toString());
    return list;
}
