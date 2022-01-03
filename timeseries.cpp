#include "timeseries.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>
#include <sstream>
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////

/**
 *  getter for the number of columns
 * @return the number of columns in the data table
 */
int TimeSeries::getNumberOfColumns() const { return numOfColumns; }

/**
 *  getter for the number of rows
 * @return the number of rows in the data table
 */
int TimeSeries::getNumberOfRows() const {
    return numOfRows;
}

/**
 * gets a columns name by it's index in the map
 * @param i the index of the column
 * @return the name of the column
 */
string TimeSeries::getFeatureName(int i) const {
    auto col = dataTable.begin();
    //advance the iterator until index
    for (int index = 0; index < i; index++) {
        //if out of bounds
        if (index > numOfColumns) {
            return nullptr;
        }
        col++;
    }
    return col->first;
}

/**
 * gets the vector of the column by it's name
 * @param name the name of the column
 * @return vector of specified column
 */
vector<float> TimeSeries::getVectorFeature(string name) const {
    auto col = dataTable.begin();
    for (int index = 0; col->first.compare(name); index++) {
        //should check if out of bounds?
        col++;
    }
    return col->second;
}

/**
 * this functions loads the csv file into a map of string-vector,
 * each element represents a column in the table.
 * while doing that,
 * it updates the state variables of numOfColumns and numOfRows.
 * @return map of the table data in the csv file
 */
map<string, vector<float>> TimeSeries::loadCsv() {
    //create the structure to save the data
    map<string, vector<float>> csvDataMap;
    //create the file stream
    std::ifstream dataStream(csvName);
    if (!dataStream.is_open()) throw std::runtime_error("file not open");
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
        numOfColumns++;
    }
    float currValue;

    //read the next lines of the file
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
