#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <utility>
#include <string>
#include <vector>
#include <map>

using namespace std;

class TimeSeries {
    std::string csvName;
    map<string, vector<float>> dataTable;
    int numOfColumns = 0;
    int numOfRows = 0;

public:

    TimeSeries(std::string CSVfileName) {
        this->csvName = CSVfileName;
        this->dataTable = this->loadCsv();
    };

    int getNumberOfColumns() const;
//    float *getVectorFeature(int i) const;
    int getNumberOfRows() const;
    string getFeatureName(int i) const;
    vector<float> TimeSeries::getVectorFeature(string name) const;
    map<string, vector<float>> loadCsv();
};

#endif /* TIMESERIES_H_ */
