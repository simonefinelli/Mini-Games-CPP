/**
 * @file main.cpp
 *
 * @brief Battleship
 *
 * This file includes the core of the Game.\n
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <algorithm>
#include <iostream>
#include "board.h"
#include "core.h"
#include "player.h"
#include "ship.h"

void play_game();
bool play_again();

int main() {
    do {
        play_game();
    } while (play_again());
    return 0;
}

/** TODO
 * @brief Core skeleton of the game.
 *
 * It initializes the game data, draw and update the board, display the
 * results and check if the game is over.
 */
void play_game() {
    // game initialization
    auto game_data = initialize_game();

//    // ships positioning on the playing field
//    setup_ships(game_data.player1); // Player1
//    setup_ships(game_data.player2); // Player2

//    std::string turn = game_data.player1.name;
//    // gameplay
//    do {
//        player_guess = get_player_choice();
//        update_board(player_guess, game_data);
//        switch_player();
//
//    } while (!game_is_over(game_data));
//    // game results
//    display_results(game_data);
}

/** TODO
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


