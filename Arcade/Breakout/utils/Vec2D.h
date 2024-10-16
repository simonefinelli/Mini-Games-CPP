#ifndef VEC2D_LIB_H
#define VEC2D_LIB_H

#include <iostream>

class Vec2D {
public:
    // static members ======================================================= //
    static const Vec2D Zero;
    // constructors ========================================================= //
    Vec2D() : Vec2D(0, 0) {}
    Vec2D(float x, float y) : x_coord(x), y_coord(y) {}
    // methods ============================================================== //
    inline void set_x(float x) { x_coord = x; }
    inline void set_y(float y) { y_coord = y; }
    inline float get_x() const { return x_coord; }
    inline float get_y() const { return y_coord; }

    float mag2() const;
    float mag() const;

    // operator overloading ================================================= //
    friend std::ostream& operator<<(std::ostream& out, const Vec2D& vec);
    bool operator==(const Vec2D& other_vec) const;
    bool operator!=(const Vec2D& other_vec) const;
    Vec2D operator-() const;
    Vec2D operator*(float scalar) const;  // vector * scalar 
    friend Vec2D operator*(float scalar, const Vec2D& vec);  // scalar * vector
    Vec2D operator/(float scalar) const;
    Vec2D& operator*=(float scalar);
    Vec2D& operator/=(float scalar);
    Vec2D operator+(const Vec2D& other_vec) const;
    Vec2D operator-(const Vec2D& other_vec) const;
    Vec2D& operator+=(const Vec2D& other_vec);
    Vec2D& operator-=(const Vec2D& other_vec);

private:
    float x_coord;
    float y_coord;
};

#endif // VEC2D_LIB_H