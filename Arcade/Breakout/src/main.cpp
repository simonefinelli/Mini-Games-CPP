#include <iostream>
#include <SDL2/SDL.h>
#include <thread>

#include "Color.h"
#include "Screen.h"
#include "ScreenBuffer.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int args, const char* argv[]) {

    // // Init SDL
    // if (SDL_Init(SDL_INIT_VIDEO)) {
    //     std::cerr << "Error - SDL could not initialize: " << SDL_GetError() << std::endl;
    //     return 1;
    // }

    // // SDL Window creation
    // SDL_Window* window_ptr = SDL_CreateWindow(
    //     "ARCADE",
    //     SDL_WINDOWPOS_CENTERED,
    //     SDL_WINDOWPOS_CENTERED,
    //     SCREEN_WIDTH,
    //     SCREEN_HEIGHT,
    //     SDL_WINDOW_SHOWN
    // );
    // if (!window_ptr) {
    //     std::cerr << "Error - Could not create the window: " << SDL_GetError() <<  std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // // Create a surface for the main window
    // SDL_Surface* window_surface_ptr = SDL_GetWindowSurface(window_ptr);
    // if (!window_surface_ptr) {
    //     std::cerr << "Error: Failed to create SDL Window Surface: " << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window_ptr);
    //     SDL_Quit();
    //     return 1;
    // }

    // // Init ScreenBuffer
    // ScreenBuffer screen_buffer;
    // screen_buffer.init(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // // init color class
    // Color::init_color_format(screen_buffer.get_surface()->format);

    // for (int i = 0; i<100; i++ ) {
    //     for (int j= 0; j<100; j++) {
    //         // set_pixel(surface_ptr, Color::Purple().get_pixel_color(), i, j);
    //         screen_buffer.set_pixel(Color::Purple().get_pixel_color(), i, j);
    //     }
    // }

    // for (int i = 100; i<200; i++ ) {
    //     for (int j= 100; j<200; j++) {
    //         screen_buffer.set_pixel(0x88800080, i, j);
    //     }
    // }

    // // Blit the surface of the screen buffer with the main Window
    // SDL_BlitSurface(screen_buffer.get_surface(), NULL, window_surface_ptr, NULL);

    // SDL_UpdateWindowSurface(window_ptr);

    Screen screen;
    screen.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    screen.draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Cyan());
    screen.swap_screens();

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
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // SDL_DestroyWindow(window_ptr);  // clean window
    // SDL_Quit();  // clean SDL instance

    return 0;
}