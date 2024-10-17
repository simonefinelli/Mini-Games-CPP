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

    Vec2D vec5(5,2);
    std::cout << "Unit vector" << vec5.get_norm_vec() << std::endl;
    std::cout << "Normalization" << vec5.normalize() << std::endl;

    // distance

    Vec2D v6;
    Vec2D v7(-8,-7);
    std::cout << "Distance: " << v6.Distance(v7) << std::endl;


    return 0;
}