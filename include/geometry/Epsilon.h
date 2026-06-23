#pragma once

#include <cmath>

namespace geom {


// constexpr - гарантия того, что значение вычисляется строго на этапе компиляции
constexpr double EPS = 1e-9;

// inline - деректива оптимизации, я так до конца и не пон, вроде как то оптимизирует код

inline bool is_zero(double value, double eps = EPS) {
    return std::abs(value) < eps;
}

inline bool nearly_equal(double a, double b, double eps = EPS) {
    return std::abs(a - b) < eps;
}

} // namespace geom