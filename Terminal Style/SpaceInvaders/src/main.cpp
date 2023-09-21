/**
 * @file main.cpp
 * @brief Space Invaders main.
 * This file includes the overall logic of the Game.
 * @author SimoX
 * @date 2023-09-09
 */

#include "core.h"
#include "gui.h"

void play_game();
bool play_again();

int main() {
    // initialize graphics
    gui::initialize_curses();
    do {
        play_game();
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
void play_game() {
    int user_choice;

    // game initialization
    auto game_data = initialize_game();

    // show welcome screen

    bool quit = false;
    while (!quit) {
        user_choice = get_user_input();
        // update_game_data();
        draw_screen_game();
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
