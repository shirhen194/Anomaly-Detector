#ifndef COMMANDS_H_
#define COMMANDS_H_

//#include<iostream>
#include <string.h>

//#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual void readFile(string fileName) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

//class StandardIO : DefaultIO {
//public:
//    StandardIO() {}
//
//    virtual ~StandardIO() {
//
//    }
//
//    string read() {
//        string str;
//        cin >> str;
//        return str;
//    }
//
//    void write(string text) {
//        cout << text << endl;
//    }
//
//    void write(float f) {
//        cout << f << endl;
//    }
//
//    void read(float *f) {
//        cin >> *f;
//
//    }
//
//    void readFile(string fileName) {
//        string line;
//        vector<string> lines;
//        line = this->read();
//        while (line != "done") {
//            lines.push_back(line);
//            line = this->read();
//        }
//        this->writeToFile(lines, fileName);
//        this->write("Upload complete.");
//    }
//
//    void writeToFile(vector<string> lines, string fileName) {
//        ofstream file;
//        file.open(fileName);
//        for (string l: lines) {
//            file << l << endl;
//        }
//        file.close();
//    }
//};

class Command {
protected:
    string description;
    DefaultIO *dio;
    SimpleAnomalyDetector *anomalyDetector;

public:
    Command(DefaultIO *dio, string description, SimpleAnomalyDetector *anomalyDetector)
            : dio(dio), description(description), anomalyDetector(anomalyDetector) {}

    virtual void execute() = 0;

    virtual ~Command() {}

    virtual string getDescription() = 0;

};

class UploadCommand : public Command {

public:
    UploadCommand(DefaultIO *dio, string description, SimpleAnomalyDetector *ad)
            : Command(dio, description, ad) {}

    virtual ~UploadCommand() {

    }

    virtual void execute() {
        // load the train file.
        loadFile("Please upload your local train CSV file.", "anomalyTrain.csv");
        // load the test file.
        loadFile("Please upload your local test CSV file.", "anomalyTest.csv");
    }

    void loadFile(string message, string fileName) {
        // write massage to client.
        this->dio->write(message);
        // read from client and save in csv file.
        this->dio->readFile(fileName);
    }

    virtual string getDescription() {
        return this->description;
    }

};

class AlgoSettingCommand : public Command {
public:
    AlgoSettingCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *ad)
            : Command(dio, description, anomalyDetector) {}

    virtual ~AlgoSettingCommand() {

    }

    virtual void execute() {
        // write to client the current threshold.
        this->dio->write("The current correlation threshold is ");
        this->dio->write(this->anomalyDetector->getThreshold());

        // ask for new threshold
        this->dio->write("\nType a new threshold \n");

        // read threshold from client until get threshold in range of 0 to 1.
        float newThreshold;
        newThreshold = stoi(this->dio->read());
        while (newThreshold > 1 || newThreshold < 0) {
            this->dio->write("please choose a value between 0 and 1.\n");
            newThreshold = stoi(this->dio->read());
        }

        // set new threshold.
        this->anomalyDetector->setThreshold(newThreshold);
    }

    virtual string getDescription() {
        return this->description;
    }


};

class DetectCommand : public Command {
public:
    DetectCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *ad)
            : Command(dio, description, anomalyDetector) {}

    virtual ~DetectCommand() {

    }

    virtual void execute() {
        TimeSeries *trainTs = new TimeSeries("anomalyTrain.csv");
        TimeSeries *testTs = new TimeSeries("anomalyTest.csv");
        this->anomalyDetector->learnNormal(*trainTs);
        this->anomalyDetector->setAnomalyReport(this->anomalyDetector->detect(*testTs));
        this->dio->write("complete detection anomaly.\n ");

    }

    virtual string getDescription() {
        return this->description;
    }

};

class DisplayResultsCommand : public Command {
public:
    DisplayResultsCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~DisplayResultsCommand() {

    }

    virtual void execute() {
        for (AnomalyReport ar: this->anomalyDetector->getAnomalyReport()) {
            this->dio->write(ar.timeStep);
            this->dio->write("\t" + ar.description + "\n");
        }
        this->dio->write("Done.\n");
    }

    virtual string getDescription() {
        return this->description;
    }

};

#endif /* COMMANDS_H_ */
