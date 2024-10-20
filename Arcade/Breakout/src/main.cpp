#include <iostream>
#include "Vec2D.h"

int main() {
    Vec2D vec1;
    Vec2D vec2(2,1);

    std::cout << "Vector1:    " << vec1 << std::endl;
    std::cout << "VectorZero: " << Vec2D::ZERO << std::endl;
    std::cout << "Vector2:    " << -vec2 << std::endl;

    auto new_v = vec2 * 3;
    new_v *= 2;
    std::cout << "Vector2 * 3 * 2: " << new_v << std::endl;

    auto new_v1 = 5 * vec1;
    std::cout << "5 * Vector1: " << new_v1 << std::endl;

    // new_v = vec2 / 0.000000003; // will crash (assertion raised)

    Vec2D vec5(0.6,0.8);
    std::cout << "Magnitude " << vec5.mag2() << std::endl;
    std::cout << "Unit vector" << vec5.get_unit_vec() << std::endl;
    std::cout << "Normalization" << vec5.normalize() << std::endl;

    // distance
    Vec2D v6;
    Vec2D v7(-8,-7);
    std::cout << "Distance: " << v6.distance(v7) << std::endl;

    // projection
    Vec2D v8(1,0);
    Vec2D other(3,4);
    Vec2D projection = v8.project_onto(other);
    std::cout << "Projection: " << projection << std::endl;

    // angle
    std::cout << "Angle (radiants): " << v8.angle_between(other) << std::endl;

    // rotation
    Vec2D v9(2,3);
    Vec2D point(1,1);
    float alfa = 45; // degrees
    float alfa_rad = alfa * (M_PI / 180.0f); // radiants
    v9.rotate(alfa_rad, point);
    std::cout << "Rotated angle by +45 degrees: " << v9 << std::endl;

    return 0;
}