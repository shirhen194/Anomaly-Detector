#ifndef TIMESERIES_H_
#define TIMESERIES_H_

using namespace std;

class TimeSeries {

public:

    TimeSeries(const char *CSVfileName) {
    }

    int getNumberOfColumns() const;

    float *getVectorFeature(int i) const;

    int getNumberOfRows() const;

    string getFeatureName(int i) const;

};

#endif /* TIMESERIES_H_ */
