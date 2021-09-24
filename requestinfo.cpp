#include "requestinfo.h"

RequestInfo::RequestInfo(int doctorId, const QString &fio, const QString birthDate,
                         int experience, const QString &region,
                         const QString &locality, const QString &mainWork,
                         const QString &extraWork, const QString &speciality,
                         const QString &certificate, const QString &email, QObject *parent) :
    QObject(parent), m_doctorId(doctorId), m_fio(fio), m_birthDate(birthDate), m_experience(experience),
    m_region(region), m_locality(locality), m_mainWork(mainWork), m_extraWork(extraWork),
    m_speciality(speciality), m_certificate(certificate), m_email(email)
{

}

int RequestInfo::doctorId() const
{
    return this->m_doctorId;
}

const QString& RequestInfo::fio() const
{
    return this->m_fio;
}

const QString& RequestInfo::birthDate() const
{
    return this->m_birthDate;
}

int RequestInfo::experience() const
{
    return this->m_experience;
}

const QString& RequestInfo::region() const
{
    return this->m_region;
}

const QString& RequestInfo::locality() const
{
    return this->m_locality;
}

const QString& RequestInfo::mainWork() const
{
    return this->m_mainWork;
}
const QString& RequestInfo::extraWork() const
{
    return this->m_extraWork;
}
const QString& RequestInfo::speciality() const
{
    return this->m_speciality;
}
const QString& RequestInfo::certificate() const
{
    return this->m_certificate;
}
const QString& RequestInfo::email() const
{
    return this->m_email;
}
