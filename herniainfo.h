#ifndef HERNIAINFO_H
#define HERNIAINFO_H

#include <QObject>

class HerniaInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString herniaType READ herniaType NOTIFY propertyChanged)
    Q_PROPERTY(QString ventralHerniaType READ ventralHerniaType NOTIFY propertyChanged)
    Q_PROPERTY(QString ventralHerniaSubtype READ ventralHerniaSubtype NOTIFY propertyChanged)
    Q_PROPERTY(QString ventralHerniaWidth READ ventralHerniaWidth NOTIFY propertyChanged)
    Q_PROPERTY(int ventralHerniaLength READ ventralHerniaLength NOTIFY propertyChanged)
    Q_PROPERTY(QString groinHerniaType READ groinHerniaType NOTIFY propertyChanged)
    Q_PROPERTY(QString groinHerniaExamination READ groinHerniaExamination NOTIFY propertyChanged)
    Q_PROPERTY(QString herniaSide READ herniaSide NOTIFY propertyChanged)
    Q_PROPERTY(bool recurrence READ recurrence NOTIFY propertyChanged)
    Q_PROPERTY(bool diagnostics READ diagnostics NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> clinicalExamination READ clinicalExamination NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> uziDorsal READ uziDorsal NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> uziStanding READ uziStanding NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> kt READ kt NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> mrt READ mrt NOTIFY propertyChanged)
    Q_PROPERTY(bool preoperativePainInRest READ preoperativePainInRest NOTIFY propertyChanged)
    Q_PROPERTY(int preoperativePainInRestDegree READ preoperativePainInRestDegree NOTIFY propertyChanged)
    Q_PROPERTY(bool preoperativePainInMotion READ preoperativePainInMotion NOTIFY propertyChanged)
    Q_PROPERTY(int preoperativePainInMotionDegree READ preoperativePainInMotionDegree NOTIFY propertyChanged)
    Q_PROPERTY(bool operation READ operation NOTIFY propertyChanged)
    Q_PROPERTY(QString operationSide READ operationSide NOTIFY propertyChanged)
    Q_PROPERTY(int ringWidth READ ringWidth NOTIFY propertyChanged)
    Q_PROPERTY(int sacWidth READ sacWidth NOTIFY propertyChanged)
    Q_PROPERTY(int sacLength READ sacLength NOTIFY propertyChanged)
    Q_PROPERTY(QString operationMethod READ operationMethod NOTIFY propertyChanged)
    Q_PROPERTY(QString operationTechnique READ operationTechnique NOTIFY propertyChanged)
    Q_PROPERTY(QString mesh READ mesh NOTIFY propertyChanged)
    Q_PROPERTY(int meshWidth READ meshWidth NOTIFY propertyChanged)
    Q_PROPERTY(int meshLength READ meshLength NOTIFY propertyChanged)
    Q_PROPERTY(QString fixationType READ fixationType NOTIFY propertyChanged)
    Q_PROPERTY(QString tuckers READ tuckers NOTIFY propertyChanged)
    Q_PROPERTY(QString peritoneumClosure READ peritoneumClosure NOTIFY propertyChanged)
    Q_PROPERTY(bool drainage READ drainage NOTIFY propertyChanged)
    Q_PROPERTY(bool intraoperativeComplications READ intraoperativeComplications NOTIFY propertyChanged)
    Q_PROPERTY(bool hemorrhage READ hemorrhage NOTIFY propertyChanged)
    Q_PROPERTY(bool nerveDamage READ nerveDamage NOTIFY propertyChanged)
    Q_PROPERTY(bool cordInjury READ cordInjury NOTIFY propertyChanged)
    Q_PROPERTY(bool bowelInjury READ bowelInjury NOTIFY propertyChanged)
    Q_PROPERTY(bool earlyPostoperativeComplications READ earlyPostoperativeComplications NOTIFY propertyChanged)
    Q_PROPERTY(bool woundInfection READ woundInfection NOTIFY propertyChanged)
    Q_PROPERTY(bool seroma READ seroma NOTIFY propertyChanged)
    Q_PROPERTY(QString seromaSize READ seromaSize NOTIFY propertyChanged)
    Q_PROPERTY(bool hematoma READ hematoma NOTIFY propertyChanged)
    Q_PROPERTY(bool cordSwelling READ cordSwelling NOTIFY propertyChanged)
    Q_PROPERTY(bool orchiepididymitis READ orchiepididymitis NOTIFY propertyChanged)
    Q_PROPERTY(bool latePostoperativeComplications READ latePostoperativeComplications NOTIFY propertyChanged)
    Q_PROPERTY(bool fistulas READ fistulas NOTIFY propertyChanged)
    Q_PROPERTY(bool meshRejection READ meshRejection NOTIFY propertyChanged)
    Q_PROPERTY(bool chronicNeuralgia READ chronicNeuralgia NOTIFY propertyChanged)
    Q_PROPERTY(bool testicularAtrophy READ testicularAtrophy NOTIFY propertyChanged)
    Q_PROPERTY(bool diseaseRecurrence READ diseaseRecurrence NOTIFY propertyChanged)
    Q_PROPERTY(bool earlyPain READ earlyPain  NOTIFY propertyChanged)
    Q_PROPERTY(QList<bool> earlyInRestPain READ earlyInRestPain NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> earlyInRestPainDegree READ earlyInRestPainDegree NOTIFY propertyChanged)
    Q_PROPERTY(QList<bool> earlyInMotionPain READ earlyInMotionPain NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> earlyInMotionPainDegree READ earlyInMotionPainDegree NOTIFY propertyChanged)

    Q_PROPERTY(QList<bool> earlyPainAnalgesics READ earlyPainAnalgesics NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> earlyPainAnalgesicsDays READ earlyPainAnalgesicsDays NOTIFY propertyChanged)
    Q_PROPERTY(QList<bool> earlyPainAnalgesicsOrally READ earlyPainAnalgesicsOrally NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> earlyPainAnalgesicsOrallyDays READ earlyPainAnalgesicsOrallyDays NOTIFY propertyChanged)
    Q_PROPERTY(QList<bool> earlyPainAnalgesicsInjections READ earlyPainAnalgesicsInjections NOTIFY propertyChanged)
    Q_PROPERTY(QList<int> earlyPainAnalgesicsInjectionsDays READ earlyPainAnalgesicsInjectionsDays NOTIFY propertyChanged)

    Q_PROPERTY(bool nerveInjury READ nerveInjury NOTIFY propertyChanged)
    Q_PROPERTY(bool chronicPainInRest READ chronicPainInRest NOTIFY propertyChanged)
    Q_PROPERTY(int chronicPainInRestDegree READ chronicPainInRestDegree NOTIFY propertyChanged)
    Q_PROPERTY(bool chronicPainInMotion READ chronicPainInMotion NOTIFY propertyChanged)
    Q_PROPERTY(int chronicPainInMotionDegree READ chronicPainInMotionDegree NOTIFY propertyChanged)
    Q_PROPERTY(bool images READ images NOTIFY propertyChanged)
    Q_PROPERTY(QStringList imageSources READ imageSources NOTIFY propertyChanged)
    Q_PROPERTY(QStringList imageDescriptions READ imageDescriptions NOTIFY propertyChanged)


public:
    explicit HerniaInfo(const QString& herniaType, const QString& herniaSide, bool recurrence,
                        QObject *parent = nullptr);

    void setVentralHerniaInfo(const QString& ventralHerniaType, const QString& ventralHerniaSubtype, const QString& ventralHerniaWidth,
                              int ventralHerniaLength);
    void setGroinHerniaInfo(const QString& groinHerniaType, const QString& groinHerniaExamination);
    void setDiagnosticsInfo(const QList<int>& clinicalExamination, const QList<int>& uziDorsal, const QList<int>& uziStanding,
                        const QList<int>& kt, const QList<int>& mrt);
    void setPreoperativePainInRestInfo(int degree);
    void setPreoperativePainInMotionInfo(int degree);
    void setOperationInfo(const QString& operationSide, int ringWidth, int sacWidth, int sacLength,
                          const QString& method, const QString& tecnique,
                          bool nerveInjury);
    void setNonTensionOperationInfo(const QString& mesh, int meshWidth, int meshLength, const QString& fixationType, const QString& tuckers,
                                    const QString& peritoneumClosure, bool drainage);
    void setIntraoperativeComplicationsInfo(bool hemorrhage, bool nerveDamage, bool cordInjury, bool bowelInjury);
    void setEarlyPostoperativeComplicationsInfo(bool woundInfection, bool seroma, const QString& seromaSize,
                                                bool hematoma, bool cordSwelling, bool orchiepididymitis);
    void setLatePostoperativeComplicationsInfo(bool fistulas, bool meshRejection, bool chronicNeuralgia,
                                           bool testicularAtrophy, bool diseaseRecurrence);

    void setEarlyPainInfo(const QList<bool>& inRest, const QList<int>& inRestDegree,
                      const QList<bool>& inMotion, const QList<int>& inMotionDegree,
                      const QList<bool>& analgesics,
                      const QList<int>& analgesicsDays,
                      const QList<bool>& analgesicsOrally,
                      const QList<int>& orallyDays,
                      const QList<bool>& analgesicsInjections,
                      const QList<int>& injectionsDays);

    void setChronicInRestPainInfo(int degree);
    void setChronicInMotionPainInfo(int degree);

    void setImages(const QStringList& sources, const QStringList& descriptions);




    const QString& herniaType() const;
    const QString& ventralHerniaType() const;
    const QString& ventralHerniaSubtype() const;
    const QString& ventralHerniaWidth() const;
    int ventralHerniaLength() const;
    const QString& groinHerniaType() const;
    const QString& groinHerniaExamination() const;
    const QString& herniaSide() const;
    bool recurrence() const;

    bool diagnostics() const;
    const QList<int>& clinicalExamination() const;
    const QList<int>& uziDorsal() const;
    const QList<int>& uziStanding() const;
    const QList<int>& kt() const;
    const QList<int>& mrt() const;
    bool preoperativePainInRest() const;
    int preoperativePainInRestDegree() const;
    bool preoperativePainInMotion() const;
    int preoperativePainInMotionDegree() const;
    bool operation() const;
    const QString& operationSide() const;
    int ringWidth() const;
    int sacWidth() const;
    int sacLength() const;
    const QString& operationMethod() const;
    const QString& operationTechnique() const;
    const QString& mesh() const;
    int meshWidth() const;
    int meshLength() const;
    const QString& fixationType() const;
    const QString& tuckers() const;
    const QString& peritoneumClosure() const;
    bool drainage() const;
    bool intraoperativeComplications() const;
    bool hemorrhage() const;
    bool nerveDamage() const;
    bool cordInjury() const;
    bool bowelInjury() const;
    bool earlyPostoperativeComplications() const;
    bool woundInfection() const;
    bool seroma() const;
    const QString& seromaSize() const;
    bool hematoma() const;
    bool cordSwelling() const;
    bool orchiepididymitis() const;
    bool latePostoperativeComplications() const;
    bool fistulas() const;
    bool meshRejection() const;
    bool chronicNeuralgia() const;
    bool testicularAtrophy() const;
    bool diseaseRecurrence() const;

    bool earlyPain() const;
    const QList<bool>& earlyInRestPain() const;
    const QList<int>& earlyInRestPainDegree() const;

    const QList<bool>& earlyInMotionPain() const;
    const QList<int>& earlyInMotionPainDegree() const;

    const QList<bool>& earlyPainAnalgesics() const;
    const QList<int>& earlyPainAnalgesicsDays() const;
    const QList<bool>& earlyPainAnalgesicsOrally() const;
    const QList<int>& earlyPainAnalgesicsInjectionsDays() const;
    const QList<bool>& earlyPainAnalgesicsInjections() const;
    const QList<int>& earlyPainAnalgesicsOrallyDays() const;


    bool nerveInjury() const;

    bool chronicPainInRest() const;
    int chronicPainInRestDegree() const;

    bool chronicPainInMotion() const;
    int chronicPainInMotionDegree() const;

    bool images() const;
    const QStringList& imageSources() const;
    const QStringList& imageDescriptions() const;

