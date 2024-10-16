#include "Vec2D.h"

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

/* ========================================================================== *
 * Public interface                                                           *
 * ========================================================================== */

/* ========================================================================== *
 * Private interface                                                           *
 * ========================================================================== */