#include <iostream>
#include <SDL2/SDL.h>
#include <thread>

#include "Color.h"
#include "Line2D.h"
#include "Screen.h"
#include "ScreenBuffer.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int args, const char* argv[]) {

    Screen screen;
    screen.init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    // Create a line
    Line2D line = {Vec2D(0,0), Vec2D(SCREEN_WIDTH-1, SCREEN_HEIGHT-1)};
    screen.draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Cyan());
    screen.draw(line, Color::Orange());
    screen.swap_screens();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    line = {Vec2D(SCREEN_WIDTH-1, 0), Vec2D(0,SCREEN_HEIGHT-1)};
    screen.draw(line, Color::Cyan());
    screen.swap_screens();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


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