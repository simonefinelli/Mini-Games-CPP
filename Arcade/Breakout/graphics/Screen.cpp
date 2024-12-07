/**
 * @file Screen.cpp
 * @brief The Screen class is the principal game windows manager.
 * @author SimoX
 * @date 2024-10-24
 */

#include "Screen.h"

// ========================================================================== //
// Public interface                                                           //
// ========================================================================== //

// Constructors ============================================================= //

// Default Constructor
Screen::Screen() : m_width(0), m_height(0), m_window_ptr(nullptr), m_window_surface_ptr(nullptr)  {}


// Instance methods ========================================================= //

SDL_Window* Screen::init(uint32_t w, uint32_t h, uint32_t magnification) {
    // Init SDL library
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error - SDL could not initialize: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Set width and height
    m_width = w;
    m_height = h;

    // SDL Window creation
    m_window_ptr = SDL_CreateWindow(
        "ARCADE",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_width * magnification,
        m_height * magnification,
        SDL_WINDOW_SHOWN
    );
    if (!m_window_ptr) {
        std::cerr << "Error - Could not create the window: " << SDL_GetError() <<  std::endl;
        SDL_Quit();
        return nullptr;
    }

    // Create a surface for the main window
    m_window_surface_ptr = SDL_GetWindowSurface(m_window_ptr);
    if (!m_window_surface_ptr) {
        std::cerr << "Error: Failed to create SDL Window Surface: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window_ptr);
        m_window_ptr = nullptr;
        SDL_Quit();
        return nullptr;
    }

    // Init ScreenBuffer
    m_back_buffer.init(m_width, m_height);
    
    // Init color class
    Color::init_color_format(m_back_buffer.get_surface()->format);
    m_clear_color = Color::Black();

    // Clear buffer
    m_back_buffer.clear_surface(m_clear_color);

    return m_window_ptr;
}

void Screen::swap_screens() { // for double-buffering
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    // Clear the current front facing surface (not the back-buffer)
    clear_screen();  

    // Blit the surface of the screen buffer with the main Window and scale to
    // match the magnification of the window
    SDL_BlitScaled(m_back_buffer.get_surface(), nullptr, m_window_surface_ptr, nullptr);

    SDL_UpdateWindowSurface(m_window_ptr);

    m_back_buffer.clear_surface();
}

void Screen::draw(int x, int y, const Color& color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    m_back_buffer.set_pixel(color, x, y);

}

void Screen::draw(const Vec2D& point, const Color& color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    m_back_buffer.set_pixel(color, point.get_x(), point.get_y());
}

// Operator overloading ===================================================== //

// Destructor =============================================================== //
Screen::~Screen() {
    if (m_window_ptr) {
        SDL_DestroyWindow(m_window_ptr);
        m_window_ptr = nullptr;
    }
    SDL_Quit();
}
// ========================================================================== //
// Private interface                                                          //
// ========================================================================== //

// Instance methods ========================================================= //
void Screen::clear_screen() {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");  

    SDL_FillRect(m_window_surface_ptr, nullptr, m_clear_color.get_pixel_color());
}