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

/* ========================================================================== *
 * Public interface                                                           *
 * ========================================================================== */

/* ========================================================================== *
 * Private interface                                                          *
 * ========================================================================== */