#include "compute_correlation.h"

void calculateSumAndSquareSum(float &sum, float &squareSum, const QVector<float> &values)
{
    // Calculates sum and squareSum from given list of values.
    // One need to use those values repeatedly in clustering procedure,
    // so it is best to sacrifice some memory (small comparing to values matrix) to accelerate calculations.
    sum = 0;
    squareSum = 0;
    for (int i = 0; i < values.size(); ++i) {
        float f = values.at(i);
        sum += f;
        squareSum += f * f;
    }
}

float computeCorrelation(QVector<float> &x1, QVector<float> &x2, float sum1, float sum2, float squareSum1, float squareSum2)
{
    // Calculates Pearson's correlation coefficient between two vectors x1 and x2,
    int n = x1.size();
    Q_ASSERT(x2.size() == n);
    float multiSum = 0;
    for (int i = 0; i < n; ++i) {
        multiSum += x1.at(i) * x2.at(i);
    }

    float var1 = squareSum1 - sum1 * sum1 / n;
    float var2 = squareSum2 - sum2 * sum2 / n;
    float cov = multiSum - sum1 * sum2 / n;

    if (var1 * var2 > 0) {
        float value = cov / (sqrt(var1 * var2));
        return value;
    }
    else {
        throw QString("Computing correlations failed because of NaN value of correlation coefficient");
        return -2;
    }
}
