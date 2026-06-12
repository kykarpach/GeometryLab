#include "geometry/Vec3.h"
#include "geometry/Epsilon.h"
#include <cmath>
namespace geom
{

Vec3::Vec3(): x_(0), y_(0), z_(0){}
Vec3::Vec3(double x, double y, double z): x_(x), y_(y), z_(z){}

double Vec3::x() const{
    return x_;
}
double Vec3::y() const{
    return y_;
}
double Vec3::z() const{
    return z_;
}

double Vec3::length() const{
    return std::sqrt(x_*x_ + y_*y_ + z_*z_);
}
double Vec3::length2() const{
    return (x_*x_ + y_*y_ + z_*z_);
}

double Vec3::dot(const Vec3& other) const{
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_; 
}

Vec3 Vec3::cross(const Vec3& other) const{
    
    if( ! (is_zero(length()) || is_zero(other.length()) )){
        return Vec3(y_*other.z_ - z_*other.y_,
         z_*other.x_ - x_*other.z_,
          x_*other.y_ - y_*other.x_);
    }
    
    throw std::invalid_argument("vector has a zero length");

}

Vec3 Vec3::normalized() const{
    if(is_zero(length())){
        throw std::invalid_argument("vector has zero length");
    }else{
        return Vec3(x_/length(), y_/length(), z_/length());
    }
}

double& Vec3::operator[](std::size_t index){
    if(index == 0){
        return x_;        
    }
    else if(index == 1){
        return y_;        
    }
    else if(index == 2){
        return z_;        
    }
    else{
        throw std::invalid_argument("Invalid index");
    }
}
const double& Vec3::operator[](std::size_t index) const{
    if(index == 0){
        return x_;        
    }
    else if(index == 1){
        return y_;        
    }
    else if(index == 2){
        return z_;        
    }
    else{
        throw std::invalid_argument("Invalid index");
    }
}

//Унарные + -
Vec3 Vec3::operator+()const{
    return Vec3(x_, y_, z_);
}
Vec3 Vec3::operator-()const{
    return Vec3(-x_, -y_, -z_);
}

Vec3 Vec3::operator+(const Vec3& other)const{
    return Vec3(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}
Vec3 Vec3::operator-(const Vec3& other)const{
    return Vec3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vec3 Vec3::operator*(double k) const{
    return Vec3(x_*k, y_*k, z_*k);
}
Vec3 Vec3::operator/(double k) const{
    return Vec3(x_/k, y_/k, z_/k);
}

Vec3& Vec3::operator+=(const Vec3& other){
    *this + other;
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& other){
    *this - other;
    return *this;
}

Vec3& Vec3::operator*=(double k){
    *this * k;
    return *this;
}
Vec3& Vec3::operator/=(double k){
    *this / k;
    return *this;
}

Vec3 operator*(double k, const Vec3& v){
    return v*k;
}

std::istream& operator>>(std::istream& in, Vec3& v){
    double x, y, z;
    
    if(in >> x >> y >> z){
        v = Vec3(x, y, z);
    }

    return in;
}
std::ostream& operator<<(std::ostream& out , const Vec3& v){

    out << "coordinat: " << v.x() << ", " << v.y() << ", " << v.z() << "}" << "\n";

    return out; 
}


}// namespace geom