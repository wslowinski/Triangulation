#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    double x;
    double y;

public:
    Point(double x, double y);
    ~Point() = default;
    double getX();
    double getY();
    void lineSegment(Point *p);
    void circle(double r);
    friend Point operator+(Point A, Point B);
    friend Point operator-(Point A, Point B);
    friend double operator*(Point A, Point B);
    friend double operator^(Point A, Point B);
};

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}

Point operator+(Point A, Point B) {
    return Point(A.x + B.x, A.y + B.y);
}

Point operator-(Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y);
}

double operator*(Point A, Point B) {
    return A.x * B.x + A.y * B.y;
}

double operator^(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

void Point::lineSegment(Point *p) {
    std::cout << this->x << " " << this->y << " " << p->x << " " << p->y << std::endl;
}

void Point::circle(double r) {
    std::cerr << this->x << " " << this->y << " " << r << std::endl;
}

#endif