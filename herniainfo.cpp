#include "herniainfo.h"

HerniaInfo::HerniaInfo(const QString &herniaType, const QString &herniaSide, bool recurrence, QObject *parent) :
    QObject(parent), m_herniaType(herniaType), m_herniaSide(herniaSide), m_recurrence(recurrence)
{

}

void HerniaInfo::setVentralHerniaInfo(const QString &ventralHerniaType,
                                      const QString &ventralHerniaSubtype,
                                      const QString &ventralHerniaWidth,
                                      int ventralHerniaLength)
{
    this->m_ventralHerniaType = ventralHerniaType;
    this->m_ventralHerniaSubtype = ventralHerniaSubtype;
    this->m_ventralHerniaWidth = ventralHerniaWidth;
    this->m_ventralHerniaLength = ventralHerniaLength;
}

void HerniaInfo::setGroinHerniaInfo(const QString &groinHerniaType, const QString &groinHerniaExamination)
{
    this->m_groinHerniaType = groinHerniaType;
    this->m_groinHerniaExamination = groinHerniaExamination;
}

void HerniaInfo::setDiagnosticsInfo(const QList<int> &clinicalExamination,
                                    const QList<int> &uziDorsal, const QList<int> &uziStanding,
                                    const QList<int> &kt, const QList<int> &mrt)
{
    if(!clinicalExamination.isEmpty() || !uziDorsal.isEmpty() || !uziStanding.isEmpty() || !kt.isEmpty() || !mrt.isEmpty())
        this->m_diagnostics = true;
    this->m_clinicalExamination = clinicalExamination;
    this->m_uziDorsal = uziDorsal;
    this->m_uziStanding = uziStanding;
    this->m_kt = kt;
    this->m_mrt = mrt;
}

void HerniaInfo::setPreoperativePainInRestInfo(int degree)
{
    this->m_preoperativePainInRest = true;
    this->m_preoperativePainInRestDegree = degree;
}

void HerniaInfo::setPreoperativePainInMotionInfo(int degree)
{
    this->m_preoperativePainInMotion = true;
    this->m_preoperativePainInMotionDegree = degree;
}

void HerniaInfo::setOperationInfo(const QString &operationSide, int ringWidth, int sacWidth, int sacLength,
                                  const QString &method, const QString &tecnique, bool nerveInjury)
{
    this->m_operation = true;
    this->m_operationSide = operationSide;
    this->m_ringWidth = ringWidth;
    this->m_sacWidth = sacWidth;
    this->m_sacLength = sacLength;
    this->m_operationMethod = method;
    this->m_operationTechnique = tecnique;
    this->m_nerveInjury = nerveInjury;
}

void HerniaInfo::setNonTensionOperationInfo(const QString &mesh, int meshWidth, int meshLength, const QString &fixationType,
                                            const QString &tuckers, const QString &peritoneumClosure, bool drainage)
{
    this->m_mesh = mesh;
    this->m_meshWidth = meshWidth;
    this->m_meshLength = meshLength;
    this->m_fixationType = fixationType;
    this->m_tuckers = tuckers;
    this->m_peritoneumClosure = peritoneumClosure;
    this->m_drainage = drainage;
}

void HerniaInfo::setIntraoperativeComplicationsInfo(bool hemorrhage, bool nerveDamage, bool cordInjury, bool bowelInjury)
{
    this->m_intraoperativeComplications = true;
    this->m_hemorrhage = hemorrhage;
    this->m_nerveDamage = nerveDamage;
    this->m_cordInjury = cordInjury;
    this->m_bowelInjury = bowelInjury;
}

void HerniaInfo::setEarlyPostoperativeComplicationsInfo(bool woundInfection, bool seroma, const QString &seromaSize,
                                                        bool hematoma, bool cordSwelling, bool orchiepididymitis)
{
    this->m_earlyPostoperativeComplications = true;
    this->m_woundInfection = woundInfection;
    this->m_seroma = seroma;
    this->m_seromaSize = seromaSize;
    this->m_hematoma = hematoma;
    this->m_cordSwelling = cordSwelling;
    this->m_orchiepididymitis = orchiepididymitis;
}

void HerniaInfo::setLatePostoperativeComplicationsInfo(bool fistulas, bool meshRejection, bool chronicNeuralgia,
                                                       bool testicularAtrophy, bool diseaseRecurrence)
{
    this->m_latePostoperativeComplications = true;
    this->m_fistulas = fistulas;
    this->m_meshRejection = meshRejection;
    this->m_chronicNeuralgia = chronicNeuralgia;
    this->m_testicularAtrophy = testicularAtrophy;
    this->m_diseaseRecurrence = diseaseRecurrence;
}

void HerniaInfo::setEarlyPainInfo(const QList<bool> &inRest, const QList<int> &inRestDegree,
                                  const QList<bool> &inMotion, const QList<int> &inMotionDegree,
                                  const QList<bool> &analgesics, const QList<int> &analgesicsDays,
                                  const QList<bool> &analgesicsOrally, const QList<bool> &analgesicsInjections)
{
    this->m_earlyPain = true;
    this->m_earlyInRestPain = inRest;
    this->m_earlyInRestPainDegree = inRestDegree;
    this->m_earlyInMotionPain = inMotion;
    this->m_earlyInMotionPainDegree = inMotionDegree;
    this->m_earlyPainAnalgesics = analgesics;
    this->m_earlyPainAnalgesicsDays = analgesicsDays;
    this->m_earlyPainAnalgesicsOrally = analgesicsOrally;
    this->m_earlyPainAnalgesicsInjections = analgesicsInjections;
}

void HerniaInfo::setChronicInRestPainInfo(int degree)
{
    this->m_chronicPainInRest = true;
    this->m_chronicPainInRestDegree = degree;
}

void HerniaInfo::setChronicInMotionPainInfo(int degree)
{
    this->m_chronicPainInMotion = true;
    this->m_chronicPainInMotionDegree = degree;
}

void HerniaInfo::setImages(const QStringList &sources, const QStringList &descriptions)
{
    this->m_images = true;
    this->m_imageSources = sources;
    this->m_imageDescriptions = descriptions;
}


const QString& HerniaInfo::herniaType() const
{
    return this->m_herniaType;
}

const QString& HerniaInfo::ventralHerniaType() const
{
    return this->m_ventralHerniaType;
}

const QString& HerniaInfo::ventralHerniaSubtype() const
{
    return this->m_ventralHerniaSubtype;
}

const QString& HerniaInfo::ventralHerniaWidth() const
{
    return this->m_ventralHerniaWidth;
}

int HerniaInfo::ventralHerniaLength() const
{
    return this->m_ventralHerniaLength;
}

const QString& HerniaInfo::groinHerniaType() const
{
    return this->m_groinHerniaType;
}

const QString& HerniaInfo::groinHerniaExamination() const
{
    return this->m_groinHerniaExamination;
}

const QString& HerniaInfo::herniaSide() const
{
    return this->m_herniaSide;
}

bool HerniaInfo::recurrence() const
{
    return this->m_recurrence;
}

bool HerniaInfo::diagnostics() const
{
    return this->m_diagnostics;
}

const QList<int>& HerniaInfo::clinicalExamination() const
{
    return this->m_clinicalExamination;
}

const QList<int>& HerniaInfo::uziDorsal() const
{
    return this->m_uziDorsal;
}

const QList<int>& HerniaInfo::uziStanding() const
{
    return this->m_uziStanding;
}

const QList<int>& HerniaInfo::kt() const
{
    return this->m_kt;
}

const QList<int>& HerniaInfo::mrt() const
{
    return this->m_mrt;
}

bool HerniaInfo::preoperativePainInRest() const
{
    return this->m_preoperativePainInRest;
}

int HerniaInfo::preoperativePainInRestDegree() const
{
    return this->m_preoperativePainInRestDegree;
}

bool HerniaInfo::preoperativePainInMotion() const
{
    return this->m_preoperativePainInMotion;
}

int HerniaInfo::preoperativePainInMotionDegree() const
{
    return this->m_preoperativePainInMotionDegree;
}

bool HerniaInfo::operation() const
{
    return this->m_operation;
}

const QString &HerniaInfo::operationSide() const
{
    return this->m_operationSide;
}

int HerniaInfo::ringWidth() const
{
    return this->m_ringWidth;
}

int HerniaInfo::sacWidth() const
{
    return this->m_sacWidth;
}

int HerniaInfo::sacLength() const
{
    return this->m_sacLength;
}

const QString& HerniaInfo::operationMethod() const
{
    return this->m_operationMethod;
}

const QString& HerniaInfo::operationTechnique() const
{
    return this->m_operationTechnique;
}

