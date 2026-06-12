#pragma once

#include <cstddef>
#include <iostream>
#include <cmath>
namespace geom {

class Vec3 {
public:
    Vec3();
    Vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    double length() const;
    double length2() const;

    double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;

    Vec3 normalized() const;

    double& operator[](std::size_t index);
    const double& operator[](std::size_t index) const;

    Vec3 operator+() const;
    Vec3 operator-() const;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;

    Vec3 operator*(double k) const;
    Vec3 operator/(double k) const;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(double k);
    Vec3& operator/=(double k);

private:
    double x_;
    double y_;
    double z_;
};

Vec3 operator*(double k, const Vec3& v);

std::ostream& operator<<(std::ostream& os, const Vec3& v);
std::istream& operator>>(std::istream& is, Vec3& v);

} // namespace geom