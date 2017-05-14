#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QVector>
#include <QWeakPointer>

class Signature;
class SignatureCluster;                         // will be inherited from Signature

class Signature
{
public:
    Signature(int size) {resize(size);}         // when creating signatures, the number of features must be specified
    virtual ~Signature()                   = default;
    Signature(const Signature&)            = default;
    Signature& operator=(const Signature&) = default;
    Signature(Signature&&)                 = default;
    Signature& operator=(Signature&&)      = default;
    friend Signature operator+ (const Signature &signature1, const Signature &signature2);
    Signature& operator/ (int n);

    // Virtual functions which has mainly sense for signatureCluster, but can be defined for Signature too
    virtual float correlation() const {return 1.0;}
    virtual int childCount() const {return 0;}
    virtual QSharedPointer<Signature> child(int) const;

    int size() const {return _activities->size();}
    void resize(int size) {_activities->resize(size);}
    int number() const {return _number;}
    void setNumber(int number) {_number = number;}
    float activity(int index) const {return _activities->at(index);}
    void setActivity(int index, float value) {_activities->replace(index, value);}
    QSharedPointer<QVector<float> > activities() {return _activities;}
    QString compound() const {return _compound;}
    void setCompound(QString compound) {_compound = compound;}
    float concentration() const {return _concentration;}
    void setConcentration(float concentration) {_concentration = concentration;}
    QSharedPointer<SignatureCluster> parent() const {return _parent.toStrongRef();}
    void setParent(const QSharedPointer<SignatureCluster> parent) {_parent = QWeakPointer<SignatureCluster>(parent);}

private:   
    // Vector of activities. The size typically doesn't change after construction, so QVector is used.
    QSharedPointer<QVector<float> > _activities = QSharedPointer<QVector<float> >::create();
    int _number = 0;                               // Number (id for storing in database)
    QString _compound;                             // Compound for which we had an experiment
    float _concentration = 0;                      // Concentration of given compound
    QWeakPointer<SignatureCluster> _parent;        // Parent in cluster tree
};

#endif // SIGNATURE_H
