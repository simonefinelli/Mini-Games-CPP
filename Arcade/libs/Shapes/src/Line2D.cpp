/**
 * @file Line2D.cpp
 * @brief Implementation of the Line2D class for representing and manipulating 2D lines.
 * 
 * This file contains the implementation of the Line2D class, which provides methods for
 * creating and manipulating 2D lines. The class includes constructors for initializing
 * lines with specific endpoints, as well as methods for calculating the closest point
 * on the line to a given point, the minimum distance from a point to the line, the slope
 * of the line, the midpoint of the line, and the length of the line. Additionally, the
 * class supports equality comparison between two Line2D objects.
 * 
 * The Line2D class relies on the Vec2D class for representing 2D points and vectors.
 * 
 * @note This implementation assumes the existence of a Vec2D class with appropriate
 *       methods for vector arithmetic, distance calculation, and other vector operations.
 * 
 * @see Line2D.h for the class definition and detailed documentation of each method.
 * 
 * @author SimoX
 * @date 2024-12-08
 */

#include "Line2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //

/**
 * @brief Default constructor for Line2D class.
 * 
 * Initializes a Line2D object with both start and end points set to Vec2D::ZERO.
 */
Line2D::Line2D() : Line2D(Vec2D::ZERO, Vec2D::ZERO) {}


/**
 * @brief Constructs a Line2D object using the coordinates of two points.
 * 
 * This constructor initializes a Line2D object by creating two Vec2D objects
 * representing the start and end points of the line.
 * 
 * @param x0 The x-coordinate of the start point.
 * @param y0 The y-coordinate of the start point.
 * @param x1 The x-coordinate of the end point.
 * @param y1 The y-coordinate of the end point.
 */
Line2D::Line2D(float x0, float y0, float x1, float y1)
    : Line2D(Vec2D(x0, y0), Vec2D(x1, y1)) {}

/**
 * @brief Constructs a Line2D object with two endpoints.
 * 
 * @param p0 The starting point of the line.
 * @param p1 The ending point of the line.
 */
Line2D::Line2D(const Vec2D& p0, const Vec2D& p1)
    : m_p0(p0), m_p1(p1) {

}

// Instance methods ========================================================= //

/**
 * @brief Calculates the closest point on the line or line segment to a given point.
 *
 * This function computes the point on the line defined by the current Line2D object
 * that is closest to the specified point `p`. Optionally, the calculation can be
 * constrained to the line segment defined by the two endpoints of the Line2D.
 *
 * @param p The point for which the closest point on the line or segment is to be calculated.
 * @param limit_to_segment If `true`, the closest point is constrained to lie within the
 *        line segment defined by the endpoints of the Line2D. If `false`, the closest point
 *        can lie anywhere along the infinite line.
 * @return A Vec2D representing the closest point on the line or segment to the point `p`.
 *
 * @note The method uses vector projections to determine the closest point. If `limit_to_segment`
 *       is `true`, the projection parameter is clamped between 0 and 1 to ensure the result lies
 *       within the segment bounds.
 */
Vec2D Line2D::closest_point(const Vec2D& p, bool limit_to_segment) const {
    Vec2D p0_to_p = p - m_p0;
    Vec2D p0_to_p1 = m_p1 - m_p0;

    float l2 = p0_to_p1.mag2();

    float dot = p0_to_p.dot(p0_to_p1);
    
    float t = dot / l2;

    if (limit_to_segment) t = std::fmax(0, std::fmin(1.0f, t));

    return m_p0 + p0_to_p1 * t;
}


/**
 * @brief Calculates the minimum distance from a given point to the line.
 *
 * This function computes the minimum distance from the specified point to the line.
 * If the `limit_to_segment` parameter is set to true, the distance is calculated
 * to the closest point on the line segment. Otherwise, the distance is calculated
 * to the closest point on the infinite line.
 *
 * @param p The point from which the distance is to be calculated.
 * @param limit_to_segment If true, limits the calculation to the line segment.
 *                         If false, calculates the distance to the infinite line.
 * @return The minimum distance from the point to the line.
 */
float Line2D::min_distance_from(const Vec2D& p, bool limit_to_segment) const {
    return p.distance(closest_point(p, limit_to_segment));
}


/**
 * @brief Calculates the slope of the line segment.
 * 
 * This function computes the slope of the line segment defined by two points, m_p0 and m_p1.
 * If the difference in the x-coordinates (dx) is less than a small epsilon value, the function
 * returns 0 to avoid division by zero.
 * 
 * @return The slope of the line segment. If the line is vertical, returns 0.
 */
float Line2D::slope() const {
    float dx = m_p1.get_x() - m_p0.get_x();

    if (fabsf(dx) < EPSILON) return 0;

    float dy = m_p1.get_y() - m_p0.get_y();

    return dy / dx;
}

/**
 * @brief Calculates the midpoint of the line segment.
 * 
 * This function computes the midpoint of the line segment defined by the
 * two endpoints m_p0 and m_p1. The midpoint is the point that is equidistant
 * from both endpoints.
 * 
 * @return Vec2D The midpoint of the line segment.
 */
Vec2D Line2D::mid_point() const {
    return Vec2D((m_p0.get_x() + m_p1.get_x())/ 2.0f, (m_p0.get_y() + m_p1.get_y()) / 2.0f);
}

/**
 * @brief Calculates the length of the line segment.
 * 
 * This function computes the distance between the two endpoints
 * of the line segment, m_p0 and m_p1.
 * 
 * @return The length of the line segment as a float.
 */
float Line2D::length() const {
    return m_p1.distance(m_p0);
}

// Operator overloading ===================================================== //

/**
 * @brief Equality operator for Line2D objects.
 *
 * This operator checks if two Line2D objects are equal by comparing their
 * endpoints.
 *
 * @param other_line The other Line2D object to compare with.
 * @return true if both Line2D objects have the same endpoints, false otherwise.
 */
bool Line2D::operator==(const Line2D& other_line) const {
    return m_p0 == other_line.get_p0() and m_p1 == other_line.get_p1();
}