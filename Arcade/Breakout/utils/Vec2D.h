/**
 * @file Vec2D.h
 * @brief Small library to handle basic 2D point operations.
 * @author SimoX
 * @date 2024-10-16
 */

#ifndef VEC2D_LIB_H
#define VEC2D_LIB_H

#include <iostream>
#include <cassert>
#include <cmath>
#include "vec2D_utils.h"

/**
 * @brief A 2D vector class representing a point or a vector in 2D space.
 * 
 * This class provides various operations for working with 2D vectors such as
 * magnitude calculation, normalization, dot product, vector projection, rotation,
 * and reflection. It also supports common vector operations like addition, 
 * subtraction, scaling, and comparison through overloaded operators.
 */
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
    Vec2D get_unit_vec() const;
    Vec2D& normalize();
    float distance(const Vec2D& other_vec) const;
    float dot(const Vec2D& other_vec) const;
    Vec2D project_onto(const Vec2D& other_vec) const;
    float angle_between(const Vec2D& other_vec) const;
    Vec2D reflect(const Vec2D& normal_vec) const;
    void rotate(float alfa, const Vec2D& point=Vec2D(0,0));
    Vec2D rotation_result(float alfa, const Vec2D& point=Vec2D(0,0)) const;

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