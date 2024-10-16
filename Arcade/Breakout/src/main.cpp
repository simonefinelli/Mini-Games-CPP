#include <iostream>
#include "Vec2D.h"

int main() {
    Vec2D vec1;
    Vec2D vec2(2,1);

    std::cout << "Vector1:    " << vec1 << std::endl;
    std::cout << "VectorZero: " << Vec2D::Zero << std::endl;
    std::cout << "Vector2:    " << -vec2 << std::endl;

    auto new_v = vec2 * 3;
    new_v *= 2;
    std::cout << "Vector2 * 3 * 2: " << new_v << std::endl;

    auto new_v1 = 5 * vec1;
    std::cout << "5 * Vector1: " << new_v1 << std::endl;

    // new_v = vec2 / 0.000000003; // will crash (assertion raised)

    return 0;
}