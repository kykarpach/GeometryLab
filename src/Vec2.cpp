#include "geometry/Vec2.h"
#include "geometry/Epsilon.h"
#include <iostream>
#include <cmath>
#include <stdexcept>


namespace geom {

// Конструкторы
Vec2::Vec2(): x_(0), y_(0) {}
Vec2::Vec2(double x, double y): x_(x), y_(y) {}

double Vec2::x() const {
    return x_;
}
double Vec2::y() const {
    return y_;
}

//Длинна отрезка
double Vec2::length() const {
    return std::sqrt(x_ * x_ + y_ * y_);
}
//Длинна отрезка в квадрате
double Vec2::length2() const {
    return x_ * x_ + y_ * y_;
}
//коллинеарный вектор но единичный
Vec2 Vec2::normalized() const {
    if( ! ( is_zero(length()) )){// Длинна не ноль? - да, не ноль, работаем
        Vec2 answ(x_ / length(), y_ / length());
        return answ;
    }
    throw std::invalid_argument("vector has zero length");
}
//скалярное произведение
double Vec2::dot(const Vec2& other) const {
    return x_ * (other.x_) + y_ * (other.y_);
}
//векторное произведение
double Vec2::cross(const Vec2& other) const {
    return x_ * (other.y_) - y_ * (other.x_);
}


const double& Vec2::operator[](std::size_t index) const {
    if (index == 0) {
        return x_;
    }
    if (index == 1) {
        return y_;
    }
    throw std::out_of_range("Vec2 index out of range");
}
double& Vec2::operator[](std::size_t index) {
    if (index == 0) {
        return x_;
    }

    if (index == 1) {
        return y_;
    }
    
    throw std::out_of_range("Vec2 index out of range");
}

// Унарные + и -
Vec2 Vec2::operator+() const {
    Vec2 answ = *this;
    return answ;
}
Vec2 Vec2::operator-() const {
    Vec2 answ (-x_, -y_);
    return answ;
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x_ += other.x();
    y_ += other.y();
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& other) {
    x_ -= other.x();
    y_ -= other.y();
    return *this;
}

Vec2& Vec2::operator*=(double k) {
    x_ *= k;
    y_ *= k;
    return *this;
}
Vec2& Vec2::operator/=(double k) {
    if (!(is_zero(k))){
        x_ /= k;
        y_ /= k;
        return *this;
    }
    throw std::invalid_argument("you can't divide by zero");
}

// Бинарные
Vec2 operator+(const Vec2& v1, const Vec2& v2) {
    Vec2 answ(v1.x() + v2.x(), v1.y() + v2.y());
    return answ;
}
Vec2 operator-(const Vec2& v1, const Vec2& v2) {
    Vec2 answ(v1.x() - v2.x(), v1.y() - v2.y());
    return answ;
}

Vec2 operator*(const Vec2& v, double k) {
    Vec2 answ(v.x() * k, v.y() * k);
    return answ;
}
Vec2 operator*(double k, const Vec2& v) {
    Vec2 answ(v.x() * k, v.y() * k);
    return answ;
}

Vec2 operator/(const Vec2& v, double k){
    if(!(is_zero(k))){
        Vec2 answ(v.x() / k, v.y() / k);
        return answ;
    }
    throw std::invalid_argument("you can't divide by zero");
}

// Операторы ввода и вывода
std::istream& operator>>(std::istream& in, Vec2& v) {
    double x;
    double y;

    if (in >> x >> y) {
        v = Vec2(x, y);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    out << "coordinate: (" << v.x() << ", " << v.y() << ") \n";
    return out;
}

} // namespace geom