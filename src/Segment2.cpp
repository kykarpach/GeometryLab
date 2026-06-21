#include "geometry/Segment2.h"

namespace geom{

Segment2::Segment2(): start_(), end_(){}
Segment2::Segment2(const Vec2& v1, const Vec2& v2): start_(v1), end_(v2){}

const Vec2& Segment2::start() const{
    return start_;
}
const Vec2& Segment2::end() const{
    return end_;
}

Vec2 Segment2::direction() const{
    return end_ - start_;
}

double Segment2::length() const{
    return ((*this).direction()).length();
}

double Segment2::length2() const{
    return ((*this).direction()).length2();
}

bool Segment2::is_degenerate() const{
    if(length() < EPS){
        return true;
    }else return false;
}

bool Segment2::contains_point(const Vec2& p) const{

    if(is_degenerate()){
        return ( is_zero(start_.x() - p.x()) &&  is_zero(start_.y() - p.y()) );
    }
    else{
        
        Vec2 v0 = start_ - end_;
        Vec2 v1 = start_ - p;
        
        if( ( is_zero(v0.cross(v1)) ) && ( v0.dot(v1) >= 0 ) && ( v0.dot(v1) <= v0.length2() ) ){
            return true;
        }else return false;
    }
}


}//namespace geom