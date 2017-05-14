#ifndef CLUSTERIZE_SIGNATURES_H
#define CLUSTERIZE_SIGNATURES_H

#include "centroid_linkage_hierarchical_clustering.h"
#include "signature_cluster.h"

void clusterizeSignatures(QList<QSharedPointer<Signature> > &signatures, QList<QSharedPointer<SignatureCluster> > &signatureClusters, double correlationThreshold);

#endif // CLUSTERIZE_SIGNATURES_H
