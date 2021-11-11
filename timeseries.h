

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <utility>
#include <string>
#include <vector>

using namespace std;

class TimeSeries {
    std::string csvName;
    std::vector<std::pair<std::string, std::vector<int>>> dataTable;
    int numOfColumns;
    int numOfRows;

public:

    TimeSeries(std::string CSVfileName) {
        this->csvName = CSVfileName;
        this->dataTable = this->loadCsv();
    };

    int getNumberOfColumns() const;

    float *getVectorFeature(int i) const;

    int getNumberOfRows() const;

    string getFeatureName(int i) const;

    std::vector<std::pair<std::string, std::vector<float>>> loadCsv();
};


#endif /* TIMESERIES_H_ */
