#ifndef CENTROID_LINKAGE_HIERARCHICAL_CLUSTERING_H
#define CENTROID_LINKAGE_HIERARCHICAL_CLUSTERING_H

#include <QSharedPointer>
#include <QVector>
#include <queue>

#include "hierarchical_clustering_elements.h"
#include "compute_correlation.h"

using namespace HierarchicalClusteringElements;

QList<QSharedPointer<Cluster> > centroidLinkageHierarchicalClustering(QList<QSharedPointer<QVector<float> > > &valueMatrix, double threshold);

#endif // CENTROID_LINKAGE_HIERARCHICAL_CLUSTERING_H
