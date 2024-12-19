/**
 * @file Triangle.cpp
 * @brief 
 * @author SimoX
 * @date 2024-12-16
 */

#include <cmath>

#include "Triangle2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //     
Triangle2D::Triangle2D() : Triangle2D(Vec2D::ZERO, Vec2D::ZERO, Vec2D::ZERO) {}

Triangle2D::Triangle2D(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) {
    m_points.push_back(p0);
    m_points.push_back(p1);
    m_points.push_back(p2);
}

// Instance methods ========================================================= //
Vec2D Triangle2D::get_center_point() const {
    float x_centroid = (m_points[0].get_x() + m_points[1].get_x() + m_points[2].get_x()) / 3.0f;
    float y_centroid = (m_points[0].get_y() + m_points[1].get_y() + m_points[2].get_y()) / 3.0f;

    return Vec2D(x_centroid, y_centroid);
}

float Triangle2D::area() const {
    return area(get_p0(), get_p1(), get_p2());
}

bool Triangle2D::contains_point(const Vec2D& p) const {
    float this_area = area();

    float a1 = area(p, get_p0(), get_p2());
    float a2 = area(get_p0(), p, get_p2());
    float a3 = area(get_p0(), get_p1(), p);

    return is_equal(this_area, a1 + a2 + a3);;
}


// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //

float Triangle2D::area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const {
    return fabsf(
        (p0.get_x() * (p1.get_y() - p2.get_y()) + 
         p1.get_x() * (p2.get_y() - p0.get_y()) + 
         p2.get_x() * (p0.get_y() - p1.get_y())) / 2.0f
    );
}
