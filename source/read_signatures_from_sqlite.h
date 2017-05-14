#ifndef READ_SIGNATURES_FROM_SQLITE_H
#define READ_SIGNATURES_FROM_SQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "signature_cluster.h"
#include "read_query_values.h"

int queryActivitiesNumber(QSqlDatabase &sqlDatabase);
QList<QSharedPointer<Signature> > querySignatures(QSqlDatabase &sqlDatabase, int nActivities);
void readSignatureListFromDatabase(QList<QSharedPointer<Signature> > &signatureList, QString databaseFileName, int &nActivities);

#endif // READ_SIGNATURES_FROM_SQLITE_H
