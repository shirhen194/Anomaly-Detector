////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO *dio;
    vector<Command *> commands;
    SimpleAnomalyDetector *ad;
public:
    CLI(DefaultIO *dio);

    void start();

    virtual ~CLI();

    void printMenu();
};

#endif /* CLI_H_ */
