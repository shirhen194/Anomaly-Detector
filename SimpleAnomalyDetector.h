#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
struct correlatedFeatures {
    correlatedFeatures() : minCircle(Point(0, 0), 0), isCircle(false) {};
    string feature1, feature2;  // names of the correlated features
    float corrlation = 0;
    Line lin_reg = {0, 0};
    float threshold = 0;
    bool isCircle = false;
    Circle minCircle;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> cf;
    vector<AnomalyReport> ar;
    // N is number of rows in the tests time series.
    int N;
    float threshold = 0.9;
public:
    SimpleAnomalyDetector();

    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries &ts);

    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    virtual void addCorrelatedFeature(correlatedFeatures cf1);

    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }

    virtual void checkCorrelation(const TimeSeries &ts, int f1, int f2, float m, float threshold);

    virtual correlatedFeatures createCorrelatedFeatures(const TimeSeries &ts, int i, int j, float correlation);

    virtual float computeMaxDev(vector<Point *> data, int size, Line l);

    virtual void releaseAllocatedPoints(vector<Point *> data);

    virtual bool isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf);

    float getThreshold() const;

    void setThreshold(float threshold);

    const vector<AnomalyReport> &getAnomalyReport() ;

    void setAnomalyReport(vector<AnomalyReport> ar) ;

    int getN() const;

    void setN(int n);
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
