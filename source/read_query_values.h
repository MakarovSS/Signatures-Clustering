#ifndef READ_QUERY_VALUES_H
#define READ_QUERY_VALUES_H

#include <QSqlQuery>
#include <QString>
#include <QVariant>

// Generate exception if we can't transform query to value of required type.
inline void handleQuerySuccess(bool ok) {
    if (!ok) {
        throw QString("incorrect value in database");
    }
}

// Template function for translation QVariant to value of required type. Only specializations make sense.
// Calling this generalized function should never happen.
template<typename T>
T variantTransform(QVariant, bool *) {
    Q_ASSERT(false);
    return T();
}

template<>
inline int variantTransform<int> (QVariant variant, bool *ok) {
    return variant.toInt(ok);
}

template<>
inline float variantTransform<float> (QVariant variant, bool *ok) {
    return variant.toFloat(ok);
}

template<>
inline QString variantTransform<QString> (QVariant variant, bool *ok) {
    *ok = true;
    return variant.toString();
}

// We need this function since we want to throw exceptions when we can't transform QVariant from QSqlQuery to value of required type.
// We can't guarantee that value will always have required type in SQLite, so we need to check that inside the application.
template <typename T>
T queryToVariable(QSqlQuery& query, int index) {
    bool ok;
    T t = variantTransform<T>(query.value(index), &ok);
    handleQuerySuccess(ok);
    return t;
}

#endif // READ_QUERY_VALUES_H
