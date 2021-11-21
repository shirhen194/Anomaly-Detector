#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <utility>
#include <string>
#include <vector>
#include <map>
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

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
    int getNumberOfRows() const;
    string getFeatureName(int i) const;
    vector<float> getVectorFeature(string name) const;
    map<string, vector<float>> loadCsv();
};

#endif /* TIMESERIES_H_ */
