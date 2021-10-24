#include "anomaly_detection_util.h"
#include <iostream>

float avg(float *x, int size) {
    float sum = 0;

    //sum X and Y numbers for the average
    for (int i = 0; i < size; i++, x++) {
//        std::cout << "num is: " << *x << std::endl;
        sum += *x;
    }
    // find e the average for X and Y
    float average = sum / size;
    return average;
}

// return the covariance of X and Y
float cov(float *x, float *y, int size) {
    //𝑐𝑜𝑣(𝑋, 𝑌) = 𝐸(𝑋𝑌) − 𝐸(𝑋)𝐸(𝑌) = 𝐸((𝑋 − 𝐸(𝑋))(𝑌 − 𝐸(𝑌))

    //calculate average for X and Y
    float avgX = avg(x, size);
    float avgY = avg(y, size);

    //calculate 𝑋 − 𝐸(𝑋) and Y - E(X) by subtract each number in X and Y by their average
    for (int i = 0; i < size; i++, x++, y++) {
        *x -= avgX;
        *y -= avgY;
    }

    //array of multiplications
    float mult[size];
    for (int i = 0; i < size; i++, x++, y++) {
        mult[i] = *x * *y;
    }

    //calculate the covariance of X and Y
    float covariance = avg(mult, size);
    //return the covariance
    return covariance;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size) {
//    float a = cov()
    float X[size];
    float Y[size];
    //create the X and Y arrays
    for (int i = 0; i < size; i++, points++) {
        X[i] = (*points)->x;
        Y[i] = (*points)->y;
    }
    //calculate the covariance and variance of X and Y
    float covariance = cov(X, Y, size);
    //calculate the covariance of X and Y
    float variance = var(X, Y, size);

    //calculate a and b for the Y = a*X +b
    float a = covariance / variance;
    float b = avg(Y, size) - a * avg(X, size);

    //create and return the new Line
    Line line = new Line(a, b);
    return line;
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    //calculate |f(x) - y)|
    float deviation = l.f(p.x) - p.y;
    if (0 > deviation){
        deviation = -1 * deviation;
    }
    return deviation;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    float x[] = {1, 2, 3, 4, 5, 0};
    float y[] = {6, 3, 7, 1, 9, 8};
    float k = cov(x, y, 6);
    return 0;
}
