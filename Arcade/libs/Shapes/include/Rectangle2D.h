/**
 * @file Rectangle2D.h
 * @brief Implementation of the Rectangle2D class for representing 2D rectangles.
 * 
 * This file contains the implementation of the Rectangle2D class, which provides
 * methods for creating, manipulating, and querying 2D rectangles. The class supports
 * operations such as calculating width and height, moving the rectangle, checking for
 * intersections with other rectangles, and determining if a point is contained within
 * the rectangle.
 * 
 * The Rectangle2D class uses the Vec2D class to represent points in 2D space.
 * 
 * @see Rectangle2D.cpp for the class definition and detailed documentation of each method.
 * 
 * @section Example
 * @code
 * Vec2D top_left(0, 0);
 * float w = 50.0f;
 * float h = 100.0f;
 * Rectangle2D r(top_left, w, h);
 * @endcode
 * 
 * @date 2024-12-22
 * @author SimoX
 */

#ifndef SHAPES_RECTANGLE_2D_H
#define SHAPES_RECTANGLE_2D_H

#include "Shape2D.h"

class Rectangle2D : public Shape2D {
public:
    // Constructors ========================================================= //     
    Rectangle2D();
    Rectangle2D(const Vec2D& top_left, unsigned int width, unsigned int height);
    Rectangle2D(const Vec2D& top_left, const Vec2D& bottom_right);

    // Instance methods ===================================================== //
    inline void set_top_left_point(const Vec2D& top_left) {m_points[0] = top_left;}
    inline void set_bottom_right_point(const Vec2D& bottom_right) {m_points[1] = bottom_right;}
    
    inline Vec2D get_top_left_point() const {return m_points[0];}
    inline Vec2D get_bottom_right_point() const {return m_points[1];}

    float get_width() const;
    float get_height() const;

    void move_to(const Vec2D& position);

    virtual Vec2D get_center_point() const override;

    bool intersects(const Rectangle2D& other_rectangle) const;
    bool constains_point(const Vec2D& point) const;

    static Rectangle2D inset(const Rectangle2D& rect, Vec2D& insets);

    virtual std::vector<Vec2D> get_points() const override;
};

#endif // SHAPES_RECTANGLE_2D_H