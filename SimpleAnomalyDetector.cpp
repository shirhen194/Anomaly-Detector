#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include "math.h"

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
Point **createPoints(vector<float> x, vector<float> y, int size) {
    vector<Point*> points;
    //Point **points = new Point *[size];

    for (int i = 0; i < size; i++) {
        // crate new point
        Point p (x[i], y[i]);
        // add the point to array of pointers to point.
        points.push_back(&p);
    }
    Point**data = &points[0];
    return data;
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
    return 1.1 * m;
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
    Point **data = createPoints(ts.getVectorFeature(ts.getFeatureName(i)), ts.getVectorFeature(ts.getFeatureName(j)),
                                ts.getNumberOfRows());
    Line l = linear_reg(data, ts.getNumberOfRows());
    float threshold = computeMaxDev(data, ts.getNumberOfRows(), l);
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
        for (int j = 0; j < n; j++) {
            //**i think that a feature should not check correletion with
            //itself so i add an if for when i == j
            if(i == j){
                continue;
            }
            //get features names
            string iName = ts.getFeatureName(i);
            string jName = ts.getFeatureName(j);
            //get columns by name
            vector<float> vector_i = ts.getVectorFeature(iName);
            vector<float> vector_j = ts.getVectorFeature(jName);
            // cast to float*
            //TODO: check if legal
            float *f_i = &vector_i[0];
            float *f_j = &vector_j[0];
            if (abs(pearson(f_i, f_j, ts.getNumberOfRows())) > m) {
                m = pearson(f_i, f_j, ts.getNumberOfRows());
                c = j;
            }
        }
        // i and c are correlated features with correlation m.
        correlatedFeatures cf1 = createCorrelatedFeatures(ts, i, c, m);
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
bool isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf) {
    float x =ts.getVectorFeature(cf.feature1)[i];
    float y = ts.getVectorFeature(cf.feature2)[i];
    Point p (x, y);
    if (dev(p, cf.lin_reg) > cf.threshold) {
        return true;
    }
    return false;
}

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