#include <QCoreApplication>
#include <QDebug>
#include <iostream>

#include "read_signatures_from_sqlite.h"
#include "clusterize_signatures.h"
#include "print_signature_clusters.h"

using std::cin;
using std::cout;
using std::string;

// main function does the following:
// - reads relational .SQLite database with signatures;
// - creates the objects of class Signature in memory;
// - performs agglomerative centroid linkage hierarchical clustering with the similarity between objects given by Pearson's formula;
// - creates the objects of class SignatureCluster, inherited from Signature, which store information about clustering in form of
// parent-child relationship.

int main() try
{
    QList<QSharedPointer<Signature> > signatureList;
    int nActivities;

    // Read data from signatures.sqlite
    readSignatureListFromDatabase(signatureList, "signatures.sqlite", nActivities);

    cout << signatureList.size() << " signature(s) are read from database. Perform clustering? [y/n]\n";
    string string;
    cin >> string;
    if (string == "y") {
        // Ask user about threshold for clustering.
        bool correctValue = false;
        float correlationThreshold;
        while (!correctValue) {
            cout << "Enter r-value threshold (between -1 and 1)\n";
            cin >> string;
            correlationThreshold = atof(string.c_str());
            if ((correlationThreshold >= -1) && (correlationThreshold <= 1)) {
                correctValue = true;
            }
            else {
                cout << "Incorrect value.\n";
            }
        }

        //Start clustering
        QList<QSharedPointer<SignatureCluster> > clusterList;
        clusterizeSignatures(signatureList, clusterList, correlationThreshold);

        //Print results
        printSignatureClusters(clusterList);
    }
    cout << "Running of application is completed\n";
    return 0;
}
catch (QString& exception)
{
    cout << "Running of application is terminated because of the following exception:\n";
    cout << exception.toStdString() << "\n";
    return 1;
}
catch (std::bad_alloc& exception) {
    cout << "Application has run out of memory;\n";
    return 1;
}
