#include "geometry/Distance.h"


namespace geom {


double distance(const Vec2& a, const Vec2& b){//Расстояние между двумя 2D-точками.
    return (a - b).length();
}
double distance(const Vec3& a, const Vec3& b){ //Расстояние между двумя 3D-точками.
    return (a - b).length();
}

//Минимальное расстояние от 2D-точки до 2D-отрезка.
//Именнно до отрезка, а не до прямой на который этот отрезок лежит
double distance_point_segment(const Vec2& p, const Segment2& s){
    // s - вырожденный в точку отрезок
    if(s.is_degenerate()){
        return distance(p, s.start());
    }
    else{

        Vec2 v0 = s.end() - s.start();
        Vec2 v1 = p - s.start();

        double t = v1.dot(v0)/v0.length2(); // длинна проэкции точки P на отрезок s, деленная на длинну s 
        // или t — доля пути от start до end, куда падает проекция точки p
        
        if(t < 0){
            return (p - s.start()).length();
        }
        else if (t > 1){
            return (p - s.end()).length();
        }
        else{

            Vec2 closest  =  t * v0 + s.start(); // Вектор от P до точки проэкции на отрезок s

            return (p - closest).length();
        }
    }

}

double distance_point_segment(const Vec3& p, const Segment3& s){

      // s - вырожденный в точку отрезок
    if(s.is_degenerate()){
        return distance(p, s.start());
    }
    else{

        Vec3 v0 = s.end() - s.start();
        Vec3 v1 = p - s.start();

        double t = v1.dot(v0)/v0.length2(); // длинна проэкции точки P на отрезок s, деленная на длинну s 
        // или t — доля пути от start до end, куда падает проекция точки p
        
        if(t < 0){
            return (p - s.start()).length();
        }
        else if (t > 1){
            return (p - s.end()).length();
        }
        else{

            Vec3 closest  =  t * v0 + s.start(); // Вектор от P до точки проэкции на отрезок s

            return (p - closest).length();
        }
    }
}








}// namespace geom