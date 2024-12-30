/**
 * @file Circle2D.h
 * @brief
 * @author SimoX
 * @date 2024-12-27
 */

#ifndef SHAPES_CIRCLE_2D_H
#define SHAPES_CIRCLE_2D_H

#include "Shape2D.h"
#include "Vec2D.h"

class Circle2D : public Shape2D {
public:
    // Constructors ========================================================= //     
    Circle2D();
    Circle2D(const Vec2D& center, float radius);

    // Instance methods ===================================================== //
    inline virtual Vec2D get_center_point() const override { return m_points[0]; }
    inline float get_radius () { return m_radius; }
    inline void set_radius(float radius) { m_radius = radius; }
    inline void move_to(const Vec2D& position) { m_points[0] = position; }

    bool intersects(const Circle2D& other_circle) const;
    bool contains_point(const Vec2D& point) const;

    // Operator overloading ================================================= //
private:
    // Instance variables =================================================== //
    float m_radius;
};

#endif // SHAPES_CIRCLE_2D_H