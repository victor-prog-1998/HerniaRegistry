#ifndef PATIENTLISTELEMENT_H
#define PATIENTLISTELEMENT_H

#include <QObject>

// фио снилс пол др + доступ к просмотру и доступ к редактированию

class PatientListElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fio READ fio NOTIFY fioChanged)
    Q_PROPERTY(QString sex READ sex NOTIFY sexChanged)
    Q_PROPERTY(QString birthDate READ birthDate NOTIFY birthDateChanged)
    Q_PROPERTY(QString snils READ snils NOTIFY snilsChanged)
    Q_PROPERTY(bool viewIsAvailable READ viewIsAvailable NOTIFY viewIsAvailableChanged)
    Q_PROPERTY(bool editIsAvailable READ editIsAvailable NOTIFY editIsAvailableChanged)
    Q_PROPERTY(int cardId READ cardId NOTIFY cardIdChanged)

public:
    explicit PatientListElement(int cardId, const QString& fio, const QString &sex, const QString& birthDate,
                                const QString& snils, bool viewIsAvailable, bool editIsAvailable,
                                QObject *parent = nullptr);

    const QString& fio() const;
    const QString& sex() const;
    const QString& birthDate() const;
    const QString& snils() const;
    bool viewIsAvailable() const;
    bool editIsAvailable() const;
    int cardId() const;
    void setViewAvailability(bool available);
    void setEditAvailability(bool available);

private:
    QString m_fio;
    QString m_sex;
    QString m_birthDate;
    QString m_snils;
    bool m_viewIsAvailable;
    bool m_editIsAvailable;
    int m_cardId;

signals:
    void fioChanged();
    void sexChanged();
    void birthDateChanged();
    void snilsChanged();
    void viewIsAvailableChanged();
    void editIsAvailableChanged();
    void cardIdChanged();

public slots:
};

#endif // PATIENTLISTELEMENT_H
