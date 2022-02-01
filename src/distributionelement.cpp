#include "distributionelement.h"

DistributionElement::DistributionElement(const QString &label, int count,
                                         int percent, QObject *parent) :
    QObject(parent), m_label(label), m_count(count), m_percent(percent)
{

}


const QString& DistributionElement::label() const
{
    return this->m_label;
}

int DistributionElement::count() const
{
    return this->m_count;
}

float DistributionElement::percent() const
{
    return this->m_percent;
}

bool operator <(const DistributionElement &de1, const DistributionElement &de2)
{
    return de1.m_count < de2.m_count;
}
