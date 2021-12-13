#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
	vector<correlatedFeatures> cf;
public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);
	virtual void addCorrelatedFeature(correlatedFeatures cf1);

	vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

};


#endif /* SIMPLEANOMALYDETECTOR_H_ */