const QString& HerniaInfo::mesh() const
{
    return this->m_mesh;
}

int HerniaInfo::meshWidth() const
{
    return this->m_meshWidth;
}

int HerniaInfo::meshLength() const
{
    return this->m_meshLength;
}


const QString& HerniaInfo::fixationType() const
{
    return this->m_fixationType;
}

const QString& HerniaInfo::tuckers() const
{
    return this->m_tuckers;
}

const QString& HerniaInfo::peritoneumClosure() const
{
    return this->m_peritoneumClosure;
}

bool HerniaInfo::drainage() const
{
    return this->m_drainage;
}

bool HerniaInfo::intraoperativeComplications() const
{
    return this->m_intraoperativeComplications;
}

bool HerniaInfo::hemorrhage() const
{
    return this->m_hemorrhage;
}

bool HerniaInfo::nerveDamage() const
{
    return this->m_nerveDamage;
}

bool HerniaInfo::cordInjury() const
{
    return this->m_cordInjury;
}

bool HerniaInfo::bowelInjury() const
{
    return this->m_bowelInjury;
}


bool HerniaInfo::earlyPostoperativeComplications() const
{
    return this->m_earlyPostoperativeComplications;
}

bool HerniaInfo::woundInfection() const
{
    return this->m_woundInfection;
}

bool HerniaInfo::seroma() const
{
    return this->m_seroma;
}

const QString& HerniaInfo::seromaSize() const
{
    return this->m_seromaSize;
}

bool HerniaInfo::hematoma() const
{
    return this->m_hematoma;
}

bool HerniaInfo::cordSwelling() const
{
    return this->m_cordSwelling;
}

bool HerniaInfo::orchiepididymitis() const
{
    return this->m_orchiepididymitis;
}

bool HerniaInfo::latePostoperativeComplications() const
{
    return this->m_latePostoperativeComplications;
}

bool HerniaInfo::fistulas() const
{
    return this->m_fistulas;
}

bool HerniaInfo::meshRejection() const
{
    return this->m_meshRejection;
}

bool HerniaInfo::chronicNeuralgia() const
{
    return this->m_chronicNeuralgia;
}

bool HerniaInfo::testicularAtrophy() const
{
    return this->m_testicularAtrophy;
}

bool HerniaInfo::diseaseRecurrence() const
{
    return this->m_diseaseRecurrence;
}

bool HerniaInfo::earlyPain() const
{
    return this->m_earlyPain;
}

const QList<bool>& HerniaInfo::earlyInRestPain() const
{
    return this->m_earlyInRestPain;
}

const QList<int>& HerniaInfo::earlyInRestPainDegree() const
{
    return this->m_earlyInRestPainDegree;
}


const QList<bool>& HerniaInfo::earlyInMotionPain() const
{
    return this->m_earlyInMotionPain;
}

const QList<int>& HerniaInfo::earlyInMotionPainDegree() const
{
    return this->m_earlyInMotionPainDegree;
}

const QList<bool>& HerniaInfo::earlyPainAnalgesics() const
{
    return this->m_earlyPainAnalgesics;
}

const QList<int>& HerniaInfo::earlyPainAnalgesicsDays() const
{
    return this->m_earlyPainAnalgesicsDays;
}

const QList<bool>& HerniaInfo::earlyPainAnalgesicsOrally() const
{
    return this->m_earlyPainAnalgesicsOrally;
}

const QList<bool>& HerniaInfo::earlyPainAnalgesicsInjections() const
{
    return this->m_earlyPainAnalgesicsInjections;
}



bool HerniaInfo::nerveInjury() const
{
    return this->m_nerveInjury;
}

bool HerniaInfo::chronicPainInRest() const
{
    return this->m_chronicPainInRest;
}

int HerniaInfo::chronicPainInRestDegree() const
{
    return this->m_chronicPainInRestDegree;
}


bool HerniaInfo::chronicPainInMotion() const
{
    return this->m_chronicPainInMotion;
}

int HerniaInfo::chronicPainInMotionDegree() const
{
    return this->m_chronicPainInMotionDegree;
}

bool HerniaInfo::images() const
{
    return this->m_images;
}

const QStringList &HerniaInfo::imageSources() const
{
    return this->m_imageSources;
}

const QStringList &HerniaInfo::imageDescriptions() const
{
    return this->m_imageDescriptions;
}
