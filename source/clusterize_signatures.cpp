#include "clusterize_signatures.h"

void clusterizeSignatures(QList<QSharedPointer<Signature> > &signatures, QList<QSharedPointer<SignatureCluster> > &signatureClusters, double correlationThreshold)
{
    // Simplify list of signatures to matrix of float values to run clustering procedure.
    // (Clustering is developed for more common cases, so all attributes of Signature class must be excluded)
    QList<QSharedPointer<QVector<float> > > valuesMatrix;
    int nSignatures = signatures.size();

    if (nSignatures <= 0) {
        return;
    }

    int nActivities = signatures.first()->size();
    for (int i = 0; i < nSignatures; ++i) {
        Q_ASSERT(signatures.at(i)->size() == nActivities);
        QSharedPointer<QVector<float> > activities(signatures.at(i)->activities());
        valuesMatrix.append(activities);
    }

    // Running centroid-linkage hierarchical clustering procedure.
    auto clusters = centroidLinkageHierarchicalClustering(valuesMatrix, correlationThreshold);

    // Transform given clusters to signatureClusters.
    // (From more simple output of clustering procedure to more specific class SignatureCluster)
    int currentClusterNumber = 1;
    for (int i = 0; i < clusters.size(); ++i) {
        if (!clusters.at(i)->isEmpty() > 0) {
            auto newSignatureCluster = QSharedPointer<SignatureCluster>::create(nActivities);
            for (int j = 0; j < nActivities; ++j) {     //func (copy activities)
                newSignatureCluster->setActivity(j, valuesMatrix.at(i)->at(j));
            }
            for (int j = 0; j < clusters.at(i)->nChildIndexes(); ++j) {
                int index = clusters.at(i)->childIndex(j);
                Q_ASSERT(index < signatures.size());
                newSignatureCluster->addChild(QSharedPointer<Signature>(signatures.at(index)));
                signatures[index]->setParent(newSignatureCluster);
            }
            newSignatureCluster->setNumber(currentClusterNumber++);
            newSignatureCluster->setCorrelation(correlationThreshold);
            signatureClusters.append(newSignatureCluster);
        }
    }

    // Sort signatureClusters by size (children count)
    qStableSort(signatureClusters);
}
