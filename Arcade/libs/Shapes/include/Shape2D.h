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

#ifndef SHAPES_SHAPE_2D_H
#define SHAPES_SHAPE_2D_H

#include <vector>
#include "Vec2D.h"

class Shape2D {
public:
    virtual Vec2D get_center_point() const = 0;
    inline virtual std::vector<Vec2D> get_points() const {return m_points;}
    void move_by(const Vec2D& delta_offset);

    inline virtual ~Shape2D() = default;

protected:
    std::vector<Vec2D> m_points;

};

#endif // SHAPES_SHAPE_2D_H