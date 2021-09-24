#ifndef REQUESTINFO_H
#define REQUESTINFO_H

#include <QObject>


class RequestInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int doctorId READ doctorId NOTIFY doctorIdChanged)
    Q_PROPERTY(QString fio READ fio NOTIFY fioChanged)
    Q_PROPERTY(QString birthDate READ birthDate NOTIFY birthDateChanged)
    Q_PROPERTY(int experience READ experience NOTIFY experienceChanged)
    Q_PROPERTY(QString region READ region NOTIFY regionChanged)
    Q_PROPERTY(QString locality READ locality NOTIFY localityChanged)
    Q_PROPERTY(QString mainWork READ mainWork NOTIFY mainWorkChanged)
    Q_PROPERTY(QString extraWork READ extraWork NOTIFY extraWorkChanged)
    Q_PROPERTY(QString speciality READ speciality NOTIFY specialityChanged)
    Q_PROPERTY(QString certificate READ certificate NOTIFY certificateChanged)
    Q_PROPERTY(QString email READ email NOTIFY emailChanged)
public:
    explicit RequestInfo(int doctorId, const QString& fio, const QString birthDate, int experience, const QString& region,
                         const QString& locality, const QString& mainWork, const QString& extraWork,
                         const QString& speciality, const QString& certificate, const QString& email,
                          QObject *parent = nullptr);

    int doctorId() const;
    const QString& fio() const;
    const QString& birthDate() const;
    int experience() const;
    const QString& region() const;
    const QString& locality() const;
    const QString& mainWork() const;
    const QString& extraWork() const;
    const QString& speciality() const;
    const QString& certificate() const;
    const QString& email() const;

private:
    int m_doctorId;
    QString m_fio;
    QString m_birthDate;
    int m_experience;
    QString m_region;
    QString m_locality;
    QString m_mainWork;
    QString m_extraWork;
    QString m_speciality;
    QString m_certificate;
    QString m_email;

signals:
    void doctorIdChanged();
    void fioChanged();
    void birthDateChanged();
    void experienceChanged();
    void regionChanged();
    void localityChanged();
    void mainWorkChanged();
    void extraWorkChanged();
    void specialityChanged();
    void certificateChanged();
    void emailChanged();

public slots:
};

#endif // REQUESTINFO_H
