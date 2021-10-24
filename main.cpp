#include <iostream>
#include "anomaly_detection_util.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    float x[] = {1, 2, 3, 4, 5, 0};
    float y[] = {6, 3, 7, 1, 9, 8};
    float k = cov(x, y, 6);
    return 0;
}
