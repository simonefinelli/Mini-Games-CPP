/**
 * @file main.cpp
 * @brief Space Invaders main.
 * This file includes the overall logic of the Game.
 * @author SimoX
 * @date 2023-09-09
 */

#include <chrono>
#include <thread>
#include "common.h"
#include "core.h"
#include "gui.h"

const std::chrono::duration<double> FRAME_DURATION(1.0 / FPS); // get first time interval

void game_loop();
bool play_again();

int main() {
    // initialize graphics
    gui::initialize_curses();
    
    // game procedure
    do {
        game_loop();
    } while (play_again());

    // shutdown graphics
    gui::shutdown_curses();
    return 0;

}

/**
 * @brief Core skeleton of the game.
 *
 * It initializes the game data, draw and update the board, display the
 * results and check if the game is over.
 */
void game_loop() {
    int user_choice;
    bool quit = false;

    // game initialization
    auto game_data = initialize_game();

    // show welcome screen
    // TODO

    // refresh on screen game data
    draw_screen_game(game_data);
    while (!quit) {
        // get current time
        auto curr_time = std::chrono::high_resolution_clock::now();

        // get user movement
        user_choice = get_user_input();
        // check for user input
        if (IS_QUIT_CHAR(user_choice)) { quit = true; continue; }
        // update game data
        update_game_data(game_data, static_cast<key>(user_choice));
        // refresh on screen game data
        draw_screen_game(game_data);

        // calculate how long to sleep to achieve the desired FPS
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - curr_time;
        std::chrono::duration<double> sleep_duration = FRAME_DURATION - elapsed;
        if (sleep_duration > std::chrono::duration<double>(0)) {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}

/**
 * @brief Checks if the Player wants to continue.
 *
 * @return True for yes, False for no.
 */
bool play_again() {
    return false;
}
