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
ScreenBuffer::ScreenBuffer() : m_surface_ptr(nullptr), m_surface_area(0) {}

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

void ScreenBuffer::init(uint32_t width, uint32_t height, bool alpha_channel) {
    //m_surface_ptr = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);

    if (alpha_channel) {
        m_surface_ptr = SDL_CreateRGBSurface(
            0,
            width,
            height,
            32,
            0x00FF0000,  // R mask
            0x0000FF00,  // G mask
            0x000000FF,  // B mask
            0xFF000000   // A mask
        ); 
    } else {
        m_surface_ptr = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    }

    SDL_PixelFormat* pixel_format_ptr = m_surface_ptr->format;
    std::cout << "The RGBA surface pixel format is: "
              << SDL_GetPixelFormatName(pixel_format_ptr->format) << std::endl;  // SDL_PIXELFORMAT_ARGB8888


    if (!m_surface_ptr) {
        std::cerr << "Error: Failed to create RGBA surface: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    clear_surface();

    // Update area size
    m_surface_area = m_surface_ptr->w * m_surface_ptr->h;
}

void ScreenBuffer::clear_surface(const Color& c) {
    if (m_surface_ptr) {
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
    // check surface
    if (!m_surface_ptr) std::runtime_error("Surface not found!");
    // check boudaries
    if (!((y >= 0 and y < m_surface_ptr->h) and (x >= 0 and x < m_surface_ptr->w))) 
        std::runtime_error("Pixel out of boudaries!");

    // Exclusive access to the surface until Unlock
    if (SDL_MUSTLOCK(m_surface_ptr)) SDL_LockSurface(m_surface_ptr);

    uint32_t* pixels = (uint32_t*)m_surface_ptr->pixels;  // 1D array (buffer)
    
    auto index_position = get_index(y, x);
    if(index_position < m_surface_area)
        pixels[index_position] = color.get_pixel_color();
    // else
    //     std::cout << "index: " << index_position << " out of area: " << m_surface_area << std::endl;

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

// Destructor =============================================================== //
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