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
float SimpleAnomalyDetector::computeMaxDev(vector<Point *> data, int size, Line l) {
    // m will save the max dev.
    float m = 0;
    for (int i = 0; i < size; i++) {
        if (dev(*data[i], l) > m) {
            m = dev(*data[i], l);
        }
    }
    //point in index i has the max dev and m keeps it value.
    //multiply m in 1.1 to large the max dev of the linear reg.
    return 1.1 * m;
}

/**
 * releaseAllocatedPoints.
 * @param data - vector of pointers to points. release all memory allocated.
 */
void SimpleAnomalyDetector::releaseAllocatedPoints(vector<Point *> data) {
    for (auto &point: data) {
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
correlatedFeatures
SimpleAnomalyDetector::createCorrelatedFeatures(const TimeSeries &ts, int i, int j, float correlation) {
    vector<Point *> data = createPoints(ts.getVectorFeature(ts.getFeatureName(i)),
                                        ts.getVectorFeature(ts.getFeatureName(j)),
                                        ts.getNumberOfRows());
    Line l = linear_reg(data, ts.getNumberOfRows());
    float threshold = computeMaxDev(data, ts.getNumberOfRows(), l);
    //delete data
    releaseAllocatedPoints(data);
    Point p(0, 0);
    Circle c(p, 0);
    string name1 = ts.getFeatureName(i);
    string name2 = ts.getFeatureName(j);
    correlatedFeatures cF;
    cF.corrlation = correlation;
    cF.feature1 = ts.getFeatureName(i);
    cF.feature2 = ts.getFeatureName(j);
    cF.threshold = threshold;
    cF.isCircle = false;
    cF.lin_reg = l;
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
        float m = 0;
        // c will save the index of the feature that feature i is most correlated to.
        int c = -1;
        for (int j = i + 1; j < n; j++) {
            //get features names
            string iName = ts.getFeatureName(i);
            string jName = ts.getFeatureName(j);
            //get columns by name
            vector<float> f_i = ts.getVectorFeature(iName);
            vector<float> f_j = ts.getVectorFeature(jName);
            if (abs(pearson(f_i, f_j, ts.getNumberOfRows())) > m) {
                m = pearson(f_i, f_j, ts.getNumberOfRows());
                c = j;
            }
        }
        // i and c are correlated features with correlation m.
        checkCorrelation(ts, i, c, m, this->threshold);
//        if (c != -1 && m >= 0.9) {
//            correlatedFeatures cf1 = createCorrelatedFeatures(ts, i, c, m);
//            //add correlatedFeatures i,c to the vector member.
//            this->addCorrelatedFeature(cf1);
//        }
    }

}


/**
 * this function checks if the correlation is in the right range,
 * and if it is, adds the features to correlated features.
 * @param ts    the time series by reference
 * @param i     first feature
 * @param m     correlation threshold
 * @param c     second feature
 */
void SimpleAnomalyDetector::checkCorrelation(const TimeSeries &ts, int f1, int f2, float m, float threshold) {
    if (f2 != -1 && m >= threshold) {
        correlatedFeatures cf1 = createCorrelatedFeatures(ts, f1, f2, m);
        //add correlatedFeatures i,c to the vector member.
        this->addCorrelatedFeature(cf1);
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
bool SimpleAnomalyDetector::isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf) {
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
    this->setN(ts.getNumberOfRows());
    vector<AnomalyReport> reports;
    int rows = ts.getNumberOfRows();
    for (correlatedFeatures cf: this->cf) {
        for (int i = 0; i < rows; i++) {
            if (isExceptional(ts, i, cf)) {
                string description = cf.feature1 + "-" + cf.feature2;
                AnomalyReport report(description, i + 1);
                reports.push_back(report);
            }
        }
    }
    this->setAnomalyReport(reports);
    return reports;
}

float SimpleAnomalyDetector::getThreshold() const {
    return threshold;
}

void SimpleAnomalyDetector::setThreshold(float threshold) {
    SimpleAnomalyDetector::threshold = threshold;
}

const vector<AnomalyReport> &SimpleAnomalyDetector::getAnomalyReport() {
    return ar;
}

void SimpleAnomalyDetector::setAnomalyReport(vector<AnomalyReport> ar1) {
    vector<AnomalyReport> new_ar;
    for (AnomalyReport a: ar1) {
        AnomalyReport new_a(a.description, a.timeStep);
        new_ar.push_back(new_a);
    }
    this->ar = vector<AnomalyReport>(new_ar);
}

int SimpleAnomalyDetector::getN() const {
    return N;
}

void SimpleAnomalyDetector::setN(int n) {
    N = n;
}
