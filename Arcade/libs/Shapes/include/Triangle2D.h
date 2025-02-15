/**
 * @file Triangle2D.cpp
 * @brief Implementation of the Triangle2D class for representing and manipulating 2D triangles.
 * 
 * This file contains the implementation of the Triangle2D class, which provides methods
 * for constructing triangles, calculating their centroids, areas, and checking if a point
 * lies within the triangle.
 * 
 * The Triangle2D class uses the Vec2D class to represent 2D points.
 * 
 * @see Rectangle2D.cpp for the class definition and detailed documentation of each method.
 * 
 * @section Example
 * @code
 * Vec2D p0(0, 10);
 * Vec2D p1(10, 20);
 * Vec2D p2(0, 50);
 * Triangle2D t(p0, p1, p2);
 * @endcode
 * 
 * @date 2024-12-16
 * @author SimoX
 */

#ifndef SHAPES_TRIANGLE_2D_H
#define SHAPES_TRIANGLE_2D_H

#include "Shape2D.h"

class Triangle2D : public Shape2D {
public:
    // Constructors ========================================================= //     
    Triangle2D();
    Triangle2D(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

    // Instance methods ===================================================== //
    inline Vec2D get_p0() const {return m_points[0];}
    inline Vec2D get_p1() const {return m_points[1];}
    inline Vec2D get_p2() const {return m_points[2];}
    
    inline void set_p0(const Vec2D& p0) {m_points[0] = p0;}
    inline void set_p1(const Vec2D& p1) {m_points[1] = p1;}
    inline void set_p2(const Vec2D& p2) {m_points[2] = p2;}

    virtual Vec2D get_center_point() const override;
    float area() const;
    bool contains_point(const Vec2D& p) const;
    void move_to(const Vec2D& p) override;

private:
    // Instance methods ===================================================== //
    float area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;
};

#endif // SHAPES_TRIANGLE_2D_H