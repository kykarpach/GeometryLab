#pragma once

#include "geometry/Polygon2.h"
#include "geometry/Vec2.h"
#include "geometry/Epsilon.h"

#include <vector>
#include <algorithm>

namespace geom {

    // Берёт набор точек.
    // Сортирует точки слева направо:
    // сначала по x, если x равны — по y.
    // Строит нижнюю часть оболочки.
    // Строит верхнюю часть оболочки.
    // Склеивает их в один контур.
    // Возвращает Polygon2.

// Алгоритм называется - Монотонная цепь Эндрю 
Polygon2 convex_hull(std::vector<Vec2> points);

} // namespace geom