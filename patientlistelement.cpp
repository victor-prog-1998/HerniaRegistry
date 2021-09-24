#include "patientlistelement.h"
#include "myfunctions.h"
#include <QDebug>


PatientListElement::PatientListElement(int cardId, const QString& fio, const QString& sex, const QString& birthDate,
                                       const QString& snils, bool viewIsAvailable, bool editIsAvailable,
                                       QObject *parent) :
    QObject(parent), m_fio(fio), m_snils(snils),
    m_viewIsAvailable(viewIsAvailable), m_editIsAvailable(editIsAvailable), m_cardId(cardId)
{
    m_birthDate = MyFunctions::dateToNormalFormat(birthDate);
    qDebug() << "sex: " << sex;
    m_sex = (sex == "М") ? "Мужской" : "Женский";
}

const QString &PatientListElement::fio() const
{
    return m_fio;
}

const QString &PatientListElement::sex() const
{
    return m_sex;
}

const QString &PatientListElement::birthDate() const
{
    return m_birthDate;
}

const QString &PatientListElement::snils() const
{
    return m_snils;
}

bool PatientListElement::viewIsAvailable() const
{
    return m_viewIsAvailable;
}

bool PatientListElement::editIsAvailable() const
{
    return m_editIsAvailable;
}

int PatientListElement::cardId() const
{
    return m_cardId;
}

void PatientListElement::setViewAvailability(bool available)
{
    m_viewIsAvailable = available;
}

void PatientListElement::setEditAvailability(bool available)
{
    m_editIsAvailable = available;
}
