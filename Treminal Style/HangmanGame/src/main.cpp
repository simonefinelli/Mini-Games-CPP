/**
 * @file main.cpp
 * @brief Hangman Game.
 *
 * This file includes the core of the Game.\n
 * It will take in input the player's choices and all kind of exceptions.
 *
 * @author SimoX
 * @date 2023-08-03
 */

#include <algorithm>
#include <iostream>
#include "board.h"
#include "core.h"

void play_game();
bool play_again();

int main() {
    do {
        play_game();
    } while(play_again());
    return 0;
}

/**
 * @brief Core skeleton of the game.
 *
 * It initializes the game data, draw and update the board, display the
 * results and check if the game is over.
 */
void play_game() {

    // game initialization
    auto game_data = initialize_game();
    draw_board(game_data);
    // gameplay
    do {
        std::string player_guess = get_player_choice();
        update_board(player_guess, game_data);
        draw_board(game_data);
    } while (!game_is_over(game_data));
    // game results
    display_results(game_data);
}

/**
 * @brief Check if the Player wants to continue.
 *
 * @return True for yes, False for no.
 */
bool play_again() {
    std::string player_input;

    std::cout << "\nWant to play again? ";
    std::cin >> player_input;

    // transform input to lowercase
    std::transform(player_input.begin(), player_input.end(),
                   player_input.begin(), ::tolower);

    return player_input == "y" || player_input == "yes";
}
