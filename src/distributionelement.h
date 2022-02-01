#ifndef DISTRIBUTIONELEMENT_H
#define DISTRIBUTIONELEMENT_H

#include <QObject>

class DistributionElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(float percent READ percent NOTIFY percentChanged)
public:
    explicit DistributionElement(const QString& label, int count,
                                 int percent, QObject *parent = nullptr);

    const QString& label() const;
    int count() const;
    float percent() const;

    friend bool operator <(const DistributionElement& de1, const DistributionElement& de2);

private:
    QString m_label;
    int m_count;
    float m_percent;

signals:
    void labelChanged();
    void countChanged();
    void percentChanged();

public slots:
};

#endif // DISTRIBUTIONELEMENT_H
