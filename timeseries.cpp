#include "timeseries.h"
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>
#include <sstream>

int TimeSeries::getNumberOfColumns() const{ return numOfColumns; }

//float *TimeSeries::getVectorFeature(char* n) const{
//return nullptr;
//}

int TimeSeries::getNumberOfRows() const{
    return numOfRows;
}

string TimeSeries::getFeatureName(int i) const{
    auto col = dataTable.begin();
    //advance the iterator until index
    for (int index = 0; index < i; index++)
    {
        //if out of bounds
        if(col != dataTable.end()){
            return nullptr;
        }
        col++;
    }
    return col->first;
}


vector<float> TimeSeries::getVectorFeature(string name) const{
//    return dataTable[name]->second;
    auto col = dataTable.begin();
    return col->second;
}

map<string, vector<float>>  TimeSeries::loadCsv(){
    //create the structure to save the data
    map<string, vector<float>> csvDataMap;
    //create the file stream
    std::ifstream dataStream(csvName);
    // Make sure the file is open
    if(!dataStream.is_open()) throw std::runtime_error("fle not opening :(");
    //read columns
    //get the first line
    std::string line;
    std::getline(dataStream, line);
    std::stringstream lineStream(line);

    //get column names
    std::string columnName;
    while (std::getline(lineStream, columnName, ',')) {
        //insert the column name and value to the csvData
        csvDataMap[columnName];
//        csvData.push_back({columnName, std::vector<float>{}});
        numOfColumns++;
    }
    int currValue;

    //read lines
    while (std::getline(dataStream, line)) {
        //iterator for the columns
        auto col = csvDataMap.begin();
        //get the current line
        std::stringstream currLine(line);
        //get all the values in the cells
        while (currLine >> currValue) {
            //add the value to the column vector
            col->second.push_back(currValue);
            //check if the next cell is emtpy to ignore it
            if (currLine.peek() == ',') currLine.ignore();
            col++;
        }
        numOfRows++;
    }
    return csvDataMap;
}
