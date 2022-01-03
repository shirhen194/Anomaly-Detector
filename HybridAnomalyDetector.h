#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    virtual void checkCorrelation(const TimeSeries &ts, int f1, int f2, float m, float threshold);
    correlatedFeatures createCorrelatedFeaturesCircle(const TimeSeries &ts, int i, int j, float correlation);
    virtual bool isExceptional(const TimeSeries &ts, int i, correlatedFeatures cf);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */

