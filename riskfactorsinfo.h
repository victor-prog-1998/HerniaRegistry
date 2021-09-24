#ifndef RISKFACTORSINFO_H
#define RISKFACTORSINFO_H

#include <QObject>

class RiskFactorsInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int occupationId READ occupationId NOTIFY occupationIdChanged)
    Q_PROPERTY(int sportActivitiesId READ sportActivitiesId NOTIFY sportActivitiesIdChanged)
    Q_PROPERTY(int smokingHistoryId READ smokingHistoryId NOTIFY smokingHistoryIdChanged)
    Q_PROPERTY(int cigsPerDay READ cigsPerDay NOTIFY cigsPerDayChanged)
    Q_PROPERTY(int yearsOfSmoking READ yearsOfSmoking NOTIFY yearsOfSmokingChanged)
    Q_PROPERTY(bool diabetesI READ diabetesI NOTIFY diabetesIChanged)
    Q_PROPERTY(bool diabetesII READ diabetesII NOTIFY diabetesIIChanged)
    Q_PROPERTY(bool hobl READ hobl NOTIFY hoblChanged)
    Q_PROPERTY(bool hypertension READ hypertension NOTIFY hypertensionChanged)
    Q_PROPERTY(bool heartDisease READ heartDisease NOTIFY heartDiseaseChanged)
    Q_PROPERTY(bool kidneyDisease READ kidneyDisease NOTIFY kidneyDiseaseChanged)
    Q_PROPERTY(bool gastritis READ gastritis NOTIFY gastritisChanged)
    Q_PROPERTY(bool aorticAneurysm READ aorticAneurysm NOTIFY aorticAneurysmChanged)
    Q_PROPERTY(bool immunosuppression READ immunosuppression NOTIFY immunosuppressionChanged)
    Q_PROPERTY(bool coagulopathy READ coagulopathy NOTIFY coagulopathyChanged)
    Q_PROPERTY(bool plateletAggregationInhibitors READ plateletAggregationInhibitors NOTIFY plateletAggregationInhibitorsChanged)
    Q_PROPERTY(QString otherFactors READ otherFactors NOTIFY otherFactorsChanged)
public:
    explicit RiskFactorsInfo(int occupationId, int sportActivitiesId, int smokingHistoryId,
                             int cigsPerDay, int yearsOfSmoking, bool diabetesI, bool diabetesII,
                             bool hobl, bool hypertension, bool heartDisease, bool kidneyDisease,
                             bool gastritis, bool aorticAneurysm,
                             bool immunosuppression, bool coagulopathy,
                             bool plateletAggregationInhibitors,
                             const QString& otherFactors, QObject *parent = nullptr);
    int occupationId() const;
    int sportActivitiesId() const;
    int smokingHistoryId() const;
    int cigsPerDay() const;
    int yearsOfSmoking() const;
    bool diabetesI() const;
    bool diabetesII() const;
    bool hobl() const;
    bool hypertension() const;
    bool heartDisease() const;
    bool kidneyDisease() const;
    bool gastritis() const;
    bool aorticAneurysm() const;
    bool immunosuppression() const;
    bool coagulopathy() const;
    bool plateletAggregationInhibitors() const;
    const QString& otherFactors() const;


private:
    int m_occupationId;
    int m_sportActivitiesId;
    int m_smokingHistoryId;
    int m_cigsPerDay;
    int m_yearsOfSmoking;
    bool m_diabetesI;
    bool m_diabetesII;
    bool m_hobl;
    bool m_hypertension;
    bool m_heartDisease;
    bool m_kidneyDisease;
    bool m_gastritis;
    bool m_aorticAneurysm;
    bool m_immunosuppression;
    bool m_coagulopathy;
    bool m_plateletAggregationInhibitors;
    QString m_otherFactors;


signals:
    void occupationIdChanged();
    void sportActivitiesIdChanged();
    void smokingHistoryIdChanged();
    void cigsPerDayChanged();
    void yearsOfSmokingChanged();
    void diabetesIChanged();
    void diabetesIIChanged();
    void hoblChanged();
    void hypertensionChanged();
    void heartDiseaseChanged();
    void kidneyDiseaseChanged();
    void gastritisChanged();
    void aorticAneurysmChanged();
    void immunosuppressionChanged();
    void coagulopathyChanged();
    void plateletAggregationInhibitorsChanged();
    void otherFactorsChanged();
public slots:
};

#endif // RISKFACTORSINFO_H
