/**
 * @file main.cpp
 * @brief Space Invaders main.
 * This file includes the overall logic of the Game.
 * @author SimoX
 * @date 2023-09-09
 */

#include "core.h"
#include "gui.h"
#include <iostream>

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
    bool quit = false;

    // game initialization
    auto game_data = initialize_game();

    // show welcome screen

    // refresh on screen game data
    draw_screen_game(game_data);
    while (!quit) {
        // get user movement
        user_choice = get_user_input();
        // check for user input
        if (IS_QUIT_CHAR(user_choice)) { quit = true; continue; }
        if (!IS_VALID_INPUT(user_choice)) continue;
        // update game data
        update_game_data(game_data, static_cast<key>(user_choice));
        // refresh on screen game data
        draw_screen_game(game_data);
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
