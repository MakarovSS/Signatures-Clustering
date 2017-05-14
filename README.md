***** GENERAL INFORMATION *****

This is C++ console application which was developed with use of QT Creator. It is a small part of my project Attagraph, which I developed for health sciences company Attagene Inc, located in Research Triangle Park, USA. This part has very limited functionality and exposed only for code quality testing.

The core function of this application is to read objects from SQLite database, clusterize them by agglomerative hierarchical clustering (centroid linkage) to the cutting threshold provided by user, and then print results of clustering on a console.

Note that similarity between objects is calculated as Pearson correlation coefficient, which may seem controversial to the centroid linkage technique (centroid is still calculated on euclidean-based distance). Despite of that, it is the way by which clustering of real  data, provided by Attagene, gives the most biochemically reasonable clustering results.

***** INSTALLATION *****

Code is provided in "source" folder and can be compiled in any OS from QT Creator.

There are also compiled debug and release versions for Windows in "build/debug" and "build/release". To use them, you should run signature_clustering.exe from command prompt.

Before running an application, ensure that file "signatures.sqlite" is located in application's working directory.

***** SPECIFIC TERMS *****

- "Signature" is a desciption of one biochemical experiment. It contains a vector of values which describes the result of experiment, and additional information about experiment, such as compound and its concentration, for which experiment was performed.
- "Activity" is a one of values, observed in the experiment. In this demo-version, each signature is characterized by 8 activites. In real application, there is about 50 signatures for each signature.

***** SQLITE STRUCTURE *****

The application has some requirements for SQLite file:
- It has to be named "signature.sqlite" and located in application's working directory.
- It must have table named "info" with columns "property" and "value". This table has to contain record with "property" = "activities_count", defining how much activities describe each signature.
- It must have "signatures" table which gives an information about signatures (compound and its concentration). This table can be empty.
- It must have "activities" table which contains information about activities for each signature. This table can also be empty; in this case, application will recognize no signatures.

Since this application has no purpose to provide user easy way to create or modify SQLite databases, the general advice is to use pre-made SQLite database which is provided with the application. The data in SQLite database have no connection with a real biochemical data.

***** FILES DESCRIPTION *****

* main.cpp

Calls the main function, which consequently calls reading SQLite database and creation of signatures list from obtained data, clustering the signature list by agglomerative hierarchical clustering with centroid linkage, and printing the results of clustering on console.

* centroid_linkage_hierarchical_clustering.h

Performs the agglomerative hierarchical clustering with centroid linkage. 
The input of the procedure is matrix of float numbers (it can be signatures activities, or something else - the procedure is common and doesn't require Signature syntax).
The output is list of clusters, and extended matrix of float numbers, which allows to describe activities of each cluster.

* clusterize_signatures.h

A link between main.cpp and centroid_linkage_hierarchical_clustering: transforms list of signatures in more common form as matrix of floats, runs clustering, interpretate results as clusters of signatures.

* compute_correlation.h

Contains a function calculating Pearson's correlation coefficient.

* hierarchical_clustering_elements.h

Describes a namespace HierarchicalClusteringElements, which contains two classes - Cluster and Linkage. They are used in the process of clustering, and as output of this process, and supposingly nowhere else in the program.

* print_signature_clusters.h

Prints signatures cluster tree. In this limited version, the tree has exactly two levels.

* read_signatures_from_sqlite.h

Opens SQLite database, reads the information, transform it to the form of signature's list.

* read_query_values.h

Contains template function queryToVariable, which is required to generalize query.value().toInt(), ...toString(), ...toFloat() and allow us to throw an exception if these functions did not succeeded. (In SQLite we can't guarantee that the value in column will have required type. But we must guarantee it in the application while reading SQLite).

* signature.h

Describes Signature class, which describes the parameters and response of one given biochemical experiment.

* signatureCluster.h

Describes SignatureCluster class, inherited from Signature. The mechanism of virtual functions allows to show cluster tree without need to distinguishing leafs (elements without children) from nodes (clusters). In this limited version, cluster tree has exactly two levels, so using of virtual functions may not seem reasonable at first look.
