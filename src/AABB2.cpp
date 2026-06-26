#include <geometry/AABB2.h>

namespace geom{


AABB2::AABB2(): min_(Vec2()), max_(Vec2()){}
AABB2::AABB2(const Vec2& min, const Vec2& max): min_(min), max_(max) {
    if(min.x() > max.x() || min.y() > max.y()) {//при этом min может быть равен max
        throw std::invalid_argument("max < min");
    }
}

const Vec2& AABB2::min() const{
    return min_;
}
const Vec2& AABB2::max() const{
    return max_;
}

double AABB2::width() const{
    return max_.x() - min_.x();
}
double AABB2::height() const{
    return max_.y() - min_.y();
}
double AABB2::area() const{
    return width() * height();
}

Vec2 AABB2::center() const{
    return min() + (0.5 * (max() - min()) );
}

bool AABB2::contains(const Vec2& p) const{
    return p.x() >= min().x() && p.x() <= max().x() && p.y() >= min().y() && p.y() <= max().y();
}
bool AABB2::intersects(const AABB2& other) const{
    // 1 полностью левее\парвее 2 или 1 полностью выше\ниже 2. Или и то и то.
    return !(max_.x() < other.min_.x() || other.max_.x() < min_.x() || max_.y() < other.min_.y() || other.max_.y() < min_.y());
}

void AABB2::expand(const Vec2& p){
    if(!(contains(p))){

        if(p.x() > max().x()){
            max_[0] = p.x();
        }
        if(p.y() > max().y()){
            max_[1] = p.y();
        }
        if(p.x() < min().x()){
            min_[0] = p.x();
        }
        if(p.y() < min().y()){
            min_[1] = p.y();
        }


    }
}


}