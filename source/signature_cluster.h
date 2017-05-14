#ifndef SIGNATURE_CLUSTER_H
#define SIGNATURE_CLUSTER_H

#include "signature.h"

// Cluster of signatures, which has all signature features itself.
// The object of this class is a result of averaging all consisting signatures AND information about them, given as parent-child relationship

class SignatureCluster : public Signature
{
public:
    SignatureCluster(int size) : Signature(size) {}
    virtual ~SignatureCluster()                          = default;
    SignatureCluster(const SignatureCluster&)            = default;
    SignatureCluster& operator=(const SignatureCluster&) = default;
    SignatureCluster(SignatureCluster&&)                 = default;
    SignatureCluster& operator=(SignatureCluster&&)      = default;

    //Inherited from Signature
    virtual float correlation() const override {return _correlation;}
    virtual int childCount() const override {return _children.size();}
    virtual QSharedPointer<Signature> child(int i) const override {return _children[i].toStrongRef();}

    //New functions
    void addChild(const QSharedPointer<Signature> signature);
    void clearChildren() {_children.clear();}
    void setCorrelation(float correlation) {_correlation = correlation;}
    friend bool operator <(const QSharedPointer<SignatureCluster> &c1, const QSharedPointer<SignatureCluster> &c2);

private:
    float _correlation;
    QList<QWeakPointer<Signature> > _children;             //child can be Signature or SignatureCluster
};

#endif // SIGNATURE_CLUSTER_H
