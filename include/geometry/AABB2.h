#pragma once

#include "geometry/Vec2.h"

namespace geom {

class AABB2 {
public:
    AABB2();
    AABB2(const Vec2& min, const Vec2& max);

    const Vec2& min() const;
    const Vec2& max() const;

    double width() const;
    double height() const;
    double area() const;

    Vec2 center() const;

    bool contains(const Vec2& p) const;
    bool intersects(const AABB2& other) const;

    void expand(const Vec2& p);

private:
    // max_ - Правый верхний угол
    // min_ - левый нижний угол
    Vec2 min_;
    Vec2 max_;
};

} // namespace geom