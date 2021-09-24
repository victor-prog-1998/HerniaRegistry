#include "statisticslistelement.h"
#include "myfunctions.h"

StatisticsListElement::StatisticsListElement(int cardId, const QString &sex, const QString& birthDate,
                                             const QString& region, QObject *parent) :
    QObject(parent), m_cardId(cardId), m_region(region)
{
    m_birthDate = MyFunctions::dateToNormalFormat(birthDate);
    m_sex = (sex == "М") ? "Мужской" : "Женский";
}

const QString &StatisticsListElement::sex() const
{
    return this->m_sex;
}

const QString &StatisticsListElement::birthDate() const
{
    return this->m_birthDate;
}

int StatisticsListElement::cardId() const
{
    return this->m_cardId;
}

const QString &StatisticsListElement::region()
{
    return this->m_region;
}
