#ifndef VEC2D_LIB_H
#define VEC2D_LIB_H

#include <iostream>

class Vec2D {
public:
    // static members
    static const Vec2D Zero;
    // constructors
    Vec2D() : Vec2D(0, 0) {}
    Vec2D(float x, float y) : x_coord(x), y_coord(y) {}
    // methods
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

#endif // VEC2D_LIB_H