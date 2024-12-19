/**
 * @file Shape2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-16
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