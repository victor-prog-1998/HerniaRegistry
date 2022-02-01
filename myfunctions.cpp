#include "myfunctions.h"
#include <QRegExp>
#include <QDate>
#include "distributionelement.h"

MyFunctions::MyFunctions(QObject *parent) : QObject(parent)
{

}

bool MyFunctions::checkLetterString(const QString &str)
{
    for(const QChar *ch = str.begin(); ch != str.end(); ++ch)
        if ((!ch->isLetter()) && (!ch->isSpace()))
            return false;
    return true;
}

bool MyFunctions::checkPrintableString(const QString &str, bool lineFeed)
{
    if(!lineFeed)
    {
        for(auto ch: str)
        {
            if(!ch.isPrint())
                return false;
        }
    }
    else        // когда перевод строки разрешен
    {
        for(auto ch:str)
            if((!ch.isPrint()) && (ch != '\n'))
                return false;
    }
    return true;
}

bool MyFunctions::checkNum(const QString &numString, bool zeroIsAllowed)
{
//    bool ok;     плохая идея, т.к. могут быть огромные числа - номер полиса и.т.д
//    numString.toUInt(&ok);
//    return ok;
    for(auto ch: numString)
        if(!ch.isDigit())
            return false;
    if(numString[0] == '0')
    {
        if(!zeroIsAllowed ||(numString.length() != 1))
            return false;
    }

    return true;
}

bool MyFunctions::letterDigitPointHyphenUnderscore(const QString &string)
{
    for(auto ch: string)
    {
        if((!ch.isLetterOrNumber()) && (!QString("-_.").contains(ch)))
            return false;
    }
    return true;
}

bool MyFunctions::checkLogin(const QString &loginString)
{
    if(!letterDigitPointHyphenUnderscore(loginString))
        return false;
    if(!loginString[0].isLetter())
        return false;   //первый символ может быть только буквой
    if(!loginString[loginString.size() - 1].isLetterOrNumber())
        return false;   //последний символ может быть только либо буквой, либо цифрой
    return true;
}

bool MyFunctions::checkEmail(const QString &emailString)
{
    if(!emailString.contains('@'))
        return false;
    QString beforeDog;
    QString afterDog;
    auto ch = emailString.begin();
    while(*ch != '@')
    {
        beforeDog += *ch;
        ++ch;
    }
    ++ch;
    while(ch != emailString.end())
    {
        afterDog += *ch;
        ++ch;
    }

    if((!checkLogin(beforeDog)) || (!checkLogin(afterDog)))
        return false;

    if(!afterDog.contains('.'))
        return false;

    return true;
}

bool MyFunctions::checkPassword(const QString &passwordString)
{
    return letterDigitPointHyphenUnderscore(passwordString);
}

QString MyFunctions::dateToNormalFormat(const QString &dateInStandartFormat)
{
    QStringList list = dateInStandartFormat.split('-');
    return list[2] + '.' + list[1] + '.' + list[0];
}

int MyFunctions::parseDay(const QString &date)
{
    QStringList list = date.split('.');
    return list[0].toInt();
}

int MyFunctions::parseMonth(const QString &date)
{
    QStringList list = date.split('.');
    return list[1].toInt();
}

int MyFunctions::parseYear(const QString &date)
{
    QStringList list = date.split('.');
    return list[2].toInt();
}

void MyFunctions::calculatePercentList(const QList<int> &countList, QList<float> &emptyPercentList)
{
    int sum = 0;
    for(auto count: countList)
        sum += count;
    for(auto count: countList)
        emptyPercentList.push_back(count * 100.0 / sum );
}

void MyFunctions::sortDistributionList(QList<QObject *> &distList)
{
    std::sort(distList.begin(), distList.end(), [](QObject* el1, QObject* el2)
    {return *(qobject_cast<DistributionElement*>(el1)) < *(qobject_cast<DistributionElement*>(el2));});
}

bool MyFunctions::imageIsFromProvider(const QString &source)
{
    // Пример ссылки на изображение из провайдера  "image://provider/image_1"
    // Результат - лог. выражение: является ли подстрока из первых 8 символов строкой "image://"
    return (source.left(8) == "image://");
}

