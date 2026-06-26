#pragma once

#include "geometry/AABB2.h"
#include "geometry/Vec2.h"

#include <cstddef>
#include <vector>

namespace geom {

class Polygon2 {
public:

    explicit Polygon2(const std::vector<Vec2>& vertices);

    std::size_t size() const;
    bool empty() const;

    const Vec2& operator[](std::size_t index) const;

    double perimeter() const;
    double area() const;

    AABB2 bounding_box() const;

    bool contains_point(const Vec2& p) const;

private:
    std::vector<Vec2> vertices_;
};

} // namespace geom