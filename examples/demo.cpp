#include "geometry/Vec2.h"
#include "geometry/Vec3.h"

#include <iostream>

int main() {
    std::cout << "=== Vec2 demo ===\n";

    geom::Vec2 a2(3.0, 4.0);
    geom::Vec2 b2(1.0, 2.0);

    std::cout << "a2 = " << a2 << '\n';
    std::cout << "b2 = " << b2 << '\n';
    std::cout << "a2 + b2 = " << (a2 + b2) << '\n';
    std::cout << "dot(a2, b2) = " << a2.dot(b2) << '\n';
    std::cout << "cross(a2, b2) = " << a2.cross(b2) << '\n';
    std::cout << "length(a2) = " << a2.length() << '\n';
    std::cout << "normalized(a2) = " << a2.normalized() << '\n';

    std::cout << "\n=== Vec3 demo ===\n";

    geom::Vec3 a3(1.0, 0.0, 0.0);
    geom::Vec3 b3(0.0, 1.0, 0.0);
    geom::Vec3 c3(3.0, 4.0, 12.0);

    std::cout << "a3 = " << a3 << '\n';
    std::cout << "b3 = " << b3 << '\n';
    std::cout << "c3 = " << c3 << '\n';

    std::cout << "a3 + b3 = " << (a3 + b3) << '\n';
    std::cout << "dot(a3, b3) = " << a3.dot(b3) << '\n';
    std::cout << "cross(a3, b3) = " << a3.cross(b3) << '\n';

    std::cout << "length(c3) = " << c3.length() << '\n';
    std::cout << "normalized(c3) = " << c3.normalized() << '\n';

    std::cout << "\nEnter Vec3 as three numbers, example: 5 6 7\n";

    geom::Vec3 input3;

    if (std::cin >> input3) {
        std::cout << "You entered: " << input3 << '\n';
        std::cout << "input3 + c3 = " << (input3 + c3) << '\n';
        std::cout << "dot(input3, c3) = " << input3.dot(c3) << '\n';
        std::cout << "cross(input3, c3) = " << input3.cross(c3) << '\n';
    } else {
        std::cout << "Invalid input\n";
    }

    return 0;
}