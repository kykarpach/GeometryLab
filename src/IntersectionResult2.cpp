#include "geometry/IntersectionResult2.h"

namespace geom {

IntersectionResult2 IntersectionResult2::none() {
    IntersectionResult2 result;
    result.type = IntersectionType2::None;
    return result;
}

IntersectionResult2 IntersectionResult2::point_result(const Vec2& p) {
    IntersectionResult2 result;
    result.type = IntersectionType2::Point;
    result.point = p;
    return result;
}

IntersectionResult2 IntersectionResult2::segment_result(const Segment2& s) {
    IntersectionResult2 result;
    result.type = IntersectionType2::Segment;
    result.segment = s;
    return result;
}

}