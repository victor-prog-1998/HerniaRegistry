#ifndef MAINCARDINFO_H
#define MAINCARDINFO_H

#include <QObject>

class MainCardInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fio READ fio NOTIFY fioChanged)
    Q_PROPERTY(QString birthDate READ birthDate NOTIFY birthDateChanged)
    Q_PROPERTY(QString sex READ sex NOTIFY sexChanged)
    Q_PROPERTY(QString phone READ phone NOTIFY phoneChanged)
    Q_PROPERTY(int regionId READ regionId NOTIFY regionIdChanged)
    Q_PROPERTY(QString district READ district NOTIFY districtChanged)
    Q_PROPERTY(QString locality READ locality NOTIFY localityChanged)
    Q_PROPERTY(QString street READ street NOTIFY streetChanged)
    Q_PROPERTY(QString house READ house NOTIFY houseChanged)
    Q_PROPERTY(QString flat READ flat NOTIFY flatChanged)
    Q_PROPERTY(QString passport READ passport NOTIFY passportChanged)
    Q_PROPERTY(QString snils READ snils NOTIFY snilsChanged)
    Q_PROPERTY(QString polisType READ polisType NOTIFY polisTypeChanged)
    Q_PROPERTY(QString polisNumber READ polisNumber NOTIFY polisNumberChanged)
    Q_PROPERTY(QString bloodType READ bloodType NOTIFY bloodTypeChanged)
    Q_PROPERTY(QString rhesusFactor READ rhesusFactor NOTIFY rhesusFactorChanged)
    Q_PROPERTY(int weight READ weight NOTIFY weightChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(QString complaints READ complaints NOTIFY complaintsChanged)

public:
    explicit MainCardInfo(const QString& fio, const QString& birthDate,const QString& sex, const QString& phone,
                          int regionId, const QString& district, const QString& locality, const QString& street,
                          const QString& house,const QString& flat,const QString& passport,const QString& snils,
                          const QString& polisType, const QString& polisNumber, const QString& bloodType,
                          const QString& rhesusFactor, int weight,int height,
                          const QString& complaints, QObject *parent = nullptr);


    const QString& fio() const;
    const QString& birthDate() const;
    const QString& sex() const;
    const QString& phone() const;
    int regionId() const;
    const QString& district() const;
    const QString& locality() const;
    const QString& street() const;
    const QString& house() const;
    const QString& flat() const;
    const QString& passport() const;
    const QString& snils() const;
    const QString& polisType() const;
    const QString& polisNumber() const;
    const QString& bloodType() const;
    const QString& rhesusFactor() const;
    int weight() const;
    int height() const;
    const QString& complaints() const;

private:
    QString m_fio;
    QString m_birthDate;
    QString m_sex;
    QString m_phone;
    int m_regionId;
    QString m_district;
    QString m_locality;
    QString m_street;
    QString m_house;
    QString m_flat;
    QString m_passport;
    QString m_snils;
    QString m_polisType;
    QString m_polisNumber;
    QString m_bloodType;
    QString m_rhesusFactor;
    int m_weight;
    int m_height;
    QString m_complaints;

signals:

    void fioChanged();
    void birthDateChanged();
    void sexChanged();
    void phoneChanged();
    void regionIdChanged();
    void districtChanged();
    void localityChanged();
    void streetChanged();
    void houseChanged();
    void flatChanged();
    void passportChanged();
    void snilsChanged();
    void polisTypeChanged();
    void polisNumberChanged();
    void bloodTypeChanged();
    void rhesusFactorChanged();
    void weightChanged();
    void heightChanged();
    void complaintsChanged();

public slots:
};

#endif // MAINCARDINFO_H