private:
    QString m_herniaType;

    QString m_ventralHerniaType;
    QString m_ventralHerniaSubtype;
    QString m_ventralHerniaWidth;
    int m_ventralHerniaLength;

    QString m_groinHerniaType;
    QString m_groinHerniaExamination;

    QString m_herniaSide;
    bool m_recurrence;

    bool m_diagnostics = false;
    QList<int> m_clinicalExamination;
    QList<int> m_uziDorsal;
    QList<int> m_uziStanding;
    QList<int> m_kt;
    QList<int> m_mrt;

    bool m_preoperativePainInRest = false;
    int m_preoperativePainInRestDegree;

    bool m_preoperativePainInMotion = false;
    int m_preoperativePainInMotionDegree;

    bool m_operation = false;
    QString m_operationSide;
    int m_ringWidth;
    int m_sacWidth;
    int m_sacLength;

    QString m_operationMethod;
    QString m_operationTechnique;

    QString m_mesh;
    int m_meshWidth;
    int m_meshLength;

    QString m_fixationType;
    QString m_tuckers;
    QString m_peritoneumClosure;
    bool m_drainage;

    bool m_intraoperativeComplications = false;
    bool m_hemorrhage;
    bool m_nerveDamage;
    bool m_cordInjury;
    bool m_bowelInjury;

    bool m_earlyPostoperativeComplications = false;
    bool m_woundInfection;
    bool m_seroma;
    QString m_seromaSize;
    bool m_hematoma;
    bool m_cordSwelling;
    bool m_orchiepididymitis;

    bool m_latePostoperativeComplications = false;
    bool m_fistulas;
    bool m_meshRejection;
    bool m_chronicNeuralgia;
    bool m_testicularAtrophy;
    bool m_diseaseRecurrence;

    bool m_earlyPain = false;
    // списки состоят из 3 элементов - 1, 3, и 7 сутки

    QList<bool> m_earlyInRestPain;
    QList<int> m_earlyInRestPainDegree;

    QList<bool> m_earlyInMotionPain;
    QList<int> m_earlyInMotionPainDegree;

    QList<bool> m_earlyPainAnalgesics;
    QList<int> m_earlyPainAnalgesicsDays;
    QList<bool> m_earlyPainAnalgesicsOrally;
    QList<int> m_earlyPainAnalgesicsInjectionsDays;
    QList<bool> m_earlyPainAnalgesicsInjections;
    QList<int> m_earlyPainAnalgesicsOrallyDays;


    bool m_nerveInjury;

    bool m_chronicPainInRest = false;
    int m_chronicPainInRestDegree;

    bool m_chronicPainInMotion = false;
    int m_chronicPainInMotionDegree;

    bool m_images = false;
    QStringList m_imageSources;
    QStringList m_imageDescriptions;



signals:
    void propertyChanged();

public slots:
};



#endif // HERNIAINFO_H
