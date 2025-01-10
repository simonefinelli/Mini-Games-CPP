/**
 * @file Line2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-08
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