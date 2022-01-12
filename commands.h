////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <cstring>

#include <vector>
#include <fstream>
#include <iomanip>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include "HybridAnomalyDetector.h"


using namespace std;

/**
 * DefaultIO Interface.
 * define write and read methods.
 */
class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}
};

class SocketIO: public DefaultIO{
private:
    int clientID;
public:
    SocketIO(int clientId) : clientID(clientId) {}

    /**
     * this method reads from socket to buffer in server
     * @return string read
     */
    string read() override {
        string Input;
        char buffer;
        int buffSize = sizeof (char);
        //receive info
        recv(clientID, &buffer, buffSize, 0);
        //read buffer to clientInp until endline
        while(buffer != '\n'){
            Input += buffer;
            recv(clientID, &buffer, buffSize, 0);
        }
        return Input;
    }

    /**
     * this method writes given text to the server
     * @param text the text to send to server
     */
    void write(string text) override {
        send(clientID, text.c_str(), text.size(), 0);
    }

    /**
     * this method writes the given number to the server
     * @param f float number to send to server
     */
    void write(float f) override {
        std::ostringstream num;
        num << f;
        std::string s(num.str());
        write(s);
    }

    /**
     * this method reads given number from the socket to server
     * @param f
     */
    void read(float *f) override {
        //call read to read buffer
        string input = read();
        //insert input number to given pointer value
        *f = stof(input);
    }

};

/**
 * Command Interface.
 * define the methode execute. the commands is on an object of SimpleAnomalyDetector,
 * and communicate to the client using DefaultIO.
 */
class Command {
protected:
    string description;
    DefaultIO *dio;
    SimpleAnomalyDetector *anomalyDetector;

public:
    Command(DefaultIO *dio, string description, SimpleAnomalyDetector *anomalyDetector)
            : dio(dio), description(description), anomalyDetector(anomalyDetector) {}

    virtual ~Command() {}

    virtual void execute() = 0;

    string getDescription() {
        return this->description;
    };

};

/**
 * UploadCommand implements Command.
 * upload train and test files to the serves from the client using dio.
 */
class UploadCommand : public Command {

public:
    UploadCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~UploadCommand() {

    }

    virtual void execute() {
        // load the train file.
        loadFile("Please upload your local train CSV file.\n", "anomalyTrain.csv");
        // load the test file.
        loadFile("Please upload your local test CSV file.\n", "anomalyTest.csv");
    }

    /**
     * loadFile.
     * @param message- write this message to client to ask specific file.
     * @param fileName - the name of the output file (where the server save the data from the client).
     */
    void loadFile(string message, string fileName) {
        // write message to client.
        this->dio->write(message);
        // read from client and save in csv file.
        this->readFile(fileName);
    }

    /**
     * readFile -  read a file from the client (receiving the data line by line) and save in a local file on the server.
     * @param fileName - local file to save the client data on.
     */
    void readFile(string fileName) {
        string line;
        vector<string> lines;
        line = this->dio->read();
        while (line != "done") {
            lines.push_back(line);
            line = this->dio->read();
        }
        //lines- a vector where each entry is a line of the sata the client sand.
        this->writeToFile(lines, fileName);
        this->dio->write("Upload complete.\n");
    }

    /**
     * writeToFile.
     * @param lines - vector of strings to save.
     * @param fileName - save each line in lines in this file.
     */
    void writeToFile(vector<string> lines, string fileName) {
        ofstream file;
        file.open(fileName);
        for (string l: lines) {
            file << l << endl;
        }
        file.close();
    }

};

/**
 * AlgoSettingCommand implements Command.
 * ask the client for a new threshold to SimpleAnomalyDetector.
 */
class AlgoSettingCommand : public Command {
public:
    AlgoSettingCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~AlgoSettingCommand() {

    }

