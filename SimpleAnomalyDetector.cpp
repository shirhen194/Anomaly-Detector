#include <iostream>
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include "math.h"

////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

//learn normal

/**
 * createPoints gets two vectors of floats point, creat from each row int the vector a point,
 * and add it to a vector of points.
 *
 * @param x - first vector,
 * @param y - second vector.
 * @param size - size of both vectors,
 * @return - vectors of pointers to point.
 */
vector<Point *> createPoints(vector<float> x, vector<float> y, int size) {
    vector<Point *> points;
    for (int i = 0; i < size; i++) {
        // crate new point
        Point *p = new Point(x[i], y[i]);
        // add the point to array of pointers to point.
        points.push_back(p);
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
    //multiply m in 1.1 to large the max dev of the linear reg.
    float max_dev = 1.1 * m;
    return max_dev;
}

/**
 * releaseAllocatedPoints.
 * @param data - vector of pointers to points. release all memory allocated.
 */
void releaseAllocatedPoints(vector<Point *> data) {
    for (auto &point:data) {
        delete point;
    }
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
    vector<Point *> data = createPoints(ts.getVectorFeature(ts.getFeatureName(i)),
                                        ts.getVectorFeature(ts.getFeatureName(j)),
                                        ts.getNumberOfRows());
    Point **points = &data[0];
    Line l = linear_reg(points, ts.getNumberOfRows());
    float threshold = computeMaxDev(points, ts.getNumberOfRows(), l);
    //delete data
    releaseAllocatedPoints(data);
    correlatedFeatures cF = {
            ts.getFeatureName(i), ts.getFeatureName(j), //features names
            correlation,
            l,
            threshold
    };
    return cF;
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
        //TODO: check correlation threshold!
        float m = 0.9;
        // c will save the index of the feature that feature i is most correlated to.
        int c = -1;
        for (int j = i + 1; j < n; j++) {
            //get features names
            string iName = ts.getFeatureName(i);
            string jName = ts.getFeatureName(j);
            //get columns by name
            vector<float> vector_i = ts.getVectorFeature(iName);
            vector<float> vector_j = ts.getVectorFeature(jName);
            float *f_i = &vector_i[0];
            float *f_j = &vector_j[0];
            float pearson_i_j = pearson(f_i, f_j, ts.getNumberOfRows());
            //abs pearson
            if (pearson_i_j < 0) {
                pearson_i_j = -1 * pearson_i_j;
            }
            if (pearson_i_j > m) {
                m = pearson_i_j;
                c = j;
            }
        }
        // i and c are correlated features with correlation m.
        if (c != -1) {
            correlatedFeatures cf1 = createCorrelatedFeatures(ts, i, c, m);
            //add correlatedFeatures i,c to the vector member.
            this->addCorrelatedFeature(cf1);
        }
    }

}

//detect
/**
 * isExceptional checks if the i'th roe in ts is exception regarding to the correlated feature cf.
 * @param ts - time series.
 * @param i - index of riw.
 * @param cf - correlatedFeature.
 * @return - true is there is an exception and false otherwise.
 */
bool isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf) {
    float x = ts.getVectorFeature(cf.feature1)[i];
    float y = ts.getVectorFeature(cf.feature2)[i];
    Point p(x, y);
    if (dev(p, cf.lin_reg) > cf.threshold) {
        return true;
    }
    return false;
}

/**
 * detect.
 * @param ts
 * @return - vector of reports of all exceptions in ts.
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> reports;
    int rows = ts.getNumberOfRows();
    for (int i = 0; i < rows; i++) {
        for (correlatedFeatures cf : this->cf) {
            if (isExceptional(ts, i, cf)) {
                string description = cf.feature1 + "-" + cf.feature2;
                AnomalyReport report(description, ts.getVectorFeature(ts.getFeatureName(0))[i]);
                reports.push_back(report);
            }
        }
    }
    return reports;
}