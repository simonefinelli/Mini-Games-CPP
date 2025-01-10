/**
 * @file Circle2D.h
 * 
 * @class Circle2D
 * @brief Represents a 2D circle shape.
 * 
 * This class provides functionalities to create and manipulate a 2D circle.
 * It inherits from the Shape2D class.
 * 
 * @note The circle is defined by its center point and radius.
 * 
 * @section Example
 * @code
 * Vec2D center(0.0f, 0.0f);
 * float radius = 5.0f;
 * Circle2D circle(center, radius);
 * @endcode
 * 
 * @author SimoX
 * @date 2024-12-27
 */
#include "Circle2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //    
/**
 * @brief Default constructor for Circle2D.
 * 
 * Initializes a Circle2D object with a center at the origin (Vec2D::ZERO) and a 
 * radius of 0.
 */
Circle2D::Circle2D() : Circle2D(Vec2D::ZERO, 0) {}

/**
 * @brief Constructs a Circle2D object with a specified center and radius.
 * 
 * @param center The center point of the circle as a Vec2D object.
 * @param radius The radius of the circle as a float.
 */
Circle2D::Circle2D(const Vec2D& center, float radius) : m_radius(radius) {
    m_points.push_back(center);
}

// Instance methods ========================================================= //

/**
 * @brief Checks if this circle intersects with another circle.
 * 
 * This function calculates the distance between the centers of the two circles
 * and checks if it is less than the sum of their radii. If the distance is less
 * than the sum of the radii, the circles intersect.
 * 
 * @param other_circle The other Circle2D object to check for intersection.
 * @return true if the circles intersect, false otherwise.
 */
bool Circle2D::intersects(const Circle2D& other_circle) const {
    float dist_between = get_center_point().distance(other_circle.get_center_point());
    return dist_between < (m_radius + other_circle.m_radius);
}

/**
 * @brief Checks if a given point is within the circle.
 * 
 * This function determines whether a specified point lies inside or on the 
 * boundary of the circle.
 * 
 * @param point The point to check, represented as a Vec2D object.
 * @return true if the point is within or on the boundary of the circle, false otherwise.
 */
bool Circle2D::contains_point(const Vec2D& point) const {
    return is_less_than_or_equal(get_center_point().distance(point), m_radius);
}
