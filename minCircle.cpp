//#include "minCircle.h"
//#include "math.h"
//#include "vector"
//
//using namespace std;
//
//// Infinity
//const double INF = 1e18;
//
///**
// * distance.
// * compute the distance between 2 points.
// * @return - the distance between point a and point b.
// */
//float distance(const Point &a, const Point &b) {
//    // distance = root ((x2-x1)^2+(y2-y1)^2)
//    double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//    return distance;
//}
//
///**
// * isInside.
// * checks if the distance of the point from the center od the circle is larger from the radius.
// * @return - true if the point p is in the circle c, and false otherwise.
// */
//bool isInside(const Circle &c, const Point &p) {
//    if (distance(p, c.center) <= c.radius)
//        return true;
//    return false;
//}
//
///**
// * centerOf3Points.
// * @param bx
// * @param by
// * @param cx
// * @param cy
// * @return - center of the circle define from three points.
// */
//Point centerOf3Points(float bx, float by, float cx, float cy) {
//    float B = bx * bx + by * by;
//    float C = cx * cx + cy * cy;
//    float D = bx * cy - by * cx;
//    Point center((cy * B - by * C) / (2 * D),
//                 (bx * C - cx * B) / (2 * D));
//    return center;
//}
//
///**
// * createMinCircleFrom3BoundaryPoints.
// * @param a
// * @param b
// * @param c
// * @return - a minimum circle enclosing the 3 points.
// */
//Circle createMinCircleFrom3BoundaryPoints(const Point &a, const Point &b, const Point &c) {
//    Point I = centerOf3Points(b.x - a.x, b.y - a.y,
//                              c.x - a.x, c.y - a.y);
//
//    I.x += a.x;
//    I.y += a.y;
//    Circle circle(I, distance(I, a));
//    return circle;
//}
//
///**
// * createMinCircleFrom2BoundaryPoints.
// * gets tow points and return the minimum circle that this 2 points are on its boundary.
// * @return -the minimum enclosing circle for points a,b.
// */
//Circle createMinCircleFrom2BoundaryPoints(const Point &a, const Point &b) {
//    // radius is half of the distance between the 2 points
//    float radius = distance(a, b) / 2;
//    // center is: x- the middle between the 2 x values, y- the middle between the 2 y values.
//    Point center((a.x + b.x) / 2, (a.y, b.y / 2));
//    Circle c(center, radius);
//    return c;
//}
//
///**
// * isValid.
// * checks if all the points in the array is in the circle. (using isInside function0
// * @return true if all points are in the circle and false otherwise.
// */
//bool isValid(const Circle &c, vector<Point> points) {
//    for (Point p:points) {
//        if (!isInside(c, p))
//            return false;
//    }
//    return true;
//}
//
///**
// * createMinCircleFromAtMost3Points
// * @param p - vector of at most 3 points.
// * @return - the minimum circle were all the points in p are on its boundary.
// */
//Circle createMinCircleFromAtMost3Points(vector<Point> p) {
//    // |P| <= 3
//    // there is no points on the boundary.
//    if (p.size() == 0) {
//        Point center(0, 0);
//        Circle c(center, 0);
//        return c;
//    }
//        // one point on the boundary -> just the case were the circle is the point.
//    else if (p.size() == 1) {
//        Circle c(p[0], 0);
//        return c;
//    }
//        // two points on the boundary -> createMinCircleFrom2BoundaryPoints
//    else if (p.size() == 2) {
//        return createMinCircleFrom2BoundaryPoints(p[0], p[1]);
//    }
//    // check if the circle can be with 2 points from the three
//    for (int i = 0; i < 3; i++) {
//        for (int j = i + 1; j < 3; j++) {
//            Circle c = createMinCircleFrom2BoundaryPoints(p[i], p[j]);
//            if (isValid(c, p))
//                return c;
//        }
//    }
//    // three points on the boundary -> createMinCircleFrom3BoundaryPoints
//    return createMinCircleFrom3BoundaryPoints(p[0], p[1], p[2]);
//}
//
///**
// * findMinCircleRecursive.
// * @param points - array of pointers to points.
// * @param boundary - the points that will be on the boundary of th circle.
// * @param size - size of points array.
// * @return - the minimum enclosing circle.
// */
//Circle findMinCircleRecursive(Point **points, vector<Point> boundary, size_t size) {
//    // base case size=0 or |boundary|=3
//    if (size == 0 || boundary.size() == 3) {
//        // create the circle with the points in boundary vector on its boundary.
//        return createMinCircleFromAtMost3Points(boundary);
//    }
//    // p is the last point in points array.
//    int index = rand() % size;
//    Point p = *points[index];
//    swap(points[index], points[size - 1]);
//    // recursive call
//    Circle c = findMinCircleRecursive(points, boundary, size - 1);
//    // check if p is in the circle
//    if (isInside(c, p))
//        return c;
//    // p is outside the circle -> will be on the boundary
//    boundary.push_back(p);
//
//    return findMinCircleRecursive(points, boundary, size - 1);
//}
//
///**
// * findMinCircle.
// * @param points  - array of pointers to points.
// * @param size - size of points array.
// * @return - the minimum enclosing circle.
// */
//Circle findMinCircle(Point **points, size_t size) {
//    vector<Point> boundary = {};
//    Point **points_copy = points;
//    return findMinCircleRecursive(points_copy, boundary, size);
//}
//
//// TODO: rewrite the 3boundary function!


