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

float Rectangle2D::get_width() const {
    return std::abs(get_bottom_right_point().get_x() - get_top_left_point().get_x()) + 1;
}

float Rectangle2D::get_height() const {
    return std::abs(get_bottom_right_point().get_y() - get_top_left_point().get_y()) + 1;
}

void Rectangle2D::move_to(const Vec2D& position) {
    Vec2D top_left = get_top_left_point();
    Vec2D diff = position - top_left;

    m_points[0] += diff;
    m_points[1] += diff;

    // float width = get_width();
    // float height = get_height();

    // set_top_left_point(position);
    // set_bottom_right_point(Vec2D(position.get_x() + width - 1, position.get_y() + height - 1));
}

Vec2D Rectangle2D::get_center_point() const {
    float x_component = get_top_left_point().get_x() + get_width() / 2.0f;
    float y_component = get_top_left_point().get_y() + get_height() / 2.0f;

    return Vec2D(x_component, y_component);
}

bool Rectangle2D::intersects(const Rectangle2D& other_rectangle) const {
    bool within_x = get_top_left_point().get_x() <= other_rectangle.get_bottom_right_point().get_x() and
                    get_bottom_right_point().get_x() >= other_rectangle.get_top_left_point().get_x();

    bool within_y = get_top_left_point().get_y() <= other_rectangle.get_bottom_right_point().get_y() and
                    get_bottom_right_point().get_y() >= other_rectangle.get_top_left_point().get_y();
    
    return within_x and within_y;
}

bool Rectangle2D::constains_point(const Vec2D& point) const {
    bool within_x = point.get_x() >= get_top_left_point().get_x() and
                    point.get_x() <= get_bottom_right_point().get_x();
    bool within_y = point.get_y() >= get_top_left_point().get_y() and
                    point.get_y() <= get_bottom_right_point().get_y();
                    
    return within_x and within_y;
}

Rectangle2D Rectangle2D::inset(const Rectangle2D& rect, Vec2D& insets) {
    Vec2D top_left = rect.get_top_left_point() + insets;
    float width = rect.get_width() - 2 * insets.get_x();
    float height = rect.get_height() - 2 * insets.get_y();

    return Rectangle2D(top_left, width, height);
}

/**
 * @brief Retrieves the four corner points of the rectangle.
 *
 * This function returns a vector containing the four corner points of the rectangle.
 * The points are returned in the following order:
 * - Top-left corner
 * - Bottom-right corner
 * - Bottom-left corner
 * - Top-right corner
 *
 * @return std::vector<Vec2D> A vector containing the four corner points of the rectangle.
 */
std::vector<Vec2D> Rectangle2D::get_points() const {
    std::vector<Vec2D> points;

    points.push_back(m_points[0]);
    points.push_back(Vec2D(m_points[1].get_x(), m_points[0].get_y()));
    points.push_back(Vec2D(m_points[0].get_x(), m_points[1].get_y()));
    points.push_back(m_points[1]);

    return points;
}