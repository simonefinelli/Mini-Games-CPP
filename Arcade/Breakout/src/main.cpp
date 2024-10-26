#include <iostream>
#include <SDL2/SDL.h>

#include <Color.h>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;

void set_pixel(SDL_Surface* surface_ptr, uint32_t color, int x, int y);
size_t get_index(SDL_Surface* surface_ptr, int row, int col);


int main(int args, const char* argv[]) {

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error - SDL could not initialize: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Window creation
    SDL_Window* window_ptr = SDL_CreateWindow(
        "ARCADE",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window_ptr) {
        std::cerr << "Error - Could not create the window: " << SDL_GetError() <<  std::endl;
        SDL_Quit();
        return 1;
    }

    // Create windo and RGBA surface (for alpha channel)
    SDL_Surface* window_surface_ptr = SDL_GetWindowSurface(window_ptr);
    SDL_Surface* surface_ptr = SDL_CreateRGBSurface(
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        32,
        0x00FF0000,  // R mask
        0x0000FF00,  // G mask
        0x000000FF,  // B mask
        0xFF000000   // A mask
    );  
    if (!surface_ptr) {
        std::cerr << "Error: Failed to create RGBA surface: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window_ptr);
        SDL_Quit();
        return 1;
    }
    
    SDL_PixelFormat* pixel_format = surface_ptr->format;
    std::cout << "The RGBA surface pixel format is: "
              << SDL_GetPixelFormatName(pixel_format->format) << std::endl;  // SDL_PIXELFORMAT_ARGB8888


    // init color class
    Color::init_color_format(pixel_format);
    // std::cout << "Color value" << Color::Cyan().get_pixel_color() << std::endl;


    for (int i = 0; i<100; i++ ) {
        for (int j= 0; j<100; j++) {
            set_pixel(surface_ptr, Color::Purple().get_pixel_color(), i, j);
        }
    }

    for (int i = 100; i<200; i++ ) {
        for (int j= 100; j<200; j++) {
            set_pixel(surface_ptr, Color::PURPLE, i, j);
        }
    }

    // Blit the RGBA surface onto the window surface
    SDL_BlitSurface(surface_ptr, NULL, window_surface_ptr, NULL);

    SDL_UpdateWindowSurface(window_ptr);


    // Start the main program
    SDL_Event sdl_event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_QUIT:  // close the window
                    running = false;
                    break;
                default:;
            }
        }
    }

    SDL_FreeSurface(surface_ptr);  // clear argb surface
    SDL_DestroyWindow(window_ptr);  // clean window
    SDL_Quit();  // clean SDL instance

    return 0;
}

/**
 * Set the pixel's intensity (color) in a specific location
 * color ARGB
 * x column
 * y row
 */
void set_pixel(SDL_Surface* surface_ptr, uint32_t color, int x, int y) {

    // Exclusive access to the surface until Unlock
    if (SDL_MUSTLOCK(surface_ptr)) SDL_LockSurface(surface_ptr);

    uint32_t* pixels = (uint32_t*)surface_ptr->pixels;  // 1D array (buffer)
    pixels[get_index(surface_ptr, y, x)] = color;

    if (SDL_MUSTLOCK(surface_ptr)) SDL_UnlockSurface(surface_ptr);
}

/**
 * Transform 2D index in 1D index
 */
size_t get_index(SDL_Surface* surface_ptr, int row, int col) {
    return surface_ptr->w * row + col;
}