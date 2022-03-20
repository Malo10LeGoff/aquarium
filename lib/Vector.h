#ifndef AQUARIUM_VECTOR_H
#define AQUARIUM_VECTOR_H
#include <array>

struct Vector {
    double x = 0;
    double y = 0;

    Vector() = default;
    Vector(double t_x, double t_y ): x(t_x), y(t_y){};

    // Binary operators
    Vector operator+ (const Vector &b ) const;
    Vector operator- (const Vector &b) const ;

    // Unary operators
    Vector normalize() const;
    double orientation() const; //radian
    Vector reflectX() const;
    Vector reflectY() const;

    // In place unary operators
    Vector rotate(double radian);
    Vector& operator+=(const Vector& b);
    Vector& operator*=(double k);

    std::array<double, 2 > asArray() const;

    // external operators overloads
    friend Vector operator*(const Vector v, double k);
    friend Vector operator*(double k, const Vector v);
    friend Vector operator/(const Vector v,double k);
};
// Binary operators
double det(const Vector &a, const Vector &b);
double scalar(const Vector &a, const Vector &b);
double distance(const Vector &a, const Vector &b);
// Unary operators
double norm(const Vector &v);


#endif //AQUARIUM_VECTOR_H
