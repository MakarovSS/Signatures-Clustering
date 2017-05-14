#include "print_signature_clusters.h"

using std::cout;
using std::string;

void printSignature(const QSharedPointer<Signature> signature, int shift) {
    string str;
    for (int i = 0; i < shift; ++i) {
        str += " ";
    }
    if (signature->childCount() > 0) {
        str += "CLUSTER ";
    }
    else {
        str += "signature ";
    }
    str += std::to_string(signature->number());
    if (!signature->compound().isEmpty()) {
        str += "\t (" + signature->compound().toStdString();
        if (signature->concentration() > 0) {
            str += " " + QString::number(signature->concentration()).toStdString();
        }
        str += ")";
    }
    cout << str << "\n";
    for (int i = 0; i < signature->childCount(); ++i) {
        printSignature(signature->child(i), shift + 4);
    }
}

void printSignatureClusters(const QList<QSharedPointer<SignatureCluster> > signatureClusters) {
    int nSignatureClusters = signatureClusters.size();
    for (int i = 0; i < nSignatureClusters; ++i) {
        printSignature(signatureClusters.at(i), 0);
    }
}
