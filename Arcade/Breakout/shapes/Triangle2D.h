/**
 * @file Trinagle.h
 * @brief 
 * @author SimoX
 * @date 2024-12-16
 */

#ifndef SHAPES_TRIANGLE_2D_H
#define SHAPES_TRIANGLE_2D_H

#include "Shape2D.h"

class Triangle2D : public Shape2D {
public:
    Triangle2D();
    Triangle2D(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

    inline void set_p0(const Vec2D& p0) {m_points[0] = p0;}
    inline void set_p1(const Vec2D& p1) {m_points[1] = p1;}
    inline void set_p2(const Vec2D& p2) {m_points[2] = p2;}

    inline Vec2D get_p0() const {return m_points[0];}
    inline Vec2D get_p1() const {return m_points[1];}
    inline Vec2D get_p2() const {return m_points[2];}

    virtual Vec2D get_center_point() const override;
    float area() const;
    bool contains_point(const Vec2D& p) const;

private:
    


};

#endif // SHAPES_TRIANGLE_2D_H