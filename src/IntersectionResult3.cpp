#include "geometry/IntersectionResult3.h"

namespace geom {

IntersectionResult3 IntersectionResult3::none() {
    IntersectionResult3 result;
    result.type = IntersectionType3::None;
    return result;
}

IntersectionResult3 IntersectionResult3::point_result(const Vec3& p) {
    IntersectionResult3 result;
    result.type = IntersectionType3::Point;
    result.point = p;
    return result;
}

IntersectionResult3 IntersectionResult3::segment_result(const Segment3& s) {
    IntersectionResult3 result;
    result.type = IntersectionType3::Segment;
    result.segment = s;
    return result;
}

}