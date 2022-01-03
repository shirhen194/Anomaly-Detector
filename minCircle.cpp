/**
 * The algorithm uses the observation:
 * The minimum enclosing circle (when there are more than 2 points) will be with 2 points on its boundary
 * where the distance between them is the diameter, or 3 points on its boundary and this is the minimum circle.
 * We will use these observation in the algorithm with the help of recursion - so each time we add the points that
 * will be on the boundary of the circle and create the circle accordingly.
 * Using an algorithm from the GeeksForGeeks website.
 */
////
//// Created by Reut Dayan 206433245 and Shir Hanono 208254912 on 16/10/2021.
////
#include <algorithm>
#include <math.h>
#include <vector>
#include "anomaly_detection_util.h"
#include "minCircle.h"

using namespace std;

/**
 * distance.
 * compute the distance between 2 points.
 * @return - the distance between point a and point b.
 */
float distance(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}

/**
 * isInside.
 * checks if the distance of the point from the center od the circle is larger from the radius.
 * @return - true if the point p is in the circle c, and false otherwise.
 */
bool isInside(const Circle &c, const Point &p) {
    return distance(c.center, p) <= c.radius;
}

/**
 * centerOf3Points.
 * @return - the center of the minimum circle with the 3 points on its boundary.
 */
Point centerOf3Points(float bx, float by, float cx, float cy) {
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;
    return {(cy * B - by * C) / (2 * D),
            (bx * C - cx * B) / (2 * D)};
}

/**
 * circleFrom3Points.
 * @return - a minimum circle enclosing the 3 points.
 */
Circle circleFrom3Points(const Point &a, const Point &b, const Point &c) {
    Point center = centerOf3Points(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
    center.x += a.x;
    center.y += a.y;
    // the radius is the distance between the center and a point on the boundary.
    Circle circle(center, distance(center, a));
    return circle;
}

/**
 * circleFrom2Points.
 * @return - a minimum circle enclosing the 2 points.
 */
Circle circleFrom2Points(const Point &a, const Point &b) {
    // Set the center to be the midpoint of a and b
    Point center((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
    // Set the radius to be half the distance ab
    Circle c(center, distance(a, b) / 2.0);
    return c;
}

/**
 * is_valid_circle.
 * @return - ture if all points in P are in the circle c, and false otherwise.
 */
bool isValid(const Circle &c, const vector<Point> &P) {
    // check if all the points in P are inside the circle.
    for (const Point &p : P)
        if (!isInside(c, p))
            return false;
    return true;
}

/**
 * createMinCircleFromAtMost3Points
 * @param p - vector of at most 3 points.
 * @return - the minimum circle were all the points in p are on its boundary.
 */
Circle createMinCircleFromAtMost3Points(vector<Point> &P) {
    if (P.empty()) {
        return {{0, 0}, 0};
    } else if (P.size() == 1) {
        return {P[0], 0};
    } else if (P.size() == 2) {
        return circleFrom2Points(P[0], P[1]);
    }
    // check if there is an enclosing circle from 2 points on its boundary from P.
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = circleFrom2Points(P[i], P[j]);
            if (isValid(c, P))
                return c;
        }
    }
    // circle from 3 points on its boundary.
    return circleFrom3Points(P[0], P[1], P[2]);
}

/**
 * findMinCircleRecursive.
 * @param points - array of pointers to points.
 * @param boundary - the points that will be on the boundary of th circle.
 * @param size - size of points array.
 * @return - the minimum enclosing circle.
 */
Circle findMinCircleRecursive(vector<Point> &P, vector<Point> boundary, int size) {
    // Base case: size =0 or 3 points on the boundary.
    if (size == 0 || boundary.size() == 3) {
        return createMinCircleFromAtMost3Points(boundary);
    }
    // Pick a random point randomly
    int idx = rand() % size;
    Point p = P[idx];
    swap(P[idx], P[size - 1]);
    // recursion:
    Circle d = findMinCircleRecursive(P, boundary, size - 1);
    // If d contains p, return d - d is enclosing all the points.
    if (isInside(d, p)) {
        return d;
    }
    // Otherwise, point p is on the boundary of the minimum enclosing circle.
    boundary.push_back(p);
    // Return the MEC for P - {p} and R U {p}
    return findMinCircleRecursive(P, boundary, size - 1);
}

/**
 * findMinCircle.
 * @param points  - array of pointers to points.
 * @param size - size of points array.
 * @return - the minimum enclosing circle.
 */
Circle findMinCircle(Point **points, size_t size) {
    // convert Point** to vector<Point>
    vector<Point> P;
    for (size_t i = 0; i < size; i++) {
        P.push_back(*points[i]);
    }
    vector<Point> P_copy = P;
    // call the recursion.
    return findMinCircleRecursive(P_copy, {}, P_copy.size());
}