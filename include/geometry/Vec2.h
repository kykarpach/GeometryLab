#pragma once

#include <cstddef>
#include <iostream>

namespace geom {

class Vec2 {
private:
    double x_;
    double y_;

public:
    Vec2();//
    Vec2(double x, double y);//

    double x() const;//
    double y() const;//

    double length() const;//
    double length2() const;//

    double dot(const Vec2& other) const;//
    double cross(const Vec2& other) const; // Вектороное произведение. Но позвращает только z, тк x=0 y=0

    Vec2 normalized() const; // Возвращает вектор отой направленности но длинны 1

    double& operator[](std::size_t index);//
    const double& operator[](std::size_t index) const;//

    Vec2 operator+() const;//
    Vec2 operator-() const;//

    Vec2& operator+=(const Vec2& other);//
    Vec2& operator-=(const Vec2& other);//
    Vec2& operator*=(double k);//
    Vec2& operator/=(double k);//


};

Vec2 operator + (const Vec2& v1, const Vec2& v2);//
Vec2 operator - (const Vec2& v1, const Vec2& v2);//

Vec2 operator*(const Vec2& v, double k);//
Vec2 operator*(double k, const Vec2& v);//

Vec2 operator/(const Vec2& v, double k);//

std::ostream& operator<<(std::ostream& os, const Vec2& v);
std::istream& operator>>(std::istream& is, Vec2& v);

} // namespace geom