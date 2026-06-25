#include "geometry/Vec2.h"
#include "geometry/Vec3.h"

#include <iostream>

int main() {

    // r1 = r10 + t*w
    // r2 = r20 + s*v


    geom::Vec3 r10 ( 1, 2, -1); 
    geom::Vec3 r20 ( 4, -1, 2);
    geom::Vec3 v1 ( 2, -1, 3);
    geom::Vec3 v2 ( 1, 1, -1);
    
    geom::Vec3 v_form_r10_to_r20 = r20 - r10;

    geom::Vec3 common_perpendicular = v1.cross(v2) /  (v1.cross(v2)).length() ;//Общий перпендикуляр, но еденичной длинны

    double distance_between_straight_lines = std::abs(common_perpendicular.dot(v_form_r10_to_r20));

    std::cout << v1.cross(v2) << "\n" << distance_between_straight_lines << "КОНЕЦ ВЫВОДА" << "\n";

    return 0;
}