#include "C:\Users\777\Desktop\Proga\C++\GeometryLab\include\geometry\Vec2.h"
#include <iostream>

namespace geom {


    Vec2(): x_(0), y_(0) {}
    Vec2(double x, double y): x_(x), y_(y) {}

    double x()const{
        return x_;
    }
    double y()const{
        return y_;
    }

    double length() const{
        return sqrt(x_*x_ + y_*y_);
    }
    double length2() const{
        return x_*x_ + y_*y_;
    }

    Vec2 normalized() const{
        Vec2 answ (x_/length(), y_/length()); // дописать проверку что длинна не ноль
        return answ;
    }

    double dot(const Vec2& other) const{
        return x_ * (other.x_) + y_ * (other.y_) ;
    }

    double cross(const Vec2& other) const{
        return x_*(other.y_) - y_*(other.x_);
    }

    // потом реализовать поведение в слуяае некорректного идекса
    const double& operator []  (std::size_t index) const{
  
        if(index == 0){
            return x_;
        }
        if(index == 1){
            return y_;
        }
    }
     // потом реализовать поведение в слуяае некорректного идекса
    double& operator [] (std::size_t index) {

        if(index == 0){
            return x_;
        }
        if(index == 1){
            return y_;
        }
    }

    //  Унарныые +  b -
    Vec2 operator+() const{
        Vec2 answ = *this; //Через конструктор копирования а не через конструктор
        return answ;
    }
    Vec2 operator-() const{
        Vec2 answ = -(*this);//Через конструктор копирования а не через конструктор
        return answ;
    }
    //----------------------------

    Vec2& operator+=(const Vec2& other){
        x_ += other.x();
        y_ += other.y();
        return *this;
    }
    Vec2& operator-=(const Vec2& other){
        x_ -= other.x();
        y_ -= other.y();
        return *this;
    }

    Vec2& operator*=(double k){
        x_*=k;
        y_*=k;
        return *this;
    }
    Vec2& operator/=(double k){
        x_/=k;
        y_/=k;
        return *this;
    }



    // Бинарные------------------
    Vec2 operator + (const Vec2& v1, const Vec2& v2){
        Vec2 answ(v1.x() + v2.x(), v1.y() + v2.y());
        return answ;
    }
    Vec2 operator - (const Vec2& v1, const Vec2& v2){
        Vec2 answ(v1.x() - v2.x(), v1.y() - v2.y());
        return answ;
    }

    Vec2 operator*(const Vec2& v, double k){
        Vec2 answ (v.x()*k, v.y()*k);
        return answ;
    }
    Vec2 operator*(double k, const Vec2& v){
        Vec2 answ (v.x()*k, v.y()*k);
        return answ;
    }

    Vec2 operator/(const Vec2& v, double k){
        Vec2 answ (v.x()/k, v.y()/k);
        return answ;
    }
    Vec2 operator/(double k, const Vec2& v){
        Vec2 answ (v.x()/k, v.y()/k);
        return answ;
    }
    //----------------------------

    //Операторы ВВОДА и ВЫВОДА

    std::istream& operator >> (std::istream& in, Vec2& v){
        double x, y;
        char dummy;

        in >> x >> dummy;
        in >> y >> dummy;

        v = Vec2(x, y);

        return in;
    };
    std::ostream& operator << (std::ostream& out, const Vec2& v){

        out << "coordinate: (" << v.x() << ", " << v.y() << ") \n"; 

        return out;
    };

};