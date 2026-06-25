#include "geometry/Intersections.h"
#include <algorithm>

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
    // 4. Проверить наложение коллинеарных отрезков

    if (is_zero(va.cross(vb))) {//Условие параллельности исходных отрезков
        if( !( is_zero(va.cross(w)) ) ){// случай когда отрезки лежат на разных паралл прямых
            return IntersectionResult2::none();
        }
        else{// случай когда отрезки лежат на одной прямой
            
            double t0 = (b.start() - a.start()).dot(va) / va.length2();// Где b.start() лежит оносително Va?
            double t1 = (b.end() - a.start()).dot(va) / va.length2();// Где b.утв() лежит оносително Va?
            
            double b_min = std::min(t0, t1); // дают понимания как b ориентирован относительно
            double b_max = std::max(t0, t1); //                                        a.start()

            //начало и конец пересечения отрезков a и b 
            double left = std::max(b_min, 0.0);
            double right = std::min(b_max, 1.0);

            if(left > right + EPS){//Пересечений нет - начло больше конца
                return IntersectionResult2::none();
            }

            if( is_zero(left - right) ){
                return IntersectionResult2::point_result (a.start() + va * left);
            }

            return IntersectionResult2::segment_result(Segment2 (a.start() + va * left, a.start() + va * right ));
            
        }
    }

    return IntersectionResult2::none();

}

IntersectionResult3 intersect(const Segment3& a, const Segment3& b) {

    // 1. Оба отрезка вырождены в точку
    // 2. Один из отрезков вырожден в точку
    // 3. Отрезки паралльны друг другу и лежат на разных прямых
    // 4. Отрезки паралльны друг другу и лежат на одной прямой - (перекрываются или не перекрываются)
    // 5. Орезки не параллельны - (пересекаются или не пересекаются в точке)

    Vec3 va = a.end() - a.start();
    Vec3 vb = b.end() - b.start();

    Vec3 w = b.start() - a.start();

    // Вырожденны оба либо один из
    if(a.is_degenerate() && b.is_degenerate()){
        if( is_zero( (a.start() - b.start()).length() ) ){
            return IntersectionResult3::point_result(a.start());
        }
        return IntersectionResult3::none();
    }

    if(a.is_degenerate()){
        if( is_zero( distance_point_segment(a.start(), b) ) ){
            return IntersectionResult3::point_result(a.start());
        }
        return IntersectionResult3::none();
    }

    if(b.is_degenerate()){
        if( is_zero( distance_point_segment(b.start(), a) ) ){
            return IntersectionResult3::point_result(b.start());
        }
        return IntersectionResult3::none();
    }

    //Условие на параллельность отрезков
    if( is_zero( ((va.cross(vb)).length()) ) ){ 
        if( is_zero( ((w.cross(va)).length()) ) ){ //Условие на то, что отрезки ЛЕЖАТ на одной прямой
           
            
            double t0 = (b.start() - a.start()).dot(va) / va.length2();// Где b.start() лежит оносително Va?
            double t1 = (b.end() - a.start()).dot(va) / va.length2();// Где b.утв() лежит оносително Va?
            
            double b_min = std::min(t0, t1); // дают понимания как b ориентирован относительно
            double b_max = std::max(t0, t1); //                                        a.start()

            //начало и конец пересечения отрезков a и b 
            double left = std::max(b_min, 0.0);
            double right = std::min(b_max, 1.0);

            if(left > right + EPS){//Пересечений нет - начло больше конца
                return IntersectionResult3::none();
            }

            if( is_zero(left - right) ){
                return IntersectionResult3::point_result (a.start() + va * left);
            }

            return IntersectionResult3::segment_result(Segment3 (a.start() + va * left, a.start() + va * right ));
            
        }
        return IntersectionResult3::none();
    }

    // Тут рассмотрен енпаралельный случай


    double Va_length2 = va.length2();
    double dot_va_vb = va.dot(vb);
    double Vb_length2 = vb.length2();

    double dot_w_va = va.dot(w);
    double dot_w_vb = vb.dot(w);

    double denom = Va_length2 * Vb_length2 - dot_va_vb * dot_va_vb;

    if (is_zero(denom)) {
        return IntersectionResult3::none();
    }

    double t = (Vb_length2 * dot_w_va - dot_va_vb * dot_w_vb) / denom;
    double s = (dot_va_vb * dot_w_va - Va_length2 * dot_w_vb) / denom;

    if (t < -EPS || t > 1.0 + EPS || s < -EPS || s > 1.0 + EPS) {
        return IntersectionResult3::none();
    }

    Vec3 point_a = a.start() + va * t;
    Vec3 point_b = b.start() + vb * s;

    if (!is_zero((point_a - point_b).length())) {
        return IntersectionResult3::none();
    }

    return IntersectionResult3::point_result(point_a);

}

}