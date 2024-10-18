#include <cassert>
#include <cmath>
#include "Vec2D.h"
#include "vec2D_utils.h"

// ========================================================================== //
// Static members                                                             //
// ========================================================================== //
const Vec2D Vec2D::Zero;


// ========================================================================== //
// Constructors                                                               //
// ========================================================================== //


// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Class methods ============================================================ //

/**
 * Square of the magnitude of a vector
 */
float Vec2D::mag2() const {
    return dot(*this);
}

/**
 * Magnitured of a vector
 */
float Vec2D::mag() const {
    return sqrtf(mag2());
}

/**
 * get a new normalized vector (unit vector) starting from current vector.
 */
Vec2D Vec2D::get_unit_vec() const {
    float magnitude = mag();

    if (magnitude > EPSILON)
        return *this / magnitude;
    else
        return Vec2D::Zero;
}

/**
 * normalize the vector to obtain the unit vector.
 */
Vec2D& Vec2D::normalize() {
    float magnitude = mag();

    if (magnitude > EPSILON)
        return *this /= magnitude;
    else
        return *this;
}

/**
 * 
 */
float Vec2D::distance(const Vec2D& other_vec) const {
    return (*this - other_vec).mag();
}

/**
 * 
 */
float Vec2D::dot(const Vec2D& other_vec) const {
    return x_coord * other_vec.x_coord + y_coord * other_vec.y_coord;
}

/**
 * 
 */
Vec2D Vec2D::project_onto(const Vec2D& other_vec) const {
    // retrive 
    Vec2D other_unit_vec = other_vec.get_unit_vec();

    // calculate the projection
    float dot_result = dot(other_unit_vec);
    return other_unit_vec * dot_result;
}


// Operator overloading  ==================================================== //
std::ostream& operator<<(std::ostream& out, const Vec2D& vec) {
    out << "Vec(x,y): (" << vec.x_coord << "," << vec.y_coord << ")";
    return out;
}

bool Vec2D::operator==(const Vec2D& other_vec) const {
    return is_equal(x_coord, other_vec.x_coord) and is_equal(y_coord, other_vec.y_coord);
}

bool Vec2D::operator!=(const Vec2D& other_vec) const {
    return !(*this == other_vec);
}

Vec2D Vec2D::operator-() const {
    return Vec2D(-x_coord, -y_coord);
}

Vec2D Vec2D::operator*(float scalar) const {
    return Vec2D(scalar * x_coord, scalar * y_coord);
}

Vec2D operator*(float scalar, const Vec2D& vec) {
    return vec * scalar;
}

Vec2D Vec2D::operator/(float scalar) const {
    assert(fabsf(scalar) > EPSILON);
    return Vec2D(x_coord / scalar, y_coord / scalar);
}

Vec2D& Vec2D::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

Vec2D& Vec2D::operator/=(float scalar) {
    assert(fabsf(scalar) > EPSILON);
    *this = *this / scalar;
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D& other_vec) const {
    return Vec2D(x_coord + other_vec.x_coord, y_coord + other_vec.y_coord);
}

Vec2D Vec2D::operator-(const Vec2D& other_vec) const {
    return Vec2D(x_coord - other_vec.x_coord, y_coord - other_vec.y_coord);
}

Vec2D& Vec2D::operator+=(const Vec2D& other_vec) {
    *this = *this + other_vec;
    return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& other_vec) {
    *this = *this - other_vec;
    return *this;
}


// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //