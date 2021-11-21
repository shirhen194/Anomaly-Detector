
#include <iostream>
#include "SimpleAnomalyDetector.h"
#include "timeseries.h"

#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

using namespace std;


#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

using namespace std;

// this is a simple test to put you on the right track
void generateTrainCSV(float a1,float b1, float a2, float b2){
    ofstream out("trainFile1.csv");
    out<<"A,B,C,D"<<endl;
    Line ac(a1,b1);
    Line bd(a2,b2);
    for(int i=1;i<=100;i++){
        float a=i;
        float b=rand()%40;
        out<<a<<","<<b<<","<<ac.f(a)-0.02+(rand()%40)/100.0f<<","<<bd.f(b)-0.02+(rand()%40)/100.0f<<endl;
    }
    out.close();
}

void generateTestCSV(float a1,float b1, float a2, float b2, int anomaly){
    ofstream out("testFile1.csv");
    out<<"A,B,C,D"<<endl;
    Line ac(a1,b1);
    Line bd(a2,b2);
    for(int i=1;i<=100;i++){
        float a=i;
        float b=rand()%40;
        if(i!=anomaly)
            out<<a<<","<<b<<","<<ac.f(a)-0.02+(rand()%40)/100.0f<<","<<bd.f(b)-0.02+(rand()%40)/100.0f<<endl;
        else
            out<<a<<","<<b<<","<<ac.f(a)+1<<","<<bd.f(b)-0.02+(rand()%40)/100.0f<<endl;
    }
    out.close();
}

//
//std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
//    // Reads a CSV file into a vector of <string, vector<int>> pairs where
//    // each pair represents <column name, column values>
//
//    // Create a vector of <string, int vector> pairs to store the result
//    std::vector<std::pair<std::string, std::vector<int>>> result;
//
//    // Create an input filestream
//    std::ifstream myFile(filename);
//
//    // Make sure the file is open
//    if(!myFile.is_open()) throw std::runtime_error("Could not open file");
//
//    // Helper vars
//    std::string line, colname;
//    int val;
//
//    // Read the column names
//    if(myFile.good())
//    {
//        // Extract the first line in the file
//        std::getline(myFile, line);
//
//        // Create a stringstream from line
//        std::stringstream ss(line);
//
//        // Extract each column name
//        while(std::getline(ss, colname, ',')){
//
//            // Initialize and add <colname, int vector> pairs to result
//            result.push_back({colname, std::vector<int> {}});
//        }
//    }
//
//    // Read data, line by line
//    while(std::getline(myFile, line))
//    {
//        // Create a stringstream of the current line
//        std::stringstream ss(line);
//
//        // Keep track of the current column index
//        int colIdx = 0;
//
//        // Extract each integer
//        while(ss >> val){
//
//            // Add the current integer to the 'colIdx' column's values vector
//            result.at(colIdx).second.push_back(val);
//
//            // If the next token is a comma, ignore it and move on
//            if(ss.peek() == ',') ss.ignore();
//
//            // Increment the column index
//            colIdx++;
//        }
//    }
//
//    // Close file
//    myFile.close();
//
//    return result;
//}

int main() {
    srand (time(NULL));
    float a1=1+rand()%10, b1=-50+rand()%100;
    float a2=1+rand()%20 , b2=-50+rand()%100;
    generateTrainCSV(a1,b1,a2,b2);
    // Read three_cols.csv and ones.csv
    TimeSeries ts("trainFile1.csv");


    return 0;
}


// this is a simple test to put you on the right track
//int main(){
//    TimeSeries ts("testCSV.csv");
//
//    cout<<"done"<<endl;
//    return 0;
//}
