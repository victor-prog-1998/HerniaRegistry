#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <QObject>


/* Класс со вспомогательными функциями, в основном для проверки введенных данных

 ! В QML версии не проводим проверку введенных данных на пустоту
 Этим занимаются формы qml. Кнопки отправки данных становятся активными
 только когда все обязательные поля заполнены. Поэтому функции check...()
 проверяют только корректность данных.
 Проверку фиксированной длины (паспорт, СНИЛС и т д) также не проводим
*/


class MyFunctions : public QObject
{
    Q_OBJECT
public:
    explicit MyFunctions(QObject *parent = nullptr);

    Q_INVOKABLE bool checkLetterString(const QString& str); //проверка строки, в которой должны быть только буквы и пробелы

    Q_INVOKABLE bool checkPrintableString(const QString& str, bool lineFeed = false); // печатная строка: содержит цифры,
                                                                                 // буквы и знаки препинания
                                                                          // lineFeed отвечает за возможность перевода строки

    Q_INVOKABLE bool checkNum(const QString& numString, bool zeroIsAllowed = true);
    Q_INVOKABLE bool checkPassword(const QString& passwordString);
    Q_INVOKABLE bool checkEmail(const QString& emailString);
    Q_INVOKABLE bool checkLogin(const QString& loginString);
    Q_INVOKABLE bool checkPhone(const QString& phoneString);
    Q_INVOKABLE bool checkSnils(const QString& snilsString);
    Q_INVOKABLE bool checkFio(const QString& fio); // больше не нужна, так как фамилия имя и отчество вводятся по отдельности
    Q_INVOKABLE bool checkCapitalizeWord(const QString& word); // проверяет, является ли строка словом, начинающимся с заглавной буквы
    Q_INVOKABLE bool letterDigitPointHyphenUnderscore(const QString& string); /*вспомогательная функция, используемая при проверке
                                                                    логинов, паролей, email'ов
                                                                    возвращает true, только если символы -
                                                                    буквы, цифры, точки, дефисы или подчеркивания  */




    Q_INVOKABLE bool checkPatientCardFields(const QString& cardNumber, const QString& fio, const QDate& birthDate,
                                const QString& sex, const QString& phone, const QString& region,
                                const QString& district, const QString& locality, const QString& street,
                                const QString& house, const QString& flat, const QString& passportSeries,
                                const QString& passportNumber, const QString& snils, const QString& polisType,
                                const QString& polisNumber, const QString& weight,
                                const QString& height, const QString& complaints);

    //*************** работа с датами ************************************
    static QString dateToNormalFormat(const QString& dateInStandartFormat); // Преобразование строки с датой в формат ДД.ММ.ГГГГ
    // парсинг дня, месяца и года из даты, приведенной к виду ДД.ММ.ГГГГ
    Q_INVOKABLE int parseDay(const QString& date);
    Q_INVOKABLE int parseMonth(const QString& date);
    Q_INVOKABLE int parseYear(const QString& date);

    // ********************* Для распределения ***************************************************

    static void calculatePercentList(const QList<int>& countList, QList<float>& emptyPercentList);
    static void sortDistributionList(QList<QObject*>& distList);


    // по виду ссылки на изображение опеределяет, является ли оно загруженным из провайдера (ImageProvider)
    static bool imageIsFromProvider(const QString& source);


signals:

public slots:
};

#endif // MYFUNCTIONS_H
