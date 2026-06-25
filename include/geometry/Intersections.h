#pragma once

#include "geometry/Segment3.h"
#include "geometry/IntersectionResult3.h"
#include "geometry/Segment2.h"
#include "geometry/IntersectionResult2.h"
#include "geometry/Distance.h"

namespace geom {

IntersectionResult2 intersect(const Segment2& a, const Segment2& b);

IntersectionResult3 intersect(const Segment3& a, const Segment3& b);

}