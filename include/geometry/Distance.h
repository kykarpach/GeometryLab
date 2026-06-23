#pragma once

#include "geometry/Vec2.h"
#include "geometry/Vec3.h"
#include "geometry/Segment2.h"
#include "geometry/Segment3.h"

namespace geom {

double distance(const Vec2& a, const Vec2& b);
double distance(const Vec3& a, const Vec3& b);

double distance_point_segment(const Vec2& p, const Segment2& s);
double distance_point_segment(const Vec3& p, const Segment3& s);

}