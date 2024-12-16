/**
 * @file Shape2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-16
 */
#include "Shape2D.h"

void Shape2D::move_by(const Vec2D& delta_offset) {
    for (auto& point : m_points) {
        point += delta_offset;
    }
}