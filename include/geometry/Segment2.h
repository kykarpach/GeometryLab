#pragma once

#include "geometry/Vec2.h"
#include "geometry/Epsilon.h"

namespace geom{

class Segment2{
public:

    Segment2();
    Segment2(const Vec2& start, const Vec2& end);

    const Vec2& start() const;
    const Vec2& end() const;

    Vec2 direction() const;
    double length() const;
    double length2() const;

    bool is_degenerate() const; 
    bool contains_point(const Vec2& p) const;
private:
    Vec2 start_;
    Vec2 end_;
};
  
}// namespace geom