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

// Та же самоа функция, но для 3Д
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

//Минимальное расстояние от 3D-точки до прямой.
double distance_point_line(const Vec3& p, const Vec3& A0, const Vec3& A1){

    Vec3 va = A1 - A0;
    double va_length = va.length();


    if(is_zero(va_length)){
        throw std::invalid_argument("line is degenerate");
    }

    Vec3 w = A0 - p;//Вектор из точки на прямую (К точке A0)

    return   ( (w.cross(va)).length() ) / va_length;

}


// Две бесконечные прямые здаются точками
double distance_line_line(const Vec3& A0, const Vec3& A1, const Vec3& B0, const Vec3& B1){

    Vec3 va = A1 - A0;
    Vec3 vb = B1 - B0;

    double va_length = va.length();
    double vb_length = vb.length();

    if(is_zero(va_length) || is_zero(vb_length)){
        throw std::invalid_argument("line is degenirate");
    }

    Vec3 w = B0 - A0;

    if(is_zero( (va.cross(vb)).length() )){ // Условие параллельности
        return distance_point_line(A0, B0, B1);
    }


    return 0;

}

// То же самое но поменял местами аргументы

double distance_point_segment(const Segment2& s, const Vec2& p){
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

double distance_point_segment(const Segment3& s, const Vec3& p){

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