#pragma once

#include "geometry/Segment2.h"
#include "geometry/IntersectionResult2.h"
#include "geometry/Distance.h"

namespace geom {

IntersectionResult2 intersect(const Segment2& a, const Segment2& b);

}