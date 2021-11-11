#include "timeseries.h"
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>

int TimeSeries::getNumberOfColumns() const{ return numOfColumns; }

float *TimeSeries::getVectorFeature(char* n) const{
return nullptr;
}

int TimeSeries::getNumberOfRows() const{
    return numOfRows;
}

string TimeSeries::getFeatureName(int i) const{
    return dataTable.at(i).first;
}


vector<float> TimeSeries::getFeatureValues(string name) const{
    auto it = std::find_if(std::begin(dataTable), std::end(dataTable), [&name](const auto & pair){
        return pair.first.compare(name) == 0;});
    return it->second ;// << access to the second string

    auto it = std::find_if(dataTable.begin(), dataTable.end(),
                           [&name](const std::pair<std::string , std::vector<float>>& elem) {
                               return elem.first == name;
                           });
    return it != dataTable.end() ? it->second : 99.99;
}

std::vector<std::pair<std::string, std::vector<float>>> TimeSeries::loadCsv(){
    //create the structure to save the data
    std::vector<std::pair<std::string, std::vector<float>>> csvData;
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
        //insert the column name - value vector to the csvData
        csvData.push_back({columnName, std::vector<float>{}});
        numOfColumns++;
    }
    int currValue;
    //read lines
    while (std::getline(dataStream, line)) {
        //for the index of the column
        int currCol = 0;
        //get the current line
        std::stringstream currLine(line);
        //get all the values in the cells
        while (currLine >> currValue) {
            //add the value to the column vector
            csvData.at(currCol).second.push_back(currValue);
            //check if the next cell is emtpy to ignore it
            if (currLine.peek() == ',') currLine.ignore();
            currCol++;
        }
        numOfRows++;
    }
    return csvData;
}