#include "geometry/Intersections.h"

namespace geom {

IntersectionResult2 intersect(const Segment2& a, const Segment2& b) {


    IntersectionResult2 result;

    Vec2 va = a.end() - a.start();
    Vec2 vb = b.end() - b.start();

    Vec2 w = b.start() - a.start(); // Вектор из начала первого отрезка в начало второго...

    // 1. Проверить вырожденные отрезки
    
    
    if(a.is_degenerate() && b.is_degenerate()){
        if( is_zero( ( a.start() - b.start() ).length() ) ) {
            result = IntersectionResult2::point_result(a.start());
        }else{
            result = IntersectionResult2::none();
        }
        return result;
    }
    if(a.is_degenerate()){
        // Если один отрезок вырожден  - он точка, смотрим пересечение этой точки со вторым отрезкомм
        if(is_zero(distance_point_segment(a.start(), b))){
            result = IntersectionResult2::point_result(a.start());
        }else{
            result = IntersectionResult2::none();  
        }
        return result;
    }
    if(b.is_degenerate()){
        // Если один отрезок вырожден  - он точка, смотрим пересечение этой точки со вторым отрезкомм
        if(is_zero(distance_point_segment(b.start(), a))){
            result = IntersectionResult2::point_result(b.start());
        }else{
            result = IntersectionResult2::none();  
        }
        return result;
    }

    // 2. Проверить непараллельные отрезки


    if (!is_zero(va.cross(vb))) {//Условие непрораллельности исходных отрезков

        double t = w.cross(vb) / va.cross(vb); //Выражения получаются из решения уравнение на пересечение
        double u = w.cross(va) / va.cross(vb); // a.start() + va * t = b.start() + vb * u || осталось домножить векторно

        if (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS) { // 0 < t < 1 и  0 < u < 1
            Vec2 point = a.start() + va * t;
            return IntersectionResult2::point_result(point);
        }

        return IntersectionResult2::none();
    }



    // 3. Проверить параллельные непересекающиеся

    if (is_zero(va.cross(vb))) {//Условие параллельности исходных отрезков
        if( !( is_zero(va.cross(w)) ) ){// случай когда отрезки лежат на разных паралл прямых
            return IntersectionResult2::none();
        }
        else{// случай когда отрезки лежат на одной прямой
            
            double t0 = (b.start() - a.start()).dot(va) / va.length2();// Где b.start() лежит оносително Va?
            double t1 = (b.end() - a.start()).dot(va) / va.length2();// Где b.утв() лежит оносително Va?
            
            if( -EPS <= t0 && t0 <= 1 + EPS ){
                
            }

            if( -EPS <= t1 && t1 <= 1 + EPS ){

            }

        }
            
    }





    // 4. Проверить наложение коллинеарных отрезков
    // 5. Вернуть IntersectionResult2::none / point_result / segment_result
}

}