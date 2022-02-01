#include "searchcomboboxelement.h"

SearchComboBoxElement::SearchComboBoxElement(const QString &text, bool elect, QObject *parent) :
    QObject(parent), m_text(text), m_elect(elect)
{

}

const QString &SearchComboBoxElement::text() const
{
    return m_text;
}

bool SearchComboBoxElement::elect() const
{
    return m_elect;
}

void SearchComboBoxElement::setElect(bool elect)
{
    m_elect = elect;
    electChanged();
}
