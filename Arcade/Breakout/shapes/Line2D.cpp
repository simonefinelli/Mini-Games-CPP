/**
 * @file Line2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-08
 */
#include "Line2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //

Line2D::Line2D() : Line2D(Vec2D::ZERO, Vec2D::ZERO) {}

Line2D::Line2D(float x0, float y0, float x1, float y1)
    : Line2D(Vec2D(x0, y0), Vec2D(x1, y1)) {}

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
Vec2D Line2D::closest_point(const Vec2D& p, bool limit_to_segment=false) const {
    Vec2D p0_to_p = p - m_p0;
    Vec2D p0_to_p1 = m_p1 - m_p0;

    float l2 = p0_to_p1.mag2();

    float dot = p0_to_p.dot(p0_to_p1);
    
    float t = dot / l2;

    if (limit_to_segment) t = std::fmax(0, std::fmin(1.0f, t));

    return m_p0 + p0_to_p1 * t;
}

float Line2D::min_distance_from(const Vec2D& p, bool limit_to_segment) const {
    return p.distance(closest_point(p, limit_to_segment));
}

float Line2D::slope() const {
    float dx = m_p1.get_x() - m_p0.get_x();

    if (fabsf(dx) < EPSILON) return 0;

    float dy = m_p1.get_y() - m_p0.get_y();

    return dy / dx;
}

Vec2D Line2D::mid_point() const {
    return Vec2D((m_p0.get_x() + m_p1.get_x())/ 2.0f, (m_p0.get_y() + m_p1.get_y()) / 2.0f);
}

float Line2D::length() const {
    return m_p1.distance(m_p0);
}

// Operator overloading ===================================================== //
bool Line2D::operator==(const Line2D& other_line) const {
    return m_p0 == other_line.get_p0() and m_p1 == other_line.get_p1();
}