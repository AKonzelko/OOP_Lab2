#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area() const;
    bool isDegenerate() const;
    bool containsByCrossProduct(const Point& P) const;
    bool containsByHeron(const Point& P) const;
    bool isOnEdge(const Point& P) const;
};

double heronArea(const Triangle& t);
double distance(const Point& p1, const Point& p2);
void runProgram();

#endif