/**
 * @file Rectangle2D.cpp
 * @brief 
 * @author SimoX
 * @date 2024-12-22
 */

#include <cmath>
#include "Rectangle2D.h"


// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //
Rectangle2D::Rectangle2D() : Rectangle2D(Vec2D::ZERO, Vec2D::ZERO) {}

Rectangle2D::Rectangle2D(const Vec2D& top_left, unsigned int width, unsigned int height) {
    Vec2D bottom_right(top_left.get_x() + width - 1, 
                       top_left.get_y() + height - 1);
    
    m_points.push_back(top_left);
    m_points.push_back(bottom_right);
}

Rectangle2D::Rectangle2D(const Vec2D& top_left, const Vec2D& bottom_right) {
    m_points.push_back(top_left);
    m_points.push_back(bottom_right);
}

// Instance methods ========================================================= //

float get_width() const {

}

float get_height() const {
    
}