////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>

/**
 * cov
 * @param x - vector of floats
 * @param y - vector of floats
 * @param size - size of the vectors.
 * @return the covariance of X and Y
 */
float cov(vector<float> x, vector<float> y, int size) {
    //𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸(𝑋𝑌) − 𝐸(𝑋)𝐸(𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌))

    //calculate average for X and Y
    float avgX = avg(x, size);
    float avgY = avg(y, size);

    //array of multiplications
    vector<float> mult;
    for (int i = 0; i < size; i++) {
        mult.push_back((x[i] - avgX) * (y[i] - avgY));
    }

    //calculate the covariance of X and Y
    float covariance = avg(mult, size);
    //return the covariance
    return covariance;
}

/**
 * linear_reg.
 * @param points - vector of pointers to point.
 * @param size - size of vector points.
 * @return -performs a linear regression and return s the line equation
 */
Line linear_reg(vector<Point *> points, int size) {
//    float a = cov()
    vector<float> X;
    vector<float> Y;
    //create the X and Y arrays
    for (int i = 0; i < size; i++) {
        X.push_back(points[i]->x);
        Y.push_back(points[i]->y);
    }
    //calculate the covariance and variance of X and Y
    float covariance = cov(X, Y, size);
    //calculate the variance of X and Y
    float variance = var(X, size);

    //calculate a and b for the Y = a*X +b
    float a = covariance / variance;
    float b = avg(Y, size) - a * avg(X, size);
    //create and return the new Line
    Line *line = new Line(a, b);
    return *line;
}

/**
 * dev.
 * @param p - point
 * @param l - line
 * @return - returns the deviation between point p and the line
 */
float dev(Point p, Line l) {
    float distance = l.f(p.x) - p.y;
    // Taking the root of squared distance (l2 distance)
    return distance < 0 ? -distance : distance;
}

/**
 * avg.
 * @param x - vector of floats.
 * @param size - size of the vector.
 * @return - return the average of array x
 */
float avg(vector<float> x, int size) {
    float meanX = 0;
    //compute the sum of X array
    for (int i = 0; i < size; i++) {
        meanX += x[i];
    }
    //divide by size of the array
    return meanX / size;
}

/**
 * var.
 * @param x - vector of floats.
 * @param size - size of the vector.
 * @return -returns the variance of X and Y
 */
float var(vector<float> x, int size) {
    float varX = 0;
    // average of array X
    float meanX = avg(x, size);
    //compute the sum of X array (each element pow by 2)
    for (int i = 0; i < size; i++) {
        varX += pow(x[i], 2);
    }
    varX = varX / size - pow(meanX, 2);
    return varX;
}

/**
 * pearson.
 * @param x - vector of floats
 * @param y - vector of floats
 * @param size - size of the vectors.
 * @return -returns the Pearson correlation coefficient of X and Y
 */
float pearson(vector<float> x, vector<float> y, int size) {
    return cov(x, y, size) / (sqrt((var(x, size))) * sqrt(var(y, size)));
}

/**
 * dev.
 * @param p - point.
 * @param points - vector of pointers to point.
 * @param size - size of poits vector.
 * @return - returns the deviation between point p and the line equation of the points
 */
float dev(Point p, vector<Point *> points, int size) {
    Line line = linear_reg(points, size);
    // returns |f(x) - y)|
    return dev(p, line);
}

