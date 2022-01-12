////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#include "CLI.h"
#include <iostream>
#include <string>
#include <sstream>

/**
 * CLI.
 * @param dio- IO to communicate with client.
 */
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    vector<Command *> commands;
    SimpleAnomalyDetector *ad = new HybridAnomalyDetector();
    this->ad = ad;
    Command *c1 = new UploadCommand(dio, "1.upload a time series csv file\n", ad);
    commands.push_back(c1);
    Command *c2 = new AlgoSettingCommand(dio, "2.algorithm settings\n", ad);
    commands.push_back(c2);
    Command *c3 = new DetectCommand(dio, "3.detect anomalies\n", ad);
    commands.push_back(c3);
    Command *c4 = new DisplayResultsCommand(dio, "4.display results\n", ad);
    commands.push_back(c4);
    Command *c5 = new AnalyzeAnomaliesCommand(dio, "5.upload anomalies and analyze results\n", ad);
    commands.push_back(c5);
    this->commands = commands;
}

void CLI::start() {
    int numOption = 0;
    string sOption;
    while(numOption != 6) {
        printMenu();
        sOption = dio->read();
        numOption = std::stoi(sOption);
        if(numOption == 6){
            break;
        }
        commands[numOption - 1]->execute();
    }
}

void CLI::printMenu() {
    this->dio->write("Welcome to the Anomaly Detection Server.\n"
                     "Please choose an option:\n");
    for (int i = 0; i < this->commands.size(); i++) {
        this->dio->write(this->commands[i]->getDescription());
    }
    this->dio->write("6.exit\n");
}

CLI::~CLI() {
    for (Command *c: this->commands) {
        delete c;
    }
    delete ad;
}

