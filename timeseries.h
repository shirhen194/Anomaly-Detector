

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries{

public:

	TimeSeries(const char* CSVfileName){
	}

	virtual int getNumberOfColumns() const;
    virtual float* getVectorFeature(int i) const;
    virtual int getNumberOfRows() const;
    virtual string getFeatureName(int i) const;

};



#endif /* TIMESERIES_H_ */
