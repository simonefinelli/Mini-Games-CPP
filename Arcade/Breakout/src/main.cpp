#include <iostream>
#include "Vec2D.h"

int main() {
    Vec2D vec1;
    Vec2D vec2(8,1);

    std::cout << "Vector 1:    " << vec1 << std::endl;
    std::cout << "Vector Zero: " << Vec2D::Zero << std::endl;
    std::cout << "Vector 2:    " << -vec2 << std::endl;

    return 0;
}