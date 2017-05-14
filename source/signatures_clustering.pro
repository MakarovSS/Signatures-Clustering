QT -= gui
QT += sql

CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    signature.cpp \
    read_signatures_from_sqlite.cpp \
    centroid_linkage_hierarchical_clustering.cpp \
    clusterize_signatures.cpp \
    compute_correlation.cpp \
    hierarchical_clustering_elements.cpp \
    signature_cluster.cpp \
    print_signature_clusters.cpp

HEADERS += \
    signature.h \
    read_signatures_from_sqlite.h \
    centroid_linkage_hierarchical_clustering.h \
    clusterize_signatures.h \
    compute_correlation.h \
    hierarchical_clustering_elements.h \
    signature_cluster.h \
    print_signature_clusters.h \
    read_query_values.h
