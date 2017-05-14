#ifndef HIERARCHICAL_CLUSTERING_ELEMENTS_H
#define HIERARCHICAL_CLUSTERING_ELEMENTS_H

#include <QList>
#include <QSharedPointer>
#include <QDebug>

// Classes in this unit is applied as internal structures and output of hierarchical clustering procedure.

namespace HierarchicalClusteringElements
{
    class Cluster;
    class Linkage;

    // The class "Cluster" describes the element of hierarchical clustering procedure.
    // It stores the index of itself in some elements array (created in process of clustering),
    // and indexes of all objects which are consisted in this cluster.
    class Cluster {
        public:
            Cluster(int index) : _index(index) {}
            ~Cluster()                          = default;
            Cluster(const Cluster&)             = default;
            Cluster& operator =(const Cluster&) = default;
            Cluster(Cluster&&)                  = default;
            Cluster& operator =(Cluster&&)      = default;
            friend void moveChildIndexes(Cluster &clusterFrom, Cluster &clusterTo);
            friend bool operator <(const QSharedPointer<Cluster> &c1, const QSharedPointer<Cluster> &c2);
            bool isEmpty() const {return _childIndexes.isEmpty();}
            int nChildIndexes() const {return _childIndexes.size();}
            int childIndex(int i) const {return _childIndexes.at(i);}
            void addChildIndex(int childIndex) {_childIndexes.append(childIndex);}
            int index() const {return _index;}
        private:
            QList<int> _childIndexes;       //index of children (elements inside the cluster)
            int _index;                     //own index (index of this cluster in some array)
    };

    // The class "Linkage" represents the fact of similarity between two clusters during the clustering procedure.
    // The object of this class stores indexes of similar clusters in the array of this elements,
    // and the correlation between these two elements
    class Linkage {
    public:
        Linkage(int index1, int index2, float correlation) : _index1(index1), _index2(index2), _correlation(correlation) {}
        ~Linkage()                          = default;
        Linkage(const Linkage&)             = default;
        Linkage& operator =(const Linkage&) = default;
        Linkage(Linkage&&)                  = default;
        Linkage& operator =(Linkage&&)      = default;
        friend bool operator< (const QSharedPointer<Linkage> &l1, const QSharedPointer<Linkage> &l2);
        int index1() const {return _index1;}
        int index2() const {return _index2;}
        float correlation() const {return _correlation;}
    private:
        int _index1;
        int _index2;
        float _correlation;
    };
}

#endif // HIERARCHICAL_CLUSTERING_ELEMENTS_H
