#include "geometry/Vec2.h"

#include <iostream>

int main() {
    geom::Vec2 a(3.0, 4.0);
    geom::Vec2 b(1.0, 2.0); 

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    std::cout << "a + b = " << (a + b) << '\n';

    std::cout << "dot(a, b) = " << a.dot(b) << '\n';
    std::cout << "cross(a, b) = " << a.cross(b) << '\n';

    std::cout << "length(a) = " << a.length() << '\n';
    std::cout << "a.x = " << a.x() << ", a.y = " << a.y() << '\n';
    std::cout << "a.length = " << a.length() << '\n';
    std::cout << "normalized(a) = " << a.normalized() << '\n';

    std::cout << "\nEnter vector as two numbers, example: 5 6\n";

    geom::Vec2 input;

    if (std::cin >> input) {
        std::cout << "You entered: " << input << '\n';
        std::cout << "input + a = " << (input + a) << '\n';
        std::cout << "dot(input, a) = " << input.dot(a) << '\n';
        std::cout << "cross(input, a) = " << input.cross(a) << '\n';
    } else {
        std::cout << "Invalid input\n";
    }

    return 0;
}