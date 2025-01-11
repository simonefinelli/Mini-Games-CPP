#include <iostream>

#include "Circle2D.h"
#include "Line2D.h"
#include "Rectangle2D.h"
#include "Triangle2D.h"

int main() {
    Circle2D c{Vec2D(50, 50), 50};
    Rectangle2D r{Vec2D(100, 100), 50, 25};
    Triangle2D t{Vec2D(50, 50), Vec2D(50, 50), Vec2D(50, 50)};
    Line2D l{Vec2D(0, 0), Vec2D(0,1)};

    std::cout << c.get_points()[0] << std::endl;
    std::cout << r.get_points()[0] << std::endl;
    std::cout << t.get_points()[0] << std::endl;
    std::cout << l.get_p0() << std::endl;


    return 0;
}