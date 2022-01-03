#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle() : center(0, 0), radius(0) {}
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

#endif /* MINCIRCLE_H_ */
