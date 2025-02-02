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

void Screen::draw(const Triangle2D& triangle, const Color& color, bool fill, const Color& fill_color) {

    if (fill) fill_poly(triangle.get_points(), fill_color);
    
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    Line2D p0p1 = Line2D(triangle.get_p0(), triangle.get_p1());
    Line2D p1p2 = Line2D(triangle.get_p1(), triangle.get_p2());
    Line2D p2p0 = Line2D(triangle.get_p2(), triangle.get_p0());

    draw(p0p1, color);
    draw(p1p2, color);
    draw(p2p0, color);

    
}

void Screen::draw(const Rectangle2D& rectangle, const Color& color, bool fill, const Color& fill_color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    std::vector<Vec2D> points = rectangle.get_points();

    if (fill) fill_poly(points, fill_color);

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p0p2 = Line2D(points[1], points[2]);
    Line2D p1p3 = Line2D(points[2], points[3]);
    Line2D p2p3 = Line2D(points[3], points[0]);

    draw(p0p1, color);
    draw(p0p2, color);
    draw(p1p3, color);
    draw(p2p3, color);
}

void Screen::draw(const Circle2D& circle, const Color& color, bool fill, const Color& fill_color) {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");

    std::vector<Vec2D> circle_points;  // for poly fill
    std::vector<Line2D> lines;         // for poly fill

    unsigned number_of_segments = calculate_number_of_segments(circle.get_radius());
    
    float angle = (static_cast<float>(M_PI) * 2.0f) / static_cast<float>(number_of_segments);

    Vec2D p0 = Vec2D(circle.get_center_point().get_x() + circle.get_radius(), 
                     circle.get_center_point().get_y());
    Vec2D p1 = p0;
    Line2D next_line;

    for (unsigned i=0; i < number_of_segments; i++) {
        p1.rotate(angle, circle.get_center_point());
        next_line.set_p0(p0);
        next_line.set_p1(p1);

        lines.push_back(next_line);
        circle_points.push_back(p0);

        p0 = p1;
    }

    if (fill) fill_poly(circle_points, fill_color);

    // Draw the perimeter
    for (const Line2D& line : lines) draw(line, color);
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

/**
 * This function implements a polygon filling algorithm using the scan-line method.
 */
void Screen::fill_poly(const std::vector<Vec2D>& points, const Color& color) {
    if (points.size() == 0) return;

    // Find the Bounding Box of the polygon (find the max/min for x and y component)
    float top = points[0].get_y();
    float bottom = points[0].get_y();
    float right = points[0].get_x();
    float left = points[0].get_x();

    for (size_t i = 1; i < points.size(); i++) {
        if (points[i].get_y() < top)  // min
            top = points[i].get_y();
        
        if (points[i].get_y() > bottom)  // max
            bottom = points[i].get_y();

        if (points[i].get_x() < left)  // min
            left = points[i].get_x();

        if (points[i].get_x() > right)  // max
            right = points[i].get_x();
    }

    // Go through the polygon (vertically)
    for (int pixel_y = top; pixel_y < bottom; pixel_y++) {
        std::vector<float> node_x_vec;  // intersection points

        // For each pair of consecutive points (points[i] and points[j]), 
        // the function checks if the horizontal scan line (pixel_y) intersects 
        // the edge defined by these two points.
        size_t j = points.size() - 1;
        for (size_t i = 0; i < points.size(); i++) {
            float point_iy = points[i].get_y();
            float point_jy = points[j].get_y();

            // Check if the scanline intersects the edge
            if ((point_iy <= static_cast<float>(pixel_y) && point_jy > static_cast<float>(pixel_y)) || 
                (point_jy <= static_cast<float>(pixel_y) && point_iy > static_cast<float>(pixel_y))) {

                    float denom = point_jy - point_iy;
                    if (is_equal(denom, 0)) continue; // ignore perfectly horizontal edges

                    // Linear interpolation
                    float x = points[i].get_x() + (static_cast<float>(pixel_y) - point_iy) / denom * (points[j].get_x() - points[i].get_x());

                    node_x_vec.push_back(x); // all intersection points (node_x_vec) along the scan line are stored.
            }
            j = i;
        }

        // Sort points in ascending order (to draw a line from left to right)
        std::sort(node_x_vec.begin(), node_x_vec.end(), std::less<>());

        // Draw the line
        if (node_x_vec.size() % 2 != 0) continue; // ensure valid pairs
        for (size_t k = 0; k < node_x_vec.size(); k += 2) {
            if (node_x_vec[k] > right) break;

            // Adjust the fill range to avoid filling the left and right borders
            int start_x = static_cast<int>(std::ceil(node_x_vec[k])); // round up to avoid covering the left border
            int end_x = static_cast<int>(std::floor(node_x_vec[k + 1])); // round down to avoid covering the right border

            // Clamp to the bounding box
            start_x = std::max(start_x, static_cast<int>(left) + 1); // start just after the left border
            end_x = std::min(end_x, static_cast<int>(right) - 1); // stop just before the right border

            // Ensure valid range
            if (start_x <= end_x) {
                for (int pixel_x = start_x; pixel_x <= end_x; pixel_x++) {
                    draw(pixel_x, pixel_y, color);
                }
            }
        }
    }
}

void Screen::clear_screen() {
    // Check for window initialization
    if (!m_window_ptr) throw std::runtime_error("Window not initialized!");  

    SDL_FillRect(m_window_surface_ptr, nullptr, m_clear_color.get_pixel_color());
}