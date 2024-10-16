#include "Vec2D.h"

// static members - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
const Vec2D Vec2D::Zero;

// constructors - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

// operator overloading - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::ostream& operator<<(std::ostream& out, const Vec2D& vec) {
    out << "Vec(x,y): (" << vec.x_coord << "," << vec.y_coord << ")";
    return out;
}

// public interface - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// private interface - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -