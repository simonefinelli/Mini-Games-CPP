#include <iostream>
#include <SDL2/SDL.h>

#include <Color.h>
#include <ScreenBuffer.h>

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;


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

    // Create window and RGBA surface (for alpha channel)
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
    
    SDL_PixelFormat* pixel_format_ptr = surface_ptr->format;
    std::cout << "The RGBA surface pixel format is: "
              << SDL_GetPixelFormatName(pixel_format_ptr->format) << std::endl;  // SDL_PIXELFORMAT_ARGB8888


    // init color class
    Color::init_color_format(pixel_format_ptr);
    // std::cout << "Color value" << Color::Cyan().get_pixel_color() << std::endl;

    // Init ScreenBuffer
    ScreenBuffer screen_buffer;
    screen_buffer.init(pixel_format_ptr->format, SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i<100; i++ ) {
        for (int j= 0; j<100; j++) {
            // set_pixel(surface_ptr, Color::Purple().get_pixel_color(), i, j);
            screen_buffer.set_pixel(Color::Purple().get_pixel_color(), i, j);
        }
    }

    for (int i = 100; i<200; i++ ) {
        for (int j= 100; j<200; j++) {
            screen_buffer.set_pixel(0x88800080, i, j);
        }
    }

    // Blit the RGBA surface onto the window surface
    // SDL_BlitSurface(surface_ptr, NULL, window_surface_ptr, NULL);
    SDL_BlitSurface(screen_buffer.get_surface(), NULL, window_surface_ptr, NULL);

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