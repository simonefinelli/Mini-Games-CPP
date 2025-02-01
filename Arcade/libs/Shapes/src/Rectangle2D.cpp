/**
 * @file Rectangle2D.cpp
 * @brief Implementation of the Rectangle2D class for representing 2D rectangles.
 * 
 * This file contains the implementation of the Rectangle2D class, which provides
 * methods for creating, manipulating, and querying 2D rectangles. The class supports
 * operations such as calculating width and height, moving the rectangle, checking for
 * intersections with other rectangles, and determining if a point is contained within
 * the rectangle.
 * 
 * The Rectangle2D class uses the Vec2D class to represent points in 2D space.
 * 
 * @section Example
 * @code
 * Vec2D top_left(0, 0);
 * float w = 50.0f;
 * float h = 100.0f;
 * Rectangle2D r(top_left, w, h);
 * @endcode
 * 
 * @date 2024-12-22
 * @author SimoX
 */
#include <cmath>
#include "Rectangle2D.h"


// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //

/**
 * @brief Default constructor for the Rectangle2D class.
 *
 * This constructor initializes a Rectangle2D object with both the top-left
 * and bottom-right corners set to the zero vector (Vec2D::ZERO).
 */
Rectangle2D::Rectangle2D() : Rectangle2D(Vec2D::ZERO, Vec2D::ZERO) {}

/**
 * @brief Constructs a Rectangle2D object with the specified top-left corner, width, and height.
 *
 * @param top_left The top-left corner of the rectangle as a Vec2D object.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */
Rectangle2D::Rectangle2D(const Vec2D& top_left, unsigned int width, unsigned int height) {
    Vec2D bottom_right(top_left.get_x() + width - 1, 
                       top_left.get_y() + height - 1);
    
    m_points.push_back(top_left);
    m_points.push_back(bottom_right);
}

/**
 * @brief Constructs a Rectangle2D object with the given top-left and bottom-right points.
 * 
 * @param top_left The top-left point of the rectangle.
 * @param bottom_right The bottom-right point of the rectangle.
 */
Rectangle2D::Rectangle2D(const Vec2D& top_left, const Vec2D& bottom_right) {
    m_points.push_back(top_left);
    m_points.push_back(bottom_right);
}

// Instance methods ========================================================= //

/**
 * @brief Get the width of the rectangle.
 * 
 * This function calculates the width of the rectangle by taking the absolute 
 * difference between the x-coordinates of the bottom-right and top-left points 
 * of the rectangle and adding 1 to the result.
 * 
 * @return float The width of the rectangle.
 */
float Rectangle2D::get_width() const {
    return std::abs(get_bottom_right_point().get_x() - get_top_left_point().get_x()) + 1;
}

/**
 * @brief Get the height of the rectangle.
 * 
 * This function calculates the height of the rectangle by taking the absolute 
 * difference between the y-coordinates of the bottom-right and top-left points 
 * of the rectangle, and then adding 1 to the result.
 * 
 * @return float The height of the rectangle.
 */
float Rectangle2D::get_height() const {
    return std::abs(get_bottom_right_point().get_y() - get_top_left_point().get_y()) + 1;
}

/**
 * @brief Moves the rectangle to a new position.
 *
 * This function moves the rectangle such that its top-left corner is at the specified position.
 * The relative positions of the other points of the rectangle are maintained.
 *
 * @param position The new position for the top-left corner of the rectangle.
 */
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

/**
 * @brief Calculates and returns the center point of the rectangle.
 *
 * This function computes the center point of the rectangle by taking the top-left point
 * and adding half of the width to the x-coordinate and half of the height to the y-coordinate.
 *
 * @return Vec2D The center point of the rectangle as a Vec2D object.
 */
Vec2D Rectangle2D::get_center_point() const {
    float x_component = get_top_left_point().get_x() + get_width() / 2.0f;
    float y_component = get_top_left_point().get_y() + get_height() / 2.0f;

    return Vec2D(x_component, y_component);
}

/**
 * @brief Checks if this rectangle intersects with another rectangle.
 *
 * This function determines whether the current rectangle intersects with the specified
 * `other_rectangle`. Two rectangles are considered to intersect if they overlap in both
 * the x and y dimensions.
 *
 * @param other_rectangle The rectangle to check for intersection with.
 * @return true if the rectangles intersect, false otherwise.
 */
bool Rectangle2D::intersects(const Rectangle2D& other_rectangle) const {
    bool within_x = get_top_left_point().get_x() <= other_rectangle.get_bottom_right_point().get_x() and
                    get_bottom_right_point().get_x() >= other_rectangle.get_top_left_point().get_x();

    bool within_y = get_top_left_point().get_y() <= other_rectangle.get_bottom_right_point().get_y() and
                    get_bottom_right_point().get_y() >= other_rectangle.get_top_left_point().get_y();
    
    return within_x and within_y;
}

/**
 * @brief Checks if a given point is contained within the rectangle.
 * 
 * This function determines whether the specified point lies within the bounds
 * of the rectangle. It checks if the point's x-coordinate is between the 
 * x-coordinates of the top-left and bottom-right points of the rectangle, and 
 * if the point's y-coordinate is between the y-coordinates of the top-left and 
 * bottom-right points of the rectangle.
 * 
 * @param point The point to check, represented as a Vec2D object.
 * @return true if the point is within the rectangle, false otherwise.
 */
bool Rectangle2D::constains_point(const Vec2D& point) const {
    bool within_x = point.get_x() >= get_top_left_point().get_x() and
                    point.get_x() <= get_bottom_right_point().get_x();
    bool within_y = point.get_y() >= get_top_left_point().get_y() and
                    point.get_y() <= get_bottom_right_point().get_y();
                    
    return within_x and within_y;
}

/**
 * @brief Creates a new Rectangle2D that is inset by the specified insets.
 *
 * This function takes a reference to a Rectangle2D object and a Vec2D object representing the insets.
 * It returns a new Rectangle2D object that is inset by the specified insets.
 *
 * @param rect The original Rectangle2D object to be inset.
 * @param insets The Vec2D object representing the insets to be applied.
 * @return A new Rectangle2D object that is inset by the specified insets.
 */
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
 * - Top-right corner
 * - Bottom-right corner
 * - Bottom-left corner
 *
 * @return std::vector<Vec2D> A vector containing the four corner points of the rectangle.
 */
std::vector<Vec2D> Rectangle2D::get_points() const {

    std::vector<Vec2D> points;

    points.push_back(m_points[0]);  // Top-left
    points.push_back(Vec2D(m_points[1].get_x(), m_points[0].get_y()));  // Top-right
    points.push_back(m_points[1]);  // Bottom-right
    points.push_back(Vec2D(m_points[0].get_x(), m_points[1].get_y()));  // Bottom-left

    return points;
}