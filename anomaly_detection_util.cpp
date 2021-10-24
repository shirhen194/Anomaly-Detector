////
//// Created by Shir and Reut on 16/10/2021.
////
#include "anomaly_detection_util.h"
#include <iostream>
#include <cmath>

// return the covariance of X and Y
float cov(float *x, float *y, int size) {
    //𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸(𝑋𝑌) − 𝐸(𝑋)𝐸(𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌))

    //calculate average for X and Y
    float avgX = mean(x, size);
    float avgY = mean(y, size);

    //calculate 𝑋 − 𝐸(𝑋) and Y - E(X) by subtract each number in X and Y by their average
    for (int i = 0; i < size; i++) {
        x[i] -= avgX;
        y[i] -= avgY;
    }

    //array of multiplications
    float mult[size];
    for (int i = 0; i < size; i++) {
        mult[i] = x[i] * y[i];
    }

    //calculate the covariance of X and Y
    float covariance = mean(mult, size);
    //return the covariance
    return covariance;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size) {
//    float a = cov()
    float X[size];
    float Y[size];
    //create the X and Y arrays
    for (int i = 0; i < size; i++) {
        X[i] = points[i]->x;
        Y[i] = points[i]->y;
    }
    //calculate the covariance and variance of X and Y
    float covariance = cov(X, Y, size);
    //calculate the variance of X and Y
    float variance = var(X, size);

    //calculate a and b for the Y = a*X +b

    float a = covariance / variance;
    float b = mean(Y, size) - a * mean(X, size);

    //create and return the new Line
    Line *line = new Line(a, b);
    return *line;
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    //calculate |f(x) - y)|
    float deviation = l.f(p.x) - p.y;
    // get absolute value
    deviation = abs(deviation);
    return deviation;
}

float mean(float *x, int size) {
    float meanX = 0;
    //compute the sum of X array
    for (int i = 0; i < size; i++) {
        meanX += x[i];
    }
    //divide by size of the array
    return meanX / size;
}

float var(float *x, int size) {
    float varX = 0;
    // average of array X
    float meanX = mean(x, size);
    //compute the sum of X array (each element pow by 2)
    for (int i = 0; i < size; i++) {
        varX += pow(x[i], 2);
    }
    varX = varX / size - pow(meanX, 2);
    return varX;
}

float pearson(float *x, float *y, int size) {
    return cov(x, y, size) / (sqrt((var(x, size))) * sqrt(var(y, size)));
}

float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    // returns |f(x) - y)|
    return abs(line.f(p.x) - p.y);
}

