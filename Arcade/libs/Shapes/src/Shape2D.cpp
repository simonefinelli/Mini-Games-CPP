/**
 * @file Shape2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-16
 */
#include "Shape2D.h"

/**
 * @brief Moves the shape by a given offset.
 *
 * This function iterates through all the points of the shape and adds the 
 * specified delta offset to each point, effectively moving the entire shape 
 * by the given offset.
 *
 * @param delta_offset The offset by which to move the shape. This is a 
 * Vec2D object representing the change in the x and y coordinates.
 */
void Shape2D::move_by(const Vec2D& delta_offset) {
    for (auto& point : m_points) {
        point += delta_offset;
    }
}
