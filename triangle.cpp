#include "triangle.h"
#include <iostream>
#include <cmath>

using namespace std;

static double cross(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x);
}

double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

static double heronArea(const Point& A, const Point& B, const Point& C) {
    double a = distance(A, B);
    double b = distance(B, C);
    double c = distance(C, A);
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::area() const {
    return heronArea(A, B, C);
}

bool Triangle::isDegenerate() const {
    return fabs(cross(A, B, C)) < 1e-9;
}

bool Triangle::containsByCrossProduct(const Point& P) const {
    double d1 = cross(A, B, P);
    double d2 = cross(B, C, P);
    double d3 = cross(C, A, P);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool Triangle::containsByHeron(const Point& P) const {
    double S_main = area();
    double S1 = heronArea(A, B, P);
    double S2 = heronArea(B, C, P);
    double S3 = heronArea(C, A, P);
    double S_sum = S1 + S2 + S3;

    return fabs(S_main - S_sum) < 1e-9;
}

bool Triangle::isOnEdge(const Point& P) const {
    auto onSegment = [](const Point& A, const Point& B, const Point& P) {
        double cp = cross(A, B, P);
        if (fabs(cp) > 1e-9) return false;
        return min(A.x, B.x) - 1e-9 <= P.x && P.x <= max(A.x, B.x) + 1e-9 &&
               min(A.y, B.y) - 1e-9 <= P.y && P.y <= max(A.y, B.y) + 1e-9;
    };

    return onSegment(A, B, P) || onSegment(B, C, P) || onSegment(C, A, P);
}

void runProgram() {
    Triangle tri;
    int method;

    cout << "Введіть координати точки A (x y): ";
    cin >> tri.A.x >> tri.A.y;
    cout << "Введіть координати точки B (x y): ";
    cin >> tri.B.x >> tri.B.y;
    cout << "Введіть координати точки C (x y): ";
    cin >> tri.C.x >> tri.C.y;

    if (tri.isDegenerate()) {
        cout << "Трикутник є виродженим (його площа ≈ 0)." << endl;
    }

    cout << "Оберіть метод (1 - Векторний добуток, 2 - Герон): ";
    cin >> method;

    int n;
    cout << "Скільки точок хочете перевірити? ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Point P;
        cout << "Введіть координати точки " << i + 1 << " (x y): ";
        cin >> P.x >> P.y;

        bool inside = false;
        if (method == 1) {
            inside = tri.containsByCrossProduct(P);
        } else if (method == 2) {
            inside = tri.containsByHeron(P);
        } else {
            cout << "Невідомий метод!" << endl;
            return;
        }

        if (tri.isOnEdge(P)) {
            cout << "Точка лежить на межі трикутника." << endl;
        } else if (inside) {
            cout << "Точка лежить всередині трикутника." << endl;
        } else {
            cout << "Точка знаходиться поза трикутником." << endl;
        }
    }
}