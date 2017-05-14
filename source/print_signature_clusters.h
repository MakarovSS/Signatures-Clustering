#ifndef PRINT_SIGNATURE_CLUSTERS_H
#define PRINT_SIGNATURE_CLUSTERS_H

#include <QList>
#include <string>
#include <iostream>

#include "signature_cluster.h"

void printSignature(const QSharedPointer<Signature> signature, int shift);
void printSignatureClusters(const QList<QSharedPointer<SignatureCluster> > signatureClusters);

#endif // PRINT_SIGNATURE_CLUSTERS_H
