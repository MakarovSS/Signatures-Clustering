#include "hierarchical_clustering_elements.h"

namespace HierarchicalClusteringElements {
    //all elements of cluster are transfered to another cluster; clusterFrom is empty after that
    void moveChildIndexes(Cluster &clusterFrom, Cluster &clusterTo)
    {
        clusterTo._childIndexes.append(clusterFrom._childIndexes);
        clusterFrom._childIndexes.clear();
    }

    //comparison of linkages (by correlation value)
    bool operator <(const QSharedPointer<Linkage> &l1, const QSharedPointer<Linkage> &l2)
    {
        return (l1->_correlation < l2->_correlation);
    }

    //comparison of clusters (by children count)
    bool operator <(const QSharedPointer<Cluster> &c1, const QSharedPointer<Cluster> &c2)
    {
        return (c1->nChildIndexes() < c2->nChildIndexes());
    }
}