    virtual void execute() {
        // write to client the current threshold.
        this->dio->write("The current correlation threshold is ");
        this->dio->write(this->anomalyDetector->getThreshold());
        this->dio->write("\n");
        // ask for new threshold
        this->dio->write("Type a new threshold\n");

        // read threshold from client until get threshold in range of 0 to 1.
        float newThreshold;
        this->dio->read(&newThreshold);
        while (newThreshold > 1 || newThreshold < 0) {
            this->dio->write("please choose a value between 0 and 1.\n");
            this->dio->read(&newThreshold);
        }

        // set new threshold.
        this->anomalyDetector->setThreshold(newThreshold);
    }
};

/**
 * DetectCommand implements Command.
 * detect the data the server receive from UploadCommand.
 */
class DetectCommand : public Command {
public:
    DetectCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~DetectCommand() {

    }

    virtual void execute() {
        //  TimeSeries handles the case where the files not exist
        TimeSeries *trainTs = new TimeSeries("anomalyTrain.csv");
        TimeSeries *testTs = new TimeSeries("anomalyTest.csv");
        this->anomalyDetector->learnNormal(*trainTs);
        this->anomalyDetector->detect(*testTs);
        this->dio->write("anomaly detection complete.\n");
        delete testTs;
        delete trainTs;
    }
};

/**
 * DisplayResultsCommand implements Command.
 * write the clients all the reports that has been detected (DetectCommand)
 */
class DisplayResultsCommand : public Command {
public:

    DisplayResultsCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~DisplayResultsCommand() {

    }

    virtual void execute() {
        for (AnomalyReport ar: this->anomalyDetector->getAnomalyReport()) {
            this->dio->write(to_string(ar.timeStep));
            this->dio->write("\t" + ar.description + "\n");
        }
        this->dio->write("Done.\n");
    }
};

/**
 * AnalyzeAnomaliesCommand implement Command.
 * write to client the True Positive rate and the False Positive rate.
 */
class AnalyzeAnomaliesCommand : public Command {
public:

    AnalyzeAnomaliesCommand(DefaultIO *dio, const string &description, SimpleAnomalyDetector *anomalyDetector)
            : Command(dio, description, anomalyDetector) {}

    virtual ~AnalyzeAnomaliesCommand() {

    }

    virtual void execute() {
        this->dio->write("Please upload your local anomalies file.\n");
        this->readAndAnalyzeAnomalies();
    }

    /**
     * readAndAnalyzeAnomalies.
     * receive from client the true anomalies and check the rate of TP, FP.
     */
    void readAndAnalyzeAnomalies() {

        // P is the number of anomalies series.
        int P = 0;
        // n is the number of time steps of the anomalies.
        int anomalies = 0;
        // n number of rows in the input to detect.
        int n = this->anomalyDetector->getN();
        // reportedAnomalies is the number of time steps that has been reported.

        vector<vector<string>> lines;
        string line = this->dio->read();
        while (line != "done") {
            // tokenize
            vector<string> tokens = tokenize(line, ",");
            lines.push_back(tokens);
            string start = tokens[0];
            string end = tokens[1];
            // check how many time steps in this series.
            anomalies = anomalies + stoi(end) - stoi(start) + 1;
            P++;
            // move to next line
            line = this->dio->read();
        }
        this->dio->write("Upload complete.\n");

        // write to client the true and false positive values.

        vector<int> results = this->analyzeReports(lines, this->anomalyDetector->getAnomalyReport());

        // number of time step with no anomaly.
        int N = n - anomalies;
        // result[0]=TP, result[1]=FP.
        float TPRate = results[0] / float(P);
        float FPRate = results[1] / float(N);
        writeTPFP(TPRate, FPRate);
    }

