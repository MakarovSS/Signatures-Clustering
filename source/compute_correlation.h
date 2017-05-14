#ifndef COMPUTE_CORRELATION_H
#define COMPUTE_CORRELATION_H

#include <QList>
#include <QVector>

void calculateSumAndSquareSum(float &sum, float &squareSum, const QVector<float> &values);
float computeCorrelation(QVector<float> &x1, QVector<float> &x2, float sum1, float sum2, float squareSum1, float squareSum2);

#endif // COMPUTE_CORRELATION_H
