/**
 * @file Circle2D.cpp
 * @brief 
 * @author SimoX
 * @date 2024-12-27
 */

#include "Circle2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //    
Circle2D::Circle2D() : Circle2D(Vec2D::ZERO, 0) {}

Circle2D::Circle2D(const Vec2D& center, float radius) : m_radius(radius) {
    m_points.push_back(center);
}

// Instance methods ========================================================= //
bool Circle2D::intersects(const Circle2D& other_circle) const {
    float dist_between = get_center_point().distance(other_circle.get_center_point());
    return dist_between < (m_radius + other_circle.m_radius);
}

bool Circle2D::contains_point(const Vec2D& point) const {
    return is_less_than_or_equal(get_center_point().distance(point), m_radius);
}