    /**
     * checkIfRangeOverlap-
     * checks if there is an overlap between one predicted anomaly (from detect),
     * with the true anomalies received.
     * @param predictedAnomaly - one series of predicted anomalies.
     * @param trueAnomalies - all tue anomalies received.
     * @return - true if there is an overlap, and false otherwise.
     */
    bool checkIfRangeOverlap(vector<int> predictedAnomaly, vector<vector<string>> trueAnomalies) {
        int predicted_start = predictedAnomaly[0];
        int predicted_end = predictedAnomaly[1];
        for (vector<string> trueAnomaly: trueAnomalies) {
            if (predicted_end >= stoi(trueAnomaly[0]) && predicted_end <= stoi(trueAnomaly[1]))
                return true;
            else if (predicted_start >= stoi(trueAnomaly[0]) && predicted_start <= stoi(trueAnomaly[1]))
                return true;
            else if (predicted_start <= stoi(trueAnomaly[0]) && predicted_end >= stoi(trueAnomaly[1]))
                return true;
        }
        return false;
    }

    /**
     * analyzeReports.
     * @param trueAnomalies - received from client.
     * @param reports - from detect.
     * @return - tp and fp in vector<int>. result[0]=tp, result[1]=fp.
     */
    vector<int> analyzeReports(vector<vector<string>> trueAnomalies, const vector<AnomalyReport> reports) {
        vector<vector<int>> predictedAnomalies = extractRangesFromReport(reports);
        int tp = 0;
        int fp = 0;
        for (vector<int> predictedAnomaly: predictedAnomalies) {
            if (checkIfRangeOverlap(predictedAnomaly, trueAnomalies)) {
                tp++;
            } else {
                fp++;
            }
        }
        vector<int> results;
        results.push_back(tp);
        results.push_back(fp);
        return results;
    }

    /**
     * extractRangesFromReport.
     * @param reports - all reports with time steps.
     * @return - the range of all the reports- combine a series of reports together.
     */
    vector<vector<int>> extractRangesFromReport(const vector<AnomalyReport> &reports) const {
        vector<vector<int>> ranges;
        if (reports.size() == 0) {
            return ranges;
        }
        int curr_start = reports[0].timeStep;
        int curr_end = reports[0].timeStep;
        string curr_description = reports[0].description;
        for (int i = 1; i < reports.size(); i++) {
            AnomalyReport ar = reports[i];
            //If new description - and range to vector and start new range (curr_start = timestep, curr_desc = description)
            //else:
            //  If curr_start+1==timestep - increase range (curr_end+=1)
            //  else: Add range to vector and restart range (curr_start = timestep, curr_desc=description)
            if (ar.description != curr_description) {
                addToRange(ranges, curr_start, curr_end);
                curr_start = ar.timeStep;
                curr_end = ar.timeStep;
                curr_description = ar.description;
            } else {
                if (curr_end + 1 == ar.timeStep) {
                    curr_end++;
                } else {
                    addToRange(ranges, curr_start, curr_end);
                    curr_start = ar.timeStep;
                    curr_end = ar.timeStep;
                }
            }
        }
        addToRange(ranges, curr_start, curr_end);
        return ranges;
    }

    void addToRange(vector<vector<int>> &ranges, int curr_start, int curr_end) const {
        vector<int> curr_range = {curr_start, curr_end};
        ranges.push_back(curr_range);
    }

    void writeTPFP(float TP, float FP) {
        // write to client the true and false positive values.
        this->dio->write("True Positive Rate: ");
        this->dio->write(formatFloat(TP));
        this->dio->write("\nFalse Positive Rate: ");
        this->dio->write(formatFloat(FP));
        this->dio->write("\n");
    }

    /**
     * formatFloat.
     * @param number
     * @return - the number with only 3 numbers after the dot.
     */
    float formatFloat(float number) const {
        float a = floorf(number * 1000) / 1000;
        return a;
    }

    /**
     * tokenize- separate the string to 2 strings using the delimiter.
     * @return
     */
    vector<string> tokenize(string s, string del) {
        vector<string> tokens;
        int start = 0;
        int end = s.find(del);
        while (end != -1) {
            tokens.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        tokens.push_back(s.substr(start, end - start));
        return tokens;
    }
};

#endif /* COMMANDS_H_ */
