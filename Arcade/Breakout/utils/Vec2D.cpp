#include <cassert>
#include <cmath>
#include "Vec2D.h"
#include "vec2D_utils.h"

/* ========================================================================== *
 * Static members                                                             *
 * ========================================================================== */
const Vec2D Vec2D::Zero;

/* ========================================================================== *
 * Constructors                                                               *
 * ========================================================================== */ 

/* ========================================================================== *
 * Operator overloading                                                       *
 * ========================================================================== */

/* Friend functions ========================================================= */
std::ostream& operator<<(std::ostream& out, const Vec2D& vec) {
    out << "Vec(x,y): (" << vec.x_coord << "," << vec.y_coord << ")";
    return out;
}

Vec2D operator*(float scalar, const Vec2D& vec) {
    return vec * scalar;
}

/* Class methods ============================================================ */

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

Vec2D Vec2D::operator/(float scalar) const {
    assert(fabsf(scalar) > EPSILON);
    return Vec2D(scalar / x_coord, scalar / y_coord);
}

Vec2D& Vec2D::operator*=(float scalar) {
    *this = (*this) * scalar;
    return *this;
}

Vec2D& Vec2D::operator/=(float scalar) {
    assert(fabsf(scalar) > EPSILON);
    *this = (*this) / scalar;
    return *this;
}

/* ========================================================================== *
 * Public interface                                                           *
 * ========================================================================== */

/* ========================================================================== *
 * Private interface                                                          *
 * ========================================================================== */