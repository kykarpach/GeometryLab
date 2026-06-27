#include <geometry/Polygon2.h>
#include <geometry/Segment2.h>


namespace geom{

Polygon2::Polygon2(const std::vector<Vec2>& vertices){
    if(vertices.size() < 3){
        throw std::invalid_argument("minmal vertices = 3");
    }
    for(auto i : vertices){
        vertices_.push_back(i);
    }
}

const std::vector<Vec2>& Polygon2::vertices() const{
    return vertices_;
}

std::size_t Polygon2::size() const{
    return vertices_.size();
}

bool Polygon2::empty() const{
    return vertices_.empty();
}

const Vec2& Polygon2::operator[](std::size_t index) const{
    return vertices_[index];
}

double Polygon2::perimeter() const{
    double answer = 0;
    for(size_t i = 1; i < size(); ++i){
        answer += (vertices_[i] - vertices_[i - 1]).length() ;
    }
    answer += (vertices_[size() - 1] - vertices_[0]).length();
    return answer;
}


// Формула Гаусса для многоугольника или формула "Шнурков"
double Polygon2::area() const {
    double sum = 0.0;

    for (std::size_t i = 0; i < size(); ++i) {
        std::size_t next = (i + 1) % size();
        sum += vertices_[i].cross(vertices_[next]);
    }

    return 0.5 * std::abs(sum);
}

// Минимальныая коробка полностю влючающая в себя фигуру Polygon2
AABB2 Polygon2::bounding_box() const {
    AABB2 box(vertices_[0], vertices_[0]);

    for (std::size_t i = 1; i < size(); ++i) {
        box.expand(vertices_[i]);
    }

    return box;
}


// Содержит ли фигура точку
bool Polygon2::contains_point(const Vec2& p) const {
    bool inside = false;

    for (std::size_t i = 0, j = size() - 1; i < size(); j = i++) {
        const Vec2& a = vertices_[i];
        const Vec2& b = vertices_[j];

        Segment2 edge(a, b);
        if (edge.contains_point(p)) {
            return true;
        }

        bool intersects_ray = (a.y() > p.y()) != (b.y() > p.y()); //p по высоте между a и b 

        if (intersects_ray) {
            //Это уравнение получется из условия пересечения горизонтальной прямой(проходящей через p)
            //И стороной a b - то есть мы смотрис на то где p, относительно ab? - справа\слева
            double x_intersection = (b.x() - a.x()) * (p.y() - a.y()) / (b.y() - a.y()) + a.x();//Находим x, где сторона пересекает горизонтальную линию через точку p.
            // Если пересечение справа от точки, значит наш луч(вектор точки p) вправо его задел.
            // ТОгда меняем состояние
            if (p.x() < x_intersection) {
                inside = !inside;
            }
        }
    }

    return inside;
}


}