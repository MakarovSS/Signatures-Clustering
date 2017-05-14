#include "read_signatures_from_sqlite.h"

int queryActivitiesNumber(QSqlDatabase &sqlDatabase) {
    Q_ASSERT(sqlDatabase.isOpen());

    QSqlQuery query(sqlDatabase);
    bool queryExec = query.exec("SELECT value FROM settings WHERE property = 'activities_count'");
    if (queryExec) {
        if (query.next()) {
            return queryToVariable<int>(query, 0);
        }
        else {
            throw QString("There is no information about activities_count property in the database");
        }
    }
    else {
        throw QString("Invalid structure of \"settings\" table in the database");
    }
    return 0;
}

QList<QSharedPointer<Signature> > querySignatures(QSqlDatabase &sqlDatabase, int nActivities) {
    Q_ASSERT(sqlDatabase.isOpen());

    QList<QSharedPointer<Signature> > signatures;

    QSqlQuery query(sqlDatabase);
    bool queryExec = query.exec("SELECT a.signature_number, s.compound, s.concentration, a.activity_index, a.value FROM activities a "
                                "LEFT JOIN signatures s ON a.signature_number = s.number ORDER BY a.signature_number");

    // Handling signatures and activities. When the value of "a.signature_number" changes, we create new Signature object and place
    // it in signatures list. Ordering of our query guarantees that each signature (i.e. signature with unique signature_number
    // will be threated only once, and all activities associated with that signature will be written in Signature object.
    if (queryExec)
    {
        int signatureIndex = 0;
        QSharedPointer<Signature> signature(nullptr);
        while (query.next()) {
            int index = queryToVariable<int>(query, 0);
            if ((index != signatureIndex) && (index >= 0)) {
                signature = QSharedPointer<Signature>::create(nActivities);
                signature->setNumber(index);
                signature->setCompound(queryToVariable<QString>(query, 1));
                signature->setConcentration(queryToVariable<float>(query, 2));
                signatures.append(signature);
                signatureIndex = index;
            }
            if (signature != nullptr) {
                int activityIndex = queryToVariable<int>(query, 3) - 1;
                if ((activityIndex >= 0) && (activityIndex < nActivities)) {
                    float activityValue = queryToVariable<float>(query, 4);// query.value(4).toFloat();
                    signature->setNumber(index);
                    signature->setActivity(activityIndex, activityValue);
                }
            }
            // Note: to create signature, we need only one value of activity, corresponding to the signature.
            // All other activities, if hadn't been mentioned in database, is supposed to be equal to 0.
            // It's not a bug, it's a feature! (Because we don't want to store null-responses in the database).
        }
    }
    else {
        throw QString("Invalid structure of table \"signatures\" or \"activities\" in the database.");
    }
    return signatures;
}

void readSignatureListFromDatabase(QList<QSharedPointer<Signature> > &signatures, QString databaseFileName, int &nActivities)
{
    const QString signatureDatabaseName = "signaturesDatabase";       //name for sqlite database

    // QSqlDatabase class requires all objects to go behind the scope before calling "removeDatabase" method,
    // so there we need to start new code block.
    {
        QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", signatureDatabaseName);
        database.setDatabaseName(databaseFileName);
        if (database.open()) {
            nActivities = queryActivitiesNumber(database);
            signatures = querySignatures(database, nActivities);
        }
        else {
            throw QString("can't open " + databaseFileName);
        }
    }
    QSqlDatabase::removeDatabase(signatureDatabaseName);
}
