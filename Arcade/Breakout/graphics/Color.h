/**
 * @file Color.h
 * @brief 
 * @author SimoX
 * @date 2024-10-24
 */

#ifndef GRAPHICS_COLOR_H
#define GRAPHICS_COLOR_H

#include <stdint.h>
#include <SDL2/SDL.h>

struct SDL_PixelFormat;

class Color {
public:
    // Class variables ====================================================== //
    static const SDL_PixelFormat* m_format;
    static const uint32_t BLACK, GRAY, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, ORANGE, PURPLE;

    // Class methods ======================================================== //
    static void init_color_format(const SDL_PixelFormat* format);
    // Colors factory
    static Color Black();
    static Color Gray();
    static Color White();
    static Color Red();
    static Color Green();
    static Color Blue();
    static Color Cyan();
    static Color Magenta();
    static Color Yellow();
    static Color Orange();
    static Color Purple();

    // Constructors ========================================================= //
    Color() : Color(0xFF0000) {};
    Color(uint32_t color);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    // Instance methods ===================================================== //
    inline uint32_t get_pixel_color() const {return m_color;}
    void set_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void set_red(uint8_t r);
    void set_green(uint8_t g);
    void set_blue(uint8_t b);
    void set_alpha(uint8_t a);

    uint8_t get_red() const;
    uint8_t get_green() const;
    uint8_t get_blue() const;
    uint8_t get_alpha() const;

    // Operator overloading ================================================= //
    inline bool operator==(const Color& other) const {return m_color == other.m_color;}
    inline bool operator!=(const Color& other) const {return  !(*this == other);}

private:
    uint32_t m_color;

};

#endif // GRAPHICS_COLOR_H