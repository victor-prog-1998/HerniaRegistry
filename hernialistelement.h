#ifndef HERNIALISTELEMENT_H
#define HERNIALISTELEMENT_H

#include <QObject>

class HerniaListElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int herniaId READ herniaId NOTIFY propertyChanged)
    Q_PROPERTY(QString type READ type NOTIFY propertyChanged)
    Q_PROPERTY(QString typeInfo READ typeInfo NOTIFY propertyChanged)
    Q_PROPERTY(QString side READ side NOTIFY propertyChanged)
    Q_PROPERTY(bool operation READ operation NOTIFY propertyChanged)
    Q_PROPERTY(QString operationInfo READ operationInfo NOTIFY propertyChanged)
    Q_PROPERTY(bool recurrence READ recurrence NOTIFY propertyChanged)
    Q_PROPERTY(int number READ number NOTIFY propertyChanged)

public:
    explicit HerniaListElement(int herniaId, int number, const QString& type, const QString& typeInfo, const QString& side, bool operation,
                        const QString& operationInfo, bool recurrence, QObject *parent = nullptr);

    int herniaId() const;
    const QString& type() const;
    const QString& typeInfo() const;
    const QString& side() const;
    bool operation() const;
    const QString& operationInfo() const;
    bool recurrence() const;
    int number() const;

private:
    int m_herniaId;
    int m_number;
    QString m_type;
    QString m_typeInfo; // тип грыжи указанного типа (например, если вентральная, то латеральная), а также подтип в случае вентральной
    QString m_side;
    bool m_operation;
    QString m_operationInfo; // метод лечения и техника операции
    bool m_recurrence;

signals:
    void propertyChanged();


public slots:
};

#endif // HERNIALISTELEMENT_H
