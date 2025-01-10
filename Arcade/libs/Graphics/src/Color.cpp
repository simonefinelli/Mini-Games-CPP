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
const uint32_t Color::BLACK = 0xFF000000;    // ARGB format
const uint32_t Color::GRAY = 0xFF808080;     // ARGB format
const uint32_t Color::WHITE = 0xFFFFFFFF;    // ARGB format
const uint32_t Color::RED = 0xFFFF0000;      // ARGB format
const uint32_t Color::GREEN = 0xFF00FF00;    // ARGB format
const uint32_t Color::BLUE = 0xFF0000FF;     // ARGB format
const uint32_t Color::CYAN = 0xFF00FFFF;     // ARGB format
const uint32_t Color::MAGENTA = 0xFFFF00FF;  // ARGB format
const uint32_t Color::YELLOW = 0xFFFFFF00;   // ARGB format
const uint32_t Color::ORANGE = 0xFFFFA500;   // ARGB format
const uint32_t Color::PURPLE = 0xFF800080;   // ARGB format

// Class methods ============================================================ //
void Color::init_color_format(const SDL_PixelFormat* format) {
    Color::m_format = format;
}
// Colors factory
Color Color::Black() { return Color(Color::BLACK); }      // RGBA (  0,   0,   0, 255)
Color Color::Gray() { return Color(Color::GRAY); }        // RGBA (128, 128, 128, 255)
Color Color::White() { return Color(Color::WHITE); }      // RGBA (255, 255, 255, 255)
Color Color::Red() { return Color(Color::RED); }          // RGBA (255,   0,   0, 255)
Color Color::Green() { return Color(Color::GREEN); }      // RGBA (  0, 255,   0, 255)
Color Color::Blue() { return Color(Color::BLUE); }        // RGBA (  0,   0, 255, 255)
Color Color::Cyan() { return Color(Color::CYAN); }        // RGBA (  0, 255, 255, 255)
Color Color::Magenta() { return Color(Color::MAGENTA); }  // RGBA (255,   0, 255, 255)
Color Color::Yellow() { return Color(Color::YELLOW); }    // RGBA (255, 255,   0, 255)
Color Color::Orange() { return Color(Color::ORANGE); }    // RGBA (255, 165,   0, 255)
Color Color::Purple() { return Color(Color::PURPLE); }    // RGBA (128,   0, 128, 255)

// Constructors ============================================================= //
Color::Color(uint32_t argb_color) : m_color(argb_color) {}

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