/**
 * @file Shape2D.cpp
 * @brief Implementation of the Shape2D class.
 * 
 * This file contains the implementation of the Shape2D class, which provides
 * functionalities for 2D shapes, including moving the shape by a given offset.
 * 
 * @date 2024-12-16
 * @author SimoX
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
