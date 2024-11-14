/**
 * @file ScreenBuffer.cpp
 * @brief A screen buffer class rappresents a buffer that can be applied to the SDL screen
 * @author SimoX
 * @date 2024-10-24
 */
#include "ScreenBuffer.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //
ScreenBuffer::ScreenBuffer() : m_surface_ptr(nullptr) {}

// Copy constructor
ScreenBuffer::ScreenBuffer(const ScreenBuffer& screen_buff) { 
    m_surface_ptr = SDL_CreateRGBSurfaceWithFormat(
        0,
        screen_buff.m_surface_ptr->w,
        screen_buff.m_surface_ptr->h,
        0,
        screen_buff.m_surface_ptr->format->format
    );

    if (!m_surface_ptr) {
        std::cerr << "Error: Failed to create RGBA surface: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_BlitSurface(screen_buff.m_surface_ptr, nullptr, m_surface_ptr, nullptr);  // copy all the pixels
} 


// Instance methods ========================================================= //

void ScreenBuffer::init(uint32_t format, uint32_t width, uint32_t height) {
    m_surface_ptr = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);

    if (!m_surface_ptr) {
        std::cerr << "Error: Failed to create RGBA surface: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    clear_surface();
}

void ScreenBuffer::clear_surface(const Color& c) {
    if(m_surface_ptr) {
        SDL_FillRect(m_surface_ptr, nullptr, c.get_pixel_color());
    } else {
        throw std::runtime_error("Surface not found!");
    }
}

/**
 * Set the pixel's intensity (color) in a specific location
 * color ARGB
 * x column
 * y row
 */
void ScreenBuffer::set_pixel(const Color& color, int x, int y) {

    if(!m_surface_ptr) std::runtime_error("Surface not found!");

    // Exclusive access to the surface until Unlock
    if (SDL_MUSTLOCK(m_surface_ptr)) SDL_LockSurface(m_surface_ptr);

    uint32_t* pixels = (uint32_t*)m_surface_ptr->pixels;  // 1D array (buffer)
    pixels[get_index(y, x)] = color.get_pixel_color();

    if (SDL_MUSTLOCK(m_surface_ptr)) SDL_UnlockSurface(m_surface_ptr);
}

// Operator overloading ===================================================== //
ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& screen_buff) {
    if (this == &screen_buff) return *this;

    if (m_surface_ptr) {
        SDL_FreeSurface(m_surface_ptr);
        m_surface_ptr = nullptr;
    }

    if (screen_buff.m_surface_ptr != nullptr) {
        m_surface_ptr = SDL_CreateRGBSurfaceWithFormat(
            0,
            screen_buff.m_surface_ptr->w,
            screen_buff.m_surface_ptr->h,
            0,
            screen_buff.m_surface_ptr->format->format
        );

        if (!m_surface_ptr) {
            std::cerr << "Error: Failed to create RGBA surface: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(1);
        }

        SDL_BlitSurface(screen_buff.m_surface_ptr, nullptr, m_surface_ptr, nullptr);  // copy all the pixels
    }
    
    return *this;
}

// Destructor =========================================================== //
ScreenBuffer::~ScreenBuffer() {
    if (m_surface_ptr) SDL_FreeSurface(m_surface_ptr);
}

// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //

// Instance methods ========================================================= //

/**
 * Transform 2D index in 1D index
 */
size_t ScreenBuffer::get_index(int row, int col) {
    if(!m_surface_ptr) std::runtime_error("Surface not found!");
    
    return m_surface_ptr->w * row + col;
}