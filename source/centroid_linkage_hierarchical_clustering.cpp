#include "centroid_linkage_hierarchical_clustering.h"

using namespace HierarchicalClusteringElements;

QList<QSharedPointer<Cluster> > centroidLinkageHierarchicalClustering(QList<QSharedPointer<QVector<float> > > &valuesMatrix, double threshold)
{
    // In the beginning of procedure, the list of clusters is empty:
    QList<QSharedPointer<Cluster> > clusters;

    // valuesMatrix has m examples and n features (check that all rows are of equal length):
    int m = valuesMatrix.size();
    int n;
    if (m > 0) {
        n = valuesMatrix.first()->size();
        for (auto row : valuesMatrix) {
            Q_ASSERT(row->size() == n);
        }
    }

    // Preparing clusters list (at this stage each cluster will consist of only one signature)
    // and linkages list (sorted list of similarities between rows of valueMatrix, which is above the threshold)
    for (int i = 0; i < m; ++i) {
        auto cluster = QSharedPointer<Cluster>::create(i);
        cluster->addChildIndex(i);
        clusters.append(cluster);
    }

    // Variables that will allow us to accelerate clustering,
    // because we will not need to calculate them multiple times:
    QList<float> sums, squareSums;
    for (int i = 0; i < m; ++i) {
        float sum, squareSum;
        calculateSumAndSquareSum(sum, squareSum, *valuesMatrix.at(i));
        sums.append(sum);
        squareSums.append(squareSum);
    }

    // We use priority queue of linkages (similarities between all pairs of elements with correlation above the threshold).
    // Since there is no priority queue in QT, we use STL container:
    std::priority_queue<QSharedPointer<Linkage> > linkageQueue;

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            float r = computeCorrelation(*valuesMatrix.at(i), *valuesMatrix.at(j), sums.at(i), sums.at(j), squareSums.at(i), squareSums.at(j));
            if (r >= threshold) {
                linkageQueue.emplace(QSharedPointer<Linkage>::create(i, j, r));
            }
        }
    }

    // Now, when clusters list and linkages list are prepared, we are ready to start agglomerative clustering.
    // The cycle is: Take the two most similar elements -> clusterize them -> calculate new similarities for newly created cluster.
    // The cycle ends when there are no more pairs of elements with correlation above the threshold.
    while (!linkageQueue.empty()) {
        Linkage &linkage = *linkageQueue.top(); // linkages.first();
        int index1 = linkage.index1();
        int index2 = linkage.index2();
        Cluster &cluster1 = *clusters.at(index1);
        Cluster &cluster2 = *clusters.at(index2);

        // Since we know index1 and index2, there is no need in first linkage.
        linkageQueue.pop();

        // If at least one of clusters connected by this linkage is already empty (absorbed by another cluster), do nothing.
        if (cluster1.isEmpty() || cluster2.isEmpty()) {
            continue;
        }

        int nReplicates1 = cluster1.nChildIndexes();
        int nReplicates2 = cluster2.nChildIndexes();
        int nReplicates = nReplicates1 + nReplicates2;

        // Unite two clusters, average the values with weights (massive cluster will give more influence)
        auto newValues = QSharedPointer<QVector<float> >::create();
        for (int i = 0; i < n; ++i) {
            newValues->append((valuesMatrix.at(index1)->at(i) * nReplicates1 + valuesMatrix.at(index2)->at(i) * nReplicates2) / nReplicates);
        }
        valuesMatrix.append(newValues);

        // Calculate sum and squareSum for new cluster
        float sum, squareSum;
        calculateSumAndSquareSum(sum, squareSum, *newValues);
        sums.append(sum);
        squareSums.append(squareSum);

        // Create new cluster, which "absorbes" the old ones, so they are empty after that.
        auto newCluster = QSharedPointer<Cluster>::create(clusters.size());
        moveChildIndexes(cluster1, *newCluster);
        moveChildIndexes(cluster2, *newCluster);
        clusters.append(newCluster);

        // Free memory from values of absorbed clusters; there is no need to store them any longer.
        if (index1 >= m) {
            valuesMatrix.at(index1)->clear();
        }
        if (index2 >= m) {
            valuesMatrix.at(index2)->clear();
        }

        // Calculate distance between this new cluster and old (non-empty, i.e. not absorbed) ones;
        // Create new linkages and paste them into linkages list in such way so the list will remain sorted decreasingly.
        int nClusters = clusters.size();
        Q_ASSERT(valuesMatrix.size() == nClusters);
        Q_ASSERT(sums.size() == nClusters);
        Q_ASSERT(squareSums.size() == nClusters);
        for (int i = 0; i < nClusters - 1; ++i) {
            if (!clusters.at(i)->isEmpty()) {
                float r = computeCorrelation(*valuesMatrix.at(nClusters - 1), *valuesMatrix.at(i), sums.at(nClusters - 1), sums.at(i),
                                         squareSums.at(nClusters - 1), squareSums.at(i));
                if (r >= threshold) {
                    linkageQueue.emplace(QSharedPointer<Linkage>::create(i, nClusters - 1, r));
                }
            }
        }        
    }

    return clusters;
}
