#include "signature.h"

QSharedPointer<Signature> Signature::child(int) const
{
    // Should not be called.
    Q_ASSERT(false);
    return QSharedPointer<Signature>();
}

Signature operator+ (const Signature &signature1, const Signature &signature2)
{
    int n = signature1.size();
    if (signature2.size() != n) {
        throw QString("Summarizing of signatures of unequal size");
    }

    Signature sumSignature(n);

    // If compounds are the same, the sum will belong to the same compound
    if (signature1.compound() == signature2.compound()) {
        sumSignature.setCompound(signature1.compound());
    }

    // If concentrations are equal, the sum will have the same concentration
    if (signature1.concentration() == signature2.concentration()) {
        sumSignature.setConcentration(signature1.concentration());
    }

    for (int i = 0; i < n; ++i) {
        sumSignature.setActivity(i, signature1.activity(i) + signature2.activity(i));
    }

    return sumSignature;
}

Signature& Signature::operator /(int n)
{
    if (n == 0) {
        throw QString("Signature is divided by zero");
    }
    for (int i = 0; i < _activities->size(); ++i) {
        this->setActivity(i, this->activity(i) / n);
    }
    return *this;
}
