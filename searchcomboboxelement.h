#ifndef SEARCHCOMBOBOXELEMENT_H
#define SEARCHCOMBOBOXELEMENT_H

#include <QObject>

class SearchComboBoxElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(bool elect READ elect WRITE setElect NOTIFY electChanged)
public:
    explicit SearchComboBoxElement(const QString& text, bool elect, QObject *parent = nullptr);

    const QString& text() const;

    bool elect() const;
    void setElect(bool elect);

private:
    QString m_text;
    bool m_elect;
signals:
    void electChanged();

};

#endif // SEARCHCOMBOBOXELEMENT_H
