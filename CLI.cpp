#include "CLI.h"

/**
 * CLI.
 * @param dio- IO to communicate with client.
 */
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    vector<Command *> commands;
    SimpleAnomalyDetector *ad = new HybridAnomalyDetector();
    this->ad = ad;
    Command *c1 = new UploadCommand(dio, "upload a time series csv file\n", ad);
    commands.push_back(c1);
    Command *c2 = new AlgoSettingCommand(dio, "algorithm settings\n", ad);
    commands.push_back(c2);
    Command *c3 = new DetectCommand(dio, "detect anomalies\n", ad);
    commands.push_back(c3);
    Command *c4 = new DisplayResultsCommand(dio, "display results\n", ad);
    commands.push_back(c4);
    Command *c5 = new AnalyzeAnomaliesCommand(dio, "upload anomalies and analyze results\n", ad);
    commands.push_back(c5);
    this->commands = commands;
}

void CLI::start() {
    float index;
    this->dio->read(&index);
    int exit = this->commands.size();
    while (index != exit + 1) {
        printMenu();
        this->commands[index - 1]->execute();
        this->dio->read(&index);
    }
}

void CLI::printMenu() {
    this->dio->write("Welcome to the Anomaly Detection Server.\n"
                     "Please choose an option:\n");
    for (int i = 0; i < this->commands.size(); i++) {
        this->dio->write(i + 1);
        this->dio->write(".");
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

