// main.cpp
#include <iostream>
#include <cassert>
#include "Vec2D.h"

int main() {
    // Create two vectors
    Vec2D vec1(3.0f, 4.0f);
    Vec2D vec2(1.0f, 2.0f);

    // Display the original vectors
    std::cout << "Vector 1: (" << vec1.get_x() << ", " << vec1.get_y() << ")\n";
    std::cout << "Vector 2: (" << vec2.get_x() << ", " << vec2.get_y() << ")\n";

    return 0;
}
