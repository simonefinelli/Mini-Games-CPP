/**
 * @file Triangle2D.cpp
 * @brief Implementation of the Triangle2D class for representing and manipulating 2D triangles.
 * 
 * This file contains the implementation of the Triangle2D class, which provides methods
 * for constructing triangles, calculating their centroids, areas, and checking if a point
 * lies within the triangle.
 * 
 * The Triangle2D class uses the Vec2D class to represent 2D points.
 * 
 * @author SimoX
 * @date 2024-12-16
 */
#include <cmath>
#include "Triangle2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //

/**
 * @brief Default constructor for the Triangle2D class.
 * 
 * Initializes a Triangle2D object with all vertices set to the zero vector.
 */
Triangle2D::Triangle2D() : Triangle2D(Vec2D::ZERO, Vec2D::ZERO, Vec2D::ZERO) {}

/**
 * @brief Constructs a Triangle2D object with three vertices.
 * 
 * @param p0 The first vertex of the triangle.
 * @param p1 The second vertex of the triangle.
 * @param p2 The third vertex of the triangle.
 */
Triangle2D::Triangle2D(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) {
    m_points.push_back(p0);
    m_points.push_back(p1);
    m_points.push_back(p2);
}

// Instance methods ========================================================= //

/**
 * @brief Calculates and returns the centroid (center point) of the triangle.
 *
 * This function computes the centroid of the triangle by averaging the x and y
 * coordinates of its three vertices.
 *
 * @return Vec2D The centroid of the triangle.
 */
Vec2D Triangle2D::get_center_point() const {
    float x_centroid = (m_points[0].get_x() + m_points[1].get_x() + m_points[2].get_x()) / 3.0f;
    float y_centroid = (m_points[0].get_y() + m_points[1].get_y() + m_points[2].get_y()) / 3.0f;

    return Vec2D(x_centroid, y_centroid);
}

/**
 * @brief Calculates the area of the triangle.
 * 
 * This function computes the area of the triangle using the coordinates
 * of its three vertices.
 * 
 * @return The area of the triangle.
 */
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

/**
 * @brief Calculates the area of a triangle given its three vertices.
 * 
 * This function uses the determinant method to compute the area of a triangle
 * defined by three 2D points (p0, p1, p2). The formula used is:
 * 
 * Area = |(x0(y1 - y2) + x1(y2 - y0) + x2(y0 - y1)) / 2|
 * 
 * @param p0 The first vertex of the triangle.
 * @param p1 The second vertex of the triangle.
 * @param p2 The third vertex of the triangle.
 * @return The area of the triangle.
 */
float Triangle2D::area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const {
    return fabsf(
        (p0.get_x() * (p1.get_y() - p2.get_y()) + 
         p1.get_x() * (p2.get_y() - p0.get_y()) + 
         p2.get_x() * (p0.get_y() - p1.get_y())) / 2.0f
    );
}
