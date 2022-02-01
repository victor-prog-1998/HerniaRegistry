#ifndef STATISTICSLISTELEMENT_H
#define STATISTICSLISTELEMENT_H

#include <QObject>

class StatisticsListElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sex READ sex NOTIFY sexChanged)
    Q_PROPERTY(QString birthDate READ birthDate NOTIFY birthDateChanged)
    Q_PROPERTY(int cardId READ cardId NOTIFY cardIdChanged)
    Q_PROPERTY(QString region READ region NOTIFY regionChanged)
public:
    explicit StatisticsListElement(int cardId, const QString &sex, const QString& birthDate,
                                   const QString& region, QObject *parent = nullptr);
    const QString& sex() const;
    const QString& birthDate() const;
    int cardId() const;
    const QString& region();

private:
    int m_cardId;
    QString m_sex;
    QString m_birthDate;
    QString m_region;

signals:
    void sexChanged();
    void birthDateChanged();
    void cardIdChanged();
    void regionChanged();
public slots:
};

#endif // STATISTICSLISTELEMENT_H
