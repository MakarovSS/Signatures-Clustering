#include "signature_cluster.h"

void SignatureCluster::addChild(const QSharedPointer<Signature> signature) {
    _children.append(QWeakPointer<Signature>(signature));
}

bool operator <(const QSharedPointer<SignatureCluster> &c1, const QSharedPointer<SignatureCluster> &c2) {
    return (c1->childCount() < c2->childCount());
}
