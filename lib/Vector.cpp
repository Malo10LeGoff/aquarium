//
// Created by minhtri on 18/03/2022.
//
#define _USE_MATH_DEFINES
#include "Vector.h"
#include <cmath>
#include <limits>
// functions
double scalar(const Vector &a, const Vector &b){
    return a.x * b.x + a.y + b.y;
}
double det(const Vector &a, const Vector &b){
    return a.x * b.y - a.y * b.x;
}


// Unary operators
double norm(const Vector &v){
    return std::sqrt(scalar(v,v));
};

double distanceVectors(const Vector &a, const Vector &b){
    return norm(a - b);
}


// Member functions
Vector Vector::operator+(const Vector &b) const {
    return {x + b.x, y + b.y};
}

Vector Vector::operator-(const Vector &b) const {
    return {x - b.x, y - b.y};
}

Vector Vector::normalize() const {
    return {x / norm(*this), y / norm(*this)};
}

double Vector::orientation() const {
    if (x == 0) {
        if (y> 0) {
            return M_PI /2;
        } else if (y<0){
            return - M_PI / 2;
        }
        return std::numeric_limits<double>::quiet_NaN();
    } else {
        double angle = atan(y / x);
        if (x<0) {
            angle += M_PI;
        }
        return std::fmod(angle, 2*M_PI);
    }
}

Vector Vector::rotate(double radian) {
    return {x * cos(radian) - y * sin(radian), x * sin(radian) + y * sin(radian)};
}

std::array<double, 2> Vector::asArray() const {
    return std::array<double, 2>{x,y};
}

void Vector::reflectX() {
    y = -y;
}

void Vector::reflectY() {
    x = -x;
}

Vector &Vector::operator+=(const Vector &b) {
    x += b.x;
    y += b.y;
    return *this;
}

Vector &Vector::operator*=(double k) {
    x *= k;
    y *= k;
}

Vector operator*(const Vector v, double k) {
    return {v.x * k, v.y * k};
}

Vector operator*(double k, const Vector v) {
    return v * k;
}

Vector operator/(const Vector v, double k) {
    return {v.x /k, v.y / k };
}

void Vector::clip(double xMin, double xMax, double yMin, double yMax) {
    const int margin = 5;
    x = std::min(xMax - margin, std::max(xMin + margin , x));
    y = std::min(yMax - margin , std::max(yMin + margin , y));
}

void Vector::alignToGrid() {
    x = std::round(x);
    y = std::round(y);
}

bool operator==(const Vector &a, const Vector &b) {
    return (a.x == b.x) && (a.y == b.y);
}


