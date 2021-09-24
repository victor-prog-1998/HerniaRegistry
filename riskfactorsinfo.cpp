#include "riskfactorsinfo.h"

RiskFactorsInfo::RiskFactorsInfo(int occupationId, int sportActivitiesId, int smokingHistoryId,
                                 int cigsPerDay, int yearsOfSmoking, bool diabetesI, bool diabetesII,
                                 bool hobl, bool hypertension, bool heartDisease, bool kidneyDisease,
                                 bool gastritis, bool aorticAneurysm,
                                 bool immunosuppression, bool coagulopathy,
                                 bool plateletAggregationInhibitors,
                                 const QString& otherFactors, QObject *parent) :
    QObject(parent), m_occupationId(occupationId), m_sportActivitiesId(sportActivitiesId), m_smokingHistoryId(smokingHistoryId),
    m_cigsPerDay(cigsPerDay), m_yearsOfSmoking(yearsOfSmoking), m_diabetesI(diabetesI), m_diabetesII(diabetesII),
    m_hobl(hobl), m_hypertension(hypertension), m_heartDisease(heartDisease), m_kidneyDisease(kidneyDisease),
    m_gastritis(gastritis), m_aorticAneurysm(aorticAneurysm), m_immunosuppression(immunosuppression),
    m_coagulopathy(coagulopathy), m_plateletAggregationInhibitors(plateletAggregationInhibitors), m_otherFactors(otherFactors)
{

}

int RiskFactorsInfo::occupationId()const
{
    return this->m_occupationId;
}

int RiskFactorsInfo::sportActivitiesId()const
{
    return this->m_sportActivitiesId;
}

int RiskFactorsInfo::smokingHistoryId()const
{
    return this->m_smokingHistoryId;
}

int RiskFactorsInfo::cigsPerDay()const
{
    return this->m_cigsPerDay;
}

int RiskFactorsInfo::yearsOfSmoking()const
{
    return this->m_yearsOfSmoking;
}

bool RiskFactorsInfo::diabetesI()const
{
    return this->m_diabetesI;
}

bool RiskFactorsInfo::diabetesII()const
{
    return this->m_diabetesII;
}

bool RiskFactorsInfo::hobl()const
{
    return this->m_hobl;
}

bool RiskFactorsInfo::hypertension()const
{
    return this->m_hypertension;
}

bool RiskFactorsInfo::heartDisease()const
{
    return this->m_heartDisease;
}

bool RiskFactorsInfo::kidneyDisease()const
{
    return this->m_kidneyDisease;
}

bool RiskFactorsInfo::gastritis()const
{
    return this->m_gastritis;
}

bool RiskFactorsInfo::aorticAneurysm()const
{
    return this->m_aorticAneurysm;
}

bool RiskFactorsInfo::immunosuppression()const
{
    return this->m_immunosuppression;
}

bool RiskFactorsInfo::coagulopathy()const
{
    return this->m_coagulopathy;
}

bool RiskFactorsInfo::plateletAggregationInhibitors()const
{
    return this->m_plateletAggregationInhibitors;
}

const QString& RiskFactorsInfo::otherFactors()const
{
    return this->m_otherFactors;
}