bool MyFunctions::checkPatientCardFields(const QString &cardNumber,
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
        const QString &passportSeries,
        const QString &passportNumber,
        const QString &snils,
        const QString &polisType,
        const QString &polisNumber,
        const QString &weight,
        const QString &height,
        const QString &complaints)
{


    QString emptyFields;

    if(cardNumber.isEmpty())
        emptyFields += "\nНомер карты";
    if(fio.isEmpty())
        emptyFields += "\nФИО";
    if(sex.isEmpty())
        emptyFields += "\nПол";
    if(phone.isEmpty())
        emptyFields += "\nТелефон";
    if(region.isEmpty())
        emptyFields += "\nРегион";
    if(locality.isEmpty())
        emptyFields += "\nНаселенный пункт";
    if(street.isEmpty())
        emptyFields += "\nУлица";
    if(house.isEmpty())
        emptyFields += "\nДом";
    if(passportSeries.isEmpty())
        emptyFields += "\nСерия паспорта";
    if(passportNumber.isEmpty())
        emptyFields += "\nНомер паспорта";
    if(snils.isEmpty())
        emptyFields += "\nСНИЛС";
    if(polisType.isEmpty())
        emptyFields += "\nТип полиса";
    if(polisNumber.isEmpty())
        emptyFields += "\nНомер полиса";

//    if(bloodType.isEmpty())
//        emptyFields += "\nГруппа крови";

    //    if(rhesusFactor.isEmpty())
    //        emptyFields += "\nРезус-фактор";

    if(weight.isEmpty())
        emptyFields += "\nВес";
    if(height.isEmpty())
        emptyFields += "\nРост";

    if(!emptyFields.isEmpty())
    {
        //QMessageBox::critical(0, "Недостаточно данных", "Пожалуйста, укажите следующие данные: " + emptyFields);
        return false;
    }

    QString errorFields;

    if(!checkNum(cardNumber))
        errorFields += "\nНомер карты";
    if(!checkLetterString(fio))
        errorFields += "\nФИО";
    if(birthDate > QDate::currentDate())
        errorFields += "\nДата рождения (позднее сегодняшней)";
    if(!checkPhone(phone))
        errorFields += "\nТелефон";
    if((!district.isEmpty()) && (!checkPrintableString(district)))
        errorFields += "\nРайон";
    if(!checkPrintableString(locality))
        errorFields += "\nНаселенный пункт";
    if(!checkPrintableString(street))
        errorFields += "\nУлица";
    if(!checkPrintableString(house))
        errorFields += "\nДом";
    if((!flat.isEmpty())&&(!checkNum(flat)))
        errorFields += "\nКвартира";
    if((!checkNum(passportSeries)) || (passportSeries.length() != 4))
        errorFields += "\nСерия паспорта";
    if((!checkNum(passportNumber)) || (passportNumber.length() != 6))
        errorFields += "\nНомер паспорта";
    if(!checkSnils(snils))
        errorFields += "\nСНИЛС";
    if(!checkNum(polisNumber))
        errorFields += "\nНомер полиса";
    if(!checkNum(weight))
        errorFields += "\nВес";
    if(!checkNum(height))
        errorFields += "\nРост";
    if(!checkPrintableString(complaints, true))
        errorFields += "\nЖалобы";

    if(!errorFields.isEmpty())
    {
        //QMessageBox::critical(0, "Некорректный ввод",
                  //            "Обнаружены некорректные данные в следующих полях:" + errorFields);
        return false;
    }

    return true;
}

bool MyFunctions::checkPhone(const QString &phoneString)
{
    for(auto ch:phoneString)
        if(!QString("1234567890()+-").contains(ch))
            return false;
    return true;
}

bool MyFunctions::checkSnils(const QString &snilsString)
{
//    if(snilsString.length() != 14)
//        return false;
    for(auto ch:snilsString)
        if(!QString("1234567890 -").contains(ch))
            return false;
    return true;
}

bool MyFunctions::checkFio(const QString &fio)
{
    QRegExp re("([А-Я])([а-я])+ ([А-Я])([а-я])+ ([А-Я])([а-я])+");
    return re.exactMatch(fio);
}

bool MyFunctions::checkCapitalizeWord(const QString &word)
{
    QRegExp re("([А-Я])([а-я])+");
    return re.exactMatch(word);
}
