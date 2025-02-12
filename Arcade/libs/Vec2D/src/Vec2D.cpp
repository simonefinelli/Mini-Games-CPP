/**
 * @file Vec2D.cpp
 * @brief Small library to handle basic 2D point operations.
 * @author SimoX
 * @date 2024-10-16
 */

#include "Vec2D.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Class variables ========================================================== //
const Vec2D Vec2D::ZERO = Vec2D(0.0f, 0.0f);

// Constructors ============================================================= //


// Instance methods ========================================================= //

/**
 * @brief Computes the square of the magnitude of the vector.
 * 
 * @return The square of the vector's magnitude (||v||^2).
 */
float Vec2D::mag2() const {
    return dot(*this);
}

/**
 * @brief Computes the magnitude (length) of the vector.
 * 
 * @return The magnitude of the vector (||v||).
 */
float Vec2D::mag() const {
    return sqrtf(mag2());
}

/**
 * @brief Returns a normalized (unit) vector in the same direction as the current 
 *        vector.
 * 
 * @return A unit vector pointing in the same direction as this vector, 
 *         or a zero vector if the magnitude is too small.
 */
Vec2D Vec2D::get_unit_vec() const {
    float magnitude = mag();

    if (magnitude > EPSILON)
        return *this / magnitude;
    else
        return Vec2D::ZERO;
}

/**
 * @brief Normalizes the current vector, making its magnitude equal to 1 (unit vector).
 * 
 * @return A reference to the normalized vector, or the unchanged vector if its 
 *         magnitude is too small.
 */
Vec2D& Vec2D::normalize() {
    float magnitude = mag();

    if (magnitude > EPSILON)
        return *this /= magnitude;
    else
        return *this;
}

/**
 * @brief Computes the distance between this vector and another vector.
 * 
 * @param other_vec The vector to calculate the distance to.
 * @return The distance between the two vectors.
 */
float Vec2D::distance(const Vec2D& other_vec) const {
    return (*this - other_vec).mag();
}

/**
 * @brief Computes the dot product of this vector with another vector.
 * 
 * @param other_vec The vector to perform the dot product with.
 * @return The dot product of the two vectors.
 */
float Vec2D::dot(const Vec2D& other_vec) const {
    return m_x * other_vec.m_x + m_y * other_vec.m_y;
}

/**
 * @brief Projects this vector onto another vector.
 * 
 * @param other_vec The vector to project onto.
 * @return The projection of this vector onto the given vector.
 */
Vec2D Vec2D::project_onto(const Vec2D& other_vec) const {
    // retrive 
    Vec2D other_unit_vec = other_vec.get_unit_vec();

    // calculate the projection
    float dot_result = dot(other_unit_vec);
    return other_unit_vec * dot_result;
}

/**
 * @brief Computes the angle between this vector and another vector.
 * 
 * @param other_vec The vector to compute the angle with.
 * @return The angle in radians between the two vectors.
 */
float Vec2D::angle_between(const Vec2D& other_vec) const {
    float dot_product = get_unit_vec().dot(other_vec.get_unit_vec());
    dot_product = std::min(1.0f, std::max(-1.0f, dot_product));
    return acosf(dot_product);
}

/**
 * @brief Reflects this vector off a given normal vector.
 * 
 * @param normal_vec The normal vector to reflect off of.
 * @return The reflection of this vector based on the normal vector.
 */
Vec2D Vec2D::reflect(const Vec2D& normal_vec) const {
    return *this - 2 * project_onto(normal_vec);
}

/**
 * @brief Rotates this vector around a given point by a specified angle (in radians).
 * 
 * @param alfa The angle to rotate by, in radians.
 * @param point The point around which the vector will be rotated.
 */
void Vec2D::rotate(float alfa, const Vec2D& point) {
    float x = m_x, y = m_y;
    float x0 = point.m_x, y0 = point.m_y;

    m_x = (x - x0) * cosf(alfa) - (y - y0) * sinf(alfa) + x0;
    m_y = (x - x0) * sinf(alfa) + (y - y0) * cosf(alfa) + y0;
}

/**
 * @brief Computes a new vector resulting from rotating this vector around a 
 *        given point by a specified angle (in radians).
 * 
 * @param alfa The angle to rotate by, in radians.
 * @param point The point around which the vector will be rotated.
 * @return A new vector that is the result of the rotation.
 */
Vec2D Vec2D::rotation_result(float alfa, const Vec2D& point) const {
    Vec2D tmp;
    
    float x = m_x, y = m_y;
    float x0 = point.m_x, y0 = point.m_y;

    float cos_a = cosf(alfa);
    float sin_a = sinf(alfa);

    tmp.m_x = (x - x0) * cos_a - (y - y0) * sin_a + x0;
    tmp.m_y = (x - x0) * sin_a + (y - y0) * cos_a + y0;

    return tmp;
}

// Operator overloading ===================================================== //

std::ostream& operator<<(std::ostream& out, const Vec2D& vec) {
    out << "Vec(x,y): (" << std::fixed << std::setprecision(2) 
        << vec.m_x << "," << vec.m_y << ")";
    return out;
}

bool Vec2D::operator==(const Vec2D& other_vec) const {
    return is_equal(m_x, other_vec.m_x) and is_equal(m_y, other_vec.m_y);
}

bool Vec2D::operator!=(const Vec2D& other_vec) const {
    return !(*this == other_vec);
}

Vec2D Vec2D::operator-() const {
    return Vec2D(-m_x, -m_y);
}

Vec2D Vec2D::operator*(float scalar) const {
    return Vec2D(scalar * m_x, scalar * m_y);
}

Vec2D operator*(float scalar, const Vec2D& vec) {
    return vec * scalar;
}

Vec2D Vec2D::operator/(float scalar) const {
    if (fabsf(scalar) < EPSILON)
        throw std::runtime_error("Division by zero or a very small value!");

    return Vec2D(m_x / scalar, m_y / scalar);
}

Vec2D& Vec2D::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

Vec2D& Vec2D::operator/=(float scalar) {
    if (fabsf(scalar) < EPSILON)
        throw std::runtime_error("Division by zero or a very small value!");

    *this = *this / scalar;
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D& other_vec) const {
    return Vec2D(m_x + other_vec.m_x, m_y + other_vec.m_y);
}

Vec2D Vec2D::operator-(const Vec2D& other_vec) const {
    return Vec2D(m_x - other_vec.m_x, m_y - other_vec.m_y);
}

Vec2D& Vec2D::operator+=(const Vec2D& other_vec) {
    *this = *this + other_vec;
    return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& other_vec) {
    *this = *this - other_vec;
    return *this;
}


// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //