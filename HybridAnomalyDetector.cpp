////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

#include "HybridAnomalyDetector.h"


HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub
}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

/**
 * this function creates and returns the points vector
 * @param x vector f1
 * @param y vector f2
 * @return the points vector
 */
Point **corrPoints(vector<float> x, vector<float> y) {
    Point **points = new Point *[x.size()];
    for (unsigned int i = 0; i < x.size(); i++) {
        points[i] = new Point(x[i], y[i]);
    }
    return points;
}

/**
 * gets distance from circle center
 * @param point - current point to compare to
 * @param c - thr minCircle
 * @return distance from circle center
 */
float getDistance(Point *point, const Circle &c) {
    float d = sqrt(pow(c.center.x - point->x,
                       2) + pow(c.center.y - point->y, 2) * 1.0);
    d = abs(d);
    return d;
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
correlatedFeatures
HybridAnomalyDetector::createCorrelatedFeaturesCircle(const TimeSeries &ts, int i, int j, float correlation) {

    Point **pointsData = corrPoints(ts.getVectorFeature(ts.getFeatureName(i)),
                                    ts.getVectorFeature(ts.getFeatureName(j)));
    int numRows = ts.getNumberOfRows();
    Circle minCircle = findMinCircle(pointsData, numRows);
    //delete allocated points
    for (size_t k = 0; k < numRows; k++)
        delete pointsData[k];
    delete[] pointsData;
    //create correlated feature
    Line l(0,0);
    float threshold = minCircle.radius * 1.1;
    string name1 = ts.getFeatureName(i);
    string name2 = ts.getFeatureName(j);
    correlatedFeatures cF;
    cF.corrlation = correlation;
    cF.feature1 = ts.getFeatureName(i);
    cF.feature2 = ts.getFeatureName(j);
    cF.threshold = minCircle.radius * 1.1;
    cF.isCircle = true;
    cF.minCircle = minCircle;
    return cF;
}


/**
 * this function checks if the correlation is in the right range,
 * and if it is, adds the features to correlated features.
 * @param ts    the time series by reference
 * @param i     first feature
 * @param m     correlation threshold
 * @param c     second feature
 */
void HybridAnomalyDetector::checkCorrelation(const TimeSeries &ts, int f1, int f2, float m, float threshold) {
    if (f2 != -1 && 0.5 <= m && threshold >= m) {
        correlatedFeatures cf1 = createCorrelatedFeaturesCircle(ts, f1, f2, m);
        //add correlatedFeatures i,c to the vector member.
        this->addCorrelatedFeature(cf1);
    } else if (f2 != -1 && 0.9 <= m) {
        correlatedFeatures cf1 = createCorrelatedFeatures(ts, f1, f2, m);
        //add correlatedFeatures i,c to the vector member.
        this->addCorrelatedFeature(cf1);
    }
}


/**
 * isExceptional checks if the i'th row in ts is exception regarding to the correlated feature cf.
 * @param ts - time series.
 * @param i - index of riw.
 * @param cf - correlatedFeature.
 * @return - true is there is an exception and false otherwise.
 */
bool HybridAnomalyDetector::isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf) {
    float x = ts.getVectorFeature(cf.feature1)[i];
    float y = ts.getVectorFeature(cf.feature2)[i];
    Point p(x, y);
    if(cf.isCircle && cf.threshold < getDistance(&p, cf.minCircle)){//if circle
        return true;
    } else if (!cf.isCircle && dev(p, cf.lin_reg) > cf.threshold) {//if line
        return true;
    }
    return false;
}
