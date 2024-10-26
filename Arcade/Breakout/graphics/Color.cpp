/**
 * @file Color.cpp
 * @brief 
 * @author SimoX
 * @date 2024-10-24
 */

#include "Color.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Class variables ========================================================== //
const SDL_PixelFormat* Color::m_format = nullptr;

// Class methods ============================================================ //
void Color::init_color_format(const SDL_PixelFormat* format) {
    Color::m_format = format;
}

// Constructors ============================================================= //
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    set_RGBA(r, g, b, a);
}

// Instance methods ========================================================= //
void Color::set_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    m_color = SDL_MapRGBA(m_format, r, g, b, a);
}
void Color::set_red(uint8_t red) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    set_RGBA(red, g, b, a);

}
void Color::set_green(uint8_t green) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    set_RGBA(r, green, b, a);
}
void Color::set_blue(uint8_t blue) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    set_RGBA(r, g, blue, a);
}
void Color::set_alpha(uint8_t alpha) {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    set_RGBA(r, g, b, alpha);
}

uint8_t Color::get_red() const {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    return r;
}

uint8_t Color::get_green() const {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    return g;
}

uint8_t Color::get_blue() const {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    return b;
}

uint8_t Color::get_alpha() const {
    uint8_t r, g, b, a;

    SDL_GetRGBA(m_color, m_format, &r, &g, &b, &a);
    return a;
}


// Operator overloading ===================================================== //


// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //