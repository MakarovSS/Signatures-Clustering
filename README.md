FILES DESCRIPTION
* main.cpp
Calls the main function, which consequently calls:
- reading SQLite database and creation of signatures list from obtained data;
- clustering the signature list by agglomerative hierarchical clustering with centroid linkage;
- printing the results of clustering on console.

* centroid_linkage_hierarchical_clustering.h
Performs the agglomerative hierarchical clustering with centroid linkage. 
The input of the procedure is matrix of float numbers (it can be signatures activities, or something else - the procedure is common and doesn't require Signature syntax).
The output is:
- list of clusters. Each clusters contains the indexes of elements within the cluster.
- extended matrix of float numbers, which allows to describe activities of each cluster.

* clusterize_signatures.h
A link between main.cpp and centroid_linkage_hierarchical_clustering: transforms list of signatures in more common form as matrix of floats, runs clustering, interpretate results as clusters of signatures.

* compute_correlation.h
Contains a function calculating Pearson's correlation coefficient.

* hierarchical_clustering_elements.h
Describes a namespace HierarchicalClusteringElements, which contains two classes - Cluster and Linkage - which is used in the process of clustering, and as output of this process, and supposingly nowhere else in the program.

* print_signature_clusters.h
Prints signature's cluster tree. In this limited version, tree has exactly two layers.

* read_signatures_from_sqlite.h
Opens SQLite database, reads the information, transform it to the form of signature's list.

* read_query_values.h
Template function queryToVariable, which needed to generalize query.value().toInt(), ...toString(), ...toFloat(). We need to throw an exception when this function hasn't succeeded. (In SQLite we can't guarantee that the value in column will have a certain type. But we must guarantee it in the application while reading SQLite).

* signature.h
Describes Signature class, which describes the one biochemical experiment.

* signatureCluster.h
Describes SignatureCluster class, inherited from Signature. The mechanism of virtual functions allows to print cluster tree without need to distinguishing leafs (elements without children). In this limited version, all cluster tree have exactly two layers, so the using of virtual functions may not seem reasonable at the first look.   
