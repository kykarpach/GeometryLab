#include "geometry/Segment3.h"


namespace geom{

Segment3::Segment3(){}
Segment3::Segment3(const Vec3& v1, const Vec3& v2): start_(v1), end_(v2) {}

const Vec3& Segment3::start() const{
    return start_;
}
const Vec3& Segment3::end() const{
    return end_;
}

Vec3 Segment3::direction() const{
    return end_ - start_;
}
double Segment3::length() const{
    return direction().length();
}
double Segment3::length2() const{
    return direction().length2();
}

bool Segment3::is_degenerate() const{
    return is_zero(length());
}

bool Segment3::contains_point(const Vec3& p) const{
    if(is_degenerate()){
        return is_zero( start_.x() - p.x() ) && is_zero( start_.y() - p.y() ) && is_zero( start_.z() - p.z() );
    }
    else{

        Vec3 v0 = direction();
        Vec3 v1 = p - start_;

        if(is_zero( (v0.cross(v1)).length() ) && ( v0.dot(v1) >= -EPS ) && ( v0.dot(v1) <= v0.length2() + EPS )){
            return true;
        }else return false;

    }
}


}//namespace geom