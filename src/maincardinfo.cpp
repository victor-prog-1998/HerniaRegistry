#include "maincardinfo.h"

MainCardInfo::MainCardInfo(const QString &fio,
                           const QString &birthDate,
                           const QString &sex,
                           const QString &phone,
                           int regionId,
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
                           int weight, int height,
                           const QString &complaints,
                           QObject *parent) :

                            QObject(parent), m_fio(fio), m_birthDate(birthDate), m_sex(sex), m_phone(phone),
                            m_regionId(regionId), m_district(district), m_locality(locality),
                            m_street(street), m_house(house), m_flat(flat), m_passport(passport),
                            m_snils(snils), m_polisType(polisType), m_polisNumber(polisNumber),
                            m_bloodType(bloodType), m_rhesusFactor(rhesusFactor), m_weight(weight),
                            m_height(height), m_complaints(complaints)
{

}

const QString &MainCardInfo::fio() const
{
    return this->m_fio;
}

const QString &MainCardInfo::birthDate() const
{
    return this->m_birthDate;
}

const QString &MainCardInfo::sex() const
{
    return this->m_sex;
}

const QString &MainCardInfo::phone() const
{
    return this->m_phone;
}

int MainCardInfo::regionId() const
{
    return this->m_regionId;
}

const QString &MainCardInfo::district() const
{
    return this->m_district;
}

const QString &MainCardInfo::locality() const
{
    return this->m_locality;
}

const QString &MainCardInfo::street() const
{
    return this->m_street;
}

const QString &MainCardInfo::house() const
{
    return this->m_house;
}

const QString &MainCardInfo::flat() const
{
    return this->m_flat;
}

const QString &MainCardInfo::passport() const
{
    return this->m_passport;
}

const QString &MainCardInfo::snils() const
{
    return this->m_snils;
}

const QString &MainCardInfo::polisType() const
{
    return this->m_polisType;
}

const QString &MainCardInfo::polisNumber() const
{
    return this->m_polisNumber;
}

const QString &MainCardInfo::bloodType() const
{
    return this->m_bloodType;
}

const QString &MainCardInfo::rhesusFactor() const
{
    return this->m_rhesusFactor;
}

int MainCardInfo::weight() const
{
    return this->m_weight;
}

int MainCardInfo::height() const
{
    return this->m_height;
}

const QString &MainCardInfo::complaints() const
{
    return this->m_complaints;
}
