#include "CLI.h"

CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    vector<Command> commands;
    SimpleAnomalyDetector *ad = new HybridAnomalyDetector();
    Command *c1 = new UploadCommand(dio, "upload a time series csv file", ad);
    commands.push_back(*c1);
    Command *c2 = new AlgoSettingCommand(dio, "algorithm settings", ad);
    commands.push_back(*c2);
    Command *c3 = new DetectCommand(dio, "detect anomalies", ad);
    commands.push_back(*c3);
    Command *c4 = new DisplayResultsCommand(dio, "display results", ad);
    commands.push_back(*c4);
    this->commands = commands;

}

void CLI::start() {
    //TODO:: handle exceptions in stoi or gettin index out of range.
    int index = stoi(this->dio->read());
    while (index != this->commands.size()) {
        printMenu();
        this->commands[index - 1].execute();
        index = stoi(this->dio->read());
    }
}

void CLI::printMenu() {
    for (int i = 0; i < this->commands.size(); i++) {
        this->dio->write(i + ". " + this->commands[i].getDescription());
    }
}

CLI::~CLI() {

}