// C++ program to find the minimum enclosing
// circle for N integer points in a 2-D plane
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"
#include "minCircle.h"

using namespace std;

// Defining infinity
const double INF = 1e18;

// Function to return the euclidean distance
// between two points
float dist(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle &c, const Point &p) {
    return dist(c.center, p) <= c.radius;
}

// The following two functions are used
// To find the equation of the circle when
// three points are given.

// Helper method to get a circle defined by 3 points
Point get_circle_center(float bx, float by,
                        float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

// Function to return a unique circle that
// intersects three points
Circle circle_from(const Point &A, const Point &B,
                   const Point &C) {
    Point I = get_circle_center(B.x - A.x, B.y - A.y,
                                C.x - A.x, C.y - A.y);

    I.x += A.x;
    I.y += A.y;
    return {I, dist(I, A)};
}

// Function to return the smallest circle
// that intersects 2 points
Circle circle_from(const Point &A, const Point &B) {
    // Set the center to be the midpoint of A and B
    Point C ((A.x + B.x) / 2.0, (A.y + B.y) / 2.0);

    // Set the radius to be half the distance AB
    Circle c (C, dist(A, B) / 2.0);
    return c;
}

// Function to check whether a circle
// encloses the given points
bool is_valid_circle(const Circle &c,
                     const vector<Point> &P) {

    // Iterating through all the points
    // to check whether the points
    // lie inside the circle or not
    for (const Point &p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

// Function to return the minimum enclosing
// circle for N <= 3
Circle min_circle_trivial(vector<Point> &P) {
    assert(P.size() <= 3);
    if (P.empty()) {
        return {{0, 0}, 0};
    } else if (P.size() == 1) {
        return {P[0], 0};
    } else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }

    // To check if MEC can be determined
    // by 2 points only
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm
// Takes a set of input points P and a set R
// points on the circle boundary.
// n represents the number of points in P
// that are not yet processed.
Circle welzl_helper(vector<Point> &P,
                    vector<Point> R, int n) {
    // Base case when all points processed or |R| = 3
    if (n == 0 || R.size() == 3) {
        return min_circle_trivial(R);
    }

    // Pick a random point randomly
    int idx = rand() % n;
    Point p = P[idx];

    // Put the picked point at the end of P
    // since it's more efficient than
    // deleting from the middle of the vector
    swap(P[idx], P[n - 1]);

    // Get the MEC circle d from the
    // set of points P - {p}
    Circle d = welzl_helper(P, R, n - 1);

    // If d contains p, return d
    if (is_inside(d, p)) {
        return d;
    }

    // Otherwise, must be on the boundary of the MEC
    R.push_back(p);

    // Return the MEC for P - {p} and R U {p}
    return welzl_helper(P, R, n - 1);
}

Circle findMinCircle(Point **points, size_t size) {
    vector<Point> P;
    for (size_t i = 0; i < size; i++) {
        P.push_back(*points[i]);
    }
    vector<Point> P_copy = P;
    return welzl_helper(P_copy, {}, P_copy.size());
}