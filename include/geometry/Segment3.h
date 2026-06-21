#pragma once

#include "geometry/Vec3.h"
#include "geometry/Epsilon.h"

namespace geom{

class Segment3{
public:

    Segment3();
    Segment3(const Vec3& start, const Vec3& end);

    const Vec3& start() const;
    const Vec3& end() const;

    Vec3 direction() const;
    double length() const;
    double length2() const;

    bool is_degenerate() const;
    bool contains_point(const Vec3& p) const;

private:
    Vec3 start_;
    Vec3 end_;
};
  
}// namespace geom