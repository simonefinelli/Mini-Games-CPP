/**
 * @file ScreenBuffer.h
 * @brief A screen buffer class rappresents a buffer that can be applied to the SDL screen
 * @author SimoX
 * @date 2024-10-24
 */

#ifndef GRAPHICS_SCREEN_BUFFER_H
#define GRAPHICS_SCREEN_BUFFER_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <iostream>
#include "Color.h"

class Color;
// struct SDL_surface;  // a SDL surface can be view as a big pixel buffer

/**
 * //todo
 */
class ScreenBuffer {
public:
    // Constructors ========================================================= //
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer* screen_buff); // copy constructor

    // Instance methods ===================================================== //
    void init(uint32_t format, uint32_t width, uint32_t height);
    inline SDL_Surface* get_surface() {return m_surface_ptr;}
    void clear_surface(const Color& c=Color::Black());
    void set_pixel(const Color& c, int x, int y);

    // Operator overloading ================================================= //
    ScreenBuffer& operator=(const ScreenBuffer& ScreenBuffer);

    // Destructor =========================================================== //
    ~ScreenBuffer();

private:
    // Instance variables =================================================== //
    SDL_Surface* m_surface_ptr;

    // Instance methods ===================================================== //
    size_t get_index(int row, int col);
};

#endif GRAPHICS_SCREEN_BUFFER_H