////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#ifndef ANOMALY_DETECTOR_ANOMALY_DETECTION_UTIL_H
#define ANOMALY_DETECTOR_ANOMALY_DETECTION_UTIL_H
#include <vector>
using namespace std;

//returns the average f the array
float avg(vector<float> x, int size);

// returns the variance of X and Y
float var(vector<float>x, int size);

// returns the covariance of X and Y
float cov(vector<float>x, vector<float>y, int size);

// returns the Pearson correlation coefficient of X and Y
float pearson(vector<float> x, vector<float>y, int size);

class Line {
public:
    float a, b;

    Line() : a(0), b(0) {}

    Line(float a, float b) : a(a), b(b) {}

    float f(float x) {
        return a * x + b;
    }
};

class Point {
public:
    float x, y;

    Point(float x, float y) : x(x), y(y) {}
    ~Point(){}
};

// performs a linear regression and return s the line equation
Line linear_reg(vector<Point*> points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p, vector<Point*> points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);

#endif //ANOMALY_DETECTOR_ANOMALY_DETECTION_UTIL_H
