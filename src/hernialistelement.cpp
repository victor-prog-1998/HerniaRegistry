#include "hernialistelement.h"

HerniaListElement::HerniaListElement(int herniaId, int number, const QString &type, const QString &typeInfo,
                       const QString &side, bool operation, const QString &operationInfo,
                       bool recurrence, QObject *parent) : QObject(parent),
    m_herniaId(herniaId), m_number(number), m_type(type), m_typeInfo(typeInfo), m_side(side), m_operation(operation),
    m_operationInfo(operationInfo), m_recurrence(recurrence)
{

}


int HerniaListElement::herniaId() const
{
    return this->m_herniaId;
}

const QString& HerniaListElement::type() const
{
    return this->m_type;
}

const QString& HerniaListElement::typeInfo() const
{
    return this->m_typeInfo;
}

const QString& HerniaListElement::side() const
{
    return this->m_side;
}

bool HerniaListElement::operation() const
{
    return this->m_operation;
}

const QString& HerniaListElement::operationInfo() const
{
    return this->m_operationInfo;
}

bool HerniaListElement::recurrence() const
{
    return this->m_recurrence;
}

int HerniaListElement::number() const
{
    return this->m_number;
}
