#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area() const;
    bool isDegenerate() const;

    bool containsByCrossProduct(const Point& P) const;

    bool containsByBarycentric(const Point& P) const;

    bool isOnEdge(const Point& P) const;
};

void runProgram();

#endif