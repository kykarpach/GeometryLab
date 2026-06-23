#pragma once

#include "geometry/Vec3.h"
#include "geometry/Segment3.h"
#include <optional>

namespace geom {

// Тип пересечения двух 3D-отрезков.
enum class IntersectionType3 {
    None,    // Пересечения нет.
    Point,   // Отрезки пересекаются в одной точке.
    Segment  // Отрезки накладываются друг на друга по отрезку.
};

// Результат пересечения двух 3D-отрезков.
// В зависимости от type используется только point или segment.
struct IntersectionResult3 {
    IntersectionType3 type;
    std::optional<Vec3> point;
    std::optional<Segment3> segment;

    // Статические методы-создатели.
    // Вызываются через IntersectionResult3::none(), без заранее созданного объекта.
    // Нужны, чтобы удобно создавать разные варианты результата пересечения.
    static IntersectionResult3 none();
    static IntersectionResult3 point_result(const Vec3& p);
    static IntersectionResult3 segment_result(const Segment3& s);
};

}