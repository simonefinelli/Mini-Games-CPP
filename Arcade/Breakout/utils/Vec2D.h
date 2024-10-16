#ifndef VEC2D_LIB_H
#define VEC2D_LIB_H

#include <iostream>

class Vec2D {

public:
    static const Vec2D Zero;

    Vec2D() : Vec2D(0, 0) {}
    Vec2D(float x, float y) : x_coord(x), y_coord(y) {}

    inline void set_x(float x) { x_coord = x; }
    inline void set_y(float y) { y_coord = y; }
    inline float get_x() const { return x_coord; }
    inline float get_y() const { return y_coord; }

    // operator overloading
    friend std::ostream& operator<<(std::ostream& out, const Vec2D& vec);

private:
    float x_coord;
    float y_coord;
};

const Vec2D Vec2D::Zero;

std::ostream& operator<<(std::ostream& out, const Vec2D& vec) {
    out << "Vec(x,y): (" << vec.x_coord <<"," << vec.y_coord << ")";
    return out;
}

#endif // VEC2D_LIB_H