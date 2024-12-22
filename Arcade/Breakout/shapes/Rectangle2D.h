/**
 * @file Rectangle2D.h
 * @brief 
 * @author SimoX
 * @date 2024-12-22
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
    
    inline Vec2D get_top_left_point() {return m_points[0];}
    inline Vec2D get_bottom_right_point() {return m_points[1];}

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