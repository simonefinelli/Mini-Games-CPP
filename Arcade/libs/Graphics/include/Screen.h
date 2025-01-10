/**
 * @file Screen.cpp
 * @brief The Screen class is the principal game windows manager.
 * @author SimoX
 * @date 2024-10-24
 */
#ifndef GRAPHICS_SCREEN_H
#define GRAPHICS_SCREEN_H

#include <SDL2/SDL.h>
#include <stdint.h>

#include "Circle2D.h"
#include "Color.h"
#include "Line2D.h"
#include "Rectangle2D.h"
#include "ScreenBuffer.h"
#include "Triangle2D.h"
#include "Vec2D.h"

class Vec2D;
struct SDL_Window;
struct SDL_Surface;

class Screen {
public:
    // Constructors ========================================================= //     
    Screen();

    // Instance methods ===================================================== //
    SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
    void swap_screens(); // for double-buffering

    inline void set_clear_color(const Color& clr_color) {m_clear_color = clr_color;}
    inline uint32_t width() const {return m_width;}
    inline uint32_t height() const {return m_height;}

    // Draw methods go here
    void draw(int x, int y, const Color& color);
    void draw(const Vec2D& point, const Color& color);
    void draw(const Line2D& line, const Color& color);
    void draw(const Triangle2D& triangle, const Color& color);
    void draw(const Rectangle2D& rectangle, const Color& color);
    void draw(const Circle2D& circle, const Color& color);

    // Destructor =========================================================== //
    ~Screen();
    
private:
    // Instance variables =================================================== //
    uint32_t m_width;
    uint32_t m_height;

    Color m_clear_color;  // to clear every frame
    ScreenBuffer m_back_buffer;  // for dobule-buffering 

    SDL_Window* m_window_ptr;
    SDL_Surface* m_window_surface_ptr;

    // Constructors ========================================================= //

    // Copy Constructor
    Screen(const Screen& other_screen); // copy constructor NOT allowed to be used from anyone
    
    // Instance methods ===================================================== //
    void clear_screen();

    // Operator overloading ================================================= //

    // Assignment Operator
    Screen& operator=(const Screen& screen)=default; // NOT allowed

};

#endif // GRAPHICS_SCREEN_H