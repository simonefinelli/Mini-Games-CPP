/**
 * @file Screen.cpp
 * @brief The Screen class is the principal game windows manager.
 * @author SimoX
 * @date 2024-10-24
 */

#include <cmath>
#include <algorithm>
#include "Screen.h"
#include "graphics_utils.h"

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

/**
 * Draw a line using Bresnham's Algorithm 
 */
void Screen::draw(const Line2D& line, const Color& color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    int dx, dy;

    int x0 = roundf(line.get_p0().get_x());
    int y0 = roundf(line.get_p0().get_y());
    int x1 = roundf(line.get_p1().get_x());
    int y1 = roundf(line.get_p1().get_y());

    dx = x1 - x0;
    dy = y1 - y0;

    signed const char ix((dx > 0) - (dx < 0));  // evaluate to 1 or -1 (depends of which direction the line is)
    signed const char iy((dy > 0) - (dy < 0));

    dx = abs(dx) * 2;  // * 2 to get rid of any floating point math
    dy = abs(dy) * 2;

    // Draw the line
    draw(x0, y0, color); // first point
    if (dx >= dy) {  // go along in the x direction
        int d = dy - dx/2;

        while(x0 != x1) {
            if(d >= 0) {
                d -= dx;
                y0 += iy;
            }

            d += dy;
            x0 += ix;

            draw(x0, y0, color);
        }
    } else {  // go along in y
        int d = dx - dy/2;

        while(y0 != y1) {
            if (d >= 0) {
                d -= dy;
                x0 += ix;
            }

            d += dx;
            y0 += iy;

            draw(x0, y0, color);
        }
    }

}

void Screen::draw(const Triangle2D& triangle, const Color& color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    Line2D p0p1 = Line2D(triangle.get_p0(), triangle.get_p1());
    Line2D p1p2 = Line2D(triangle.get_p1(), triangle.get_p2());
    Line2D p2p0 = Line2D(triangle.get_p2(), triangle.get_p0());

    draw(p0p1, color);
    draw(p1p2, color);
    draw(p2p0, color);
}

void Screen::draw(const Rectangle2D& rectangle, const Color& color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    std::vector<Vec2D> points = rectangle.get_points();

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p0p2 = Line2D(points[1], points[3]);
    Line2D p1p3 = Line2D(points[3], points[2]);
    Line2D p2p3 = Line2D(points[2], points[0]);

    draw(p0p1, color);
    draw(p0p2, color);
    draw(p1p3, color);
    draw(p2p3, color);
}

void Screen::draw(const Circle2D& circle, const Color& color) {
    unsigned number_of_segments = calculate_number_of_segments(circle.get_radius());
    
    float angle = (static_cast<float>(M_PI) * 2.0f) / static_cast<float>(number_of_segments);

    Vec2D p0 = Vec2D(circle.get_center_point().get_x() + circle.get_radius(), 
                     circle.get_center_point().get_y());
    Vec2D p1 = p0;
    Line2D next_line;

    for(unsigned i=0; i < number_of_segments; i++) {
        p1.rotate(angle, circle.get_center_point());
        next_line.set_p0(p0);
        next_line.set_p1(p1);

        draw(next_line, color);

        p0 = p1;
    }
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