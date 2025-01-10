/**
 * @file Line2D.h
 * 
 * @class Line2D
 * @brief Implementation of the Line2D class for representing and manipulating 2D lines.
 * 
 * This file contains the implementation of the Line2D class, which provides methods for
 * creating and manipulating 2D lines. The class includes constructors for initializing
 * lines with specific endpoints, as well as methods for calculating the closest point
 * on the line to a given point, the minimum distance from a point to the line, the slope
 * of the line, the midpoint of the line, and the length of the line. Additionally, the
 * class supports equality comparison between two Line2D objects.
 * 
 * The Line2D class relies on the Vec2D class for representing 2D points and vectors.
 * 
 * @note This implementation assumes the existence of a Vec2D class with appropriate
 *       methods for vector arithmetic, distance calculation, and other vector operations.
 * 
 * @see Line2D.cpp for the class definition and detailed documentation of each method.
 * 
 * @section Example
 * @code
 * Vec2D point1(0, 0);
 * Vec2D point2(3, 4);
 * Line2D line(point1, point2);
 * @endcode
 * 
 * @date 2024-12-08
 * @author SimoX
 */
#ifndef SHAPES_LINE_2D_H
#define SHAPES_LINE_2D_H

#include <cmath>
#include "Vec2D.h"

class Line2D {
public:
    // Constructors ========================================================= //     
    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vec2D& p0, const Vec2D& p1);

    // Instance methods ===================================================== //
    inline const Vec2D& get_p0() const {return m_p0;}
    inline const Vec2D& get_p1() const {return m_p1;}

    inline void set_p0(const Vec2D& p0) {m_p0 = p0;}
    inline void set_p1(const Vec2D& p1) {m_p1 = p1;}

    Vec2D closest_point(const Vec2D& p, bool limit_to_segment=false) const;
    float min_distance_from(const Vec2D& other_p, bool limit_to_segment=false) const;

    float slope() const;
    Vec2D mid_point() const;
    float length() const;

    // Operator overloading ================================================= //
    bool operator==(const Line2D& other_line) const;
private:
    // Instance variables =================================================== //
    Vec2D m_p0;
    Vec2D m_p1;
};

#endif // SHAPES_LINE_2D_H