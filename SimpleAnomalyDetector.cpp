#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include "math.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub


}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

/**
 * createPoints gets two vectors of floats point, creat from each row int the vector a point,
 * and add it to a vector of points.
 *
 * @param x - first vector,
 * @param y - second vector.
 * @param size - size of both vectors,
 * @return - vectors of pointers to point.
 */
Point **createPoints(float *x, float *y, int size) {
    Point **points = new Point *[size];
    for (int i = 0; i < size; i++) {
        // crate new point
        Point *p = new Point(x[i], y[i]);
        // add the point to array of pointers to point.
        points[i] = p;
    }
    return points;
}

/**
 * computeMaxDev.
 * @param data - vectors of pointers to points.
 * @param size - the size of vector data.
 * @param l - line;
 * @return - the dev between the points and line.
 */
float computeMaxDev(Point **data, int size, Line l) {
    // m will save the max dev.
    float m = 0;
    for (int i = 0; i < size; i++) {
        if (dev(*data[i], l) > m) {
            m = dev(*data[i], l);
        }
    }
    //point in index i has the max dev and m keeps it value.
    return m;
}

/**
 * createCorrelatedFeatures.
 * @param ts - the TimeSeries object.
 * @param i - the first feature.
 * @param j - second feature.
 * @param correlation - the degree of correlation between feature i and feature j.
 *
 * the function creates a new instance of the struct correlatedFeatures,
 * and add it as a member to correlatedFeature vector.
 */
correlatedFeatures createCorrelatedFeatures(const TimeSeries &ts, int i, int j, float correlation) {
    Point **data = createPoints(ts.getVectorFeature(i), ts.getVectorFeature(j), ts.getNumberOfRows());
    Line l = linear_reg(data, ts.getNumberOfRows());
    float threshold = computeMaxDev(data, ts.getNumberOfRows(), l);
    correlatedFeatures cF = {
            ts.getFeatureName(i), ts.getFeatureName(j), //features names
            correlation,
            l,
            threshold
    };
}

/**
 * addCorrelatedFeature.
 * @param cf1 - add cf1 to vector member in SimpleAnomalyDetector.
 */
void SimpleAnomalyDetector::addCorrelatedFeature(correlatedFeatures cf1) {
    this->cf.push_back(cf1);
}

/**
 * learnNormal - learn the correlated features and add all of them to the correlatedFeatures vector member.
 * @param ts
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    // n is the number of features.
    int n = ts.getNumberOfColumns();
    for (int i = 0; i < n; i++) {
        // m will save the largest correlation exist.
        int m = 0;
        // c will save the index of the feature that feature i is most correlated to.
        int c = -1;
        for (int j = 0; j < n; j++) {
            float *f_i = ts.getVectorFeature(i);
            float *f_j = ts.getVectorFeature(j);
            if (abs(pearson(f_i, f_j, ts.getNumberOfRows())) > m) {
                m = pearson(f_i, f_j, ts.getNumberOfRows());
                c = j;
            }
        }
        // i and c are correlated features.
        correlatedFeatures cf1 = createCorrelatedFeatures(ts, i, c, m);
        //add correlatedFeatures i,c to the vector member.
        this->addCorrelatedFeature(cf1);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // TODO Auto-generated destructor stub
}


