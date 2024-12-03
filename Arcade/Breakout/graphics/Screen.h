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

#include "Color.h"
#include "ScreenBuffer.h"
#include "Vec2D.h"

struct SDL_Window;
struct SDL_Surface;

class Screen {
public:
    Screen();
    ~Screen();

    SDL_Window* init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreen(); // for double-buffering

    inline void set_clear_color(const Color& clr_color) {m_clear_color = clr_color;}
    inline uint32_t width() const {return m_width;}
    inline uint32_t height() const {return m_height;}

    // Draw methods go here

    
private:
    uint32_t m_width;
    uint32_t m_height;

    Color m_clear_color;  // to clear every frame
    ScreenBuffer m_back_buffer;  // for dobule-buffering 

    SDL_Window* m_window_ptr;
    SDL_Surface* m_window_surface_ptr;

    void clear_screen();

};

#endif // GRAPHICS_SCREEN_H