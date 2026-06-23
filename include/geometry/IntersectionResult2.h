#pragma once

#include "geometry/Vec2.h"
#include "geometry/Segment2.h"
#include <optional>

namespace geom {


// Показывает что возвращается при пересечении двух отрезков:
// Ничего 
// Точка
// Отрезок
enum class IntersectionType2 {// Перерчисление
    None,
    Point,
    Segment
};

// Показывает что взвращается (ничего точка отрезок)
// И выдает точку либо отрезок. Ничего выдать нельзя, вот это да...
// Результат пересечения двух 2D-отрезков.
// В зависимости от type используется только point или segment. 
struct IntersectionResult2 {

    IntersectionType2 type;
    std::optional<Vec2> point;
    std::optional<Segment2> segment;


    // // STATIC У ФНКУЦИИ ГОВОРИТ О ТОМ ЧТО ЕЁ МОЖНО ИСПОЛЬЗОВАТЬ НЕ ПРИМЕНЯЯ К ОБЪЕКТУ КЛАССА\СТРУКТУРЫ
    // То есть IntersectionResult2 result = IntersectionResult2::none();
    // А не /
    // IntersectionResult2 temp;
    // IntersectionResult2 result = temp.none();
    
    
    
    // Создает результат "пересечения нет".
    static IntersectionResult2 none();

    // Создает результат "пересечение в одной точке p".
    static IntersectionResult2 point_result(const Vec2& p);

    //  Создает результат "пересечение является отрезком s".
    static IntersectionResult2 segment_result(const Segment2& s);
};

}