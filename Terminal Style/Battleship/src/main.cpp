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
#include "gui.h"

void play_game();
bool play_again();
void switch_player(player_turn &t);

int main() {
    do {
        play_game();
    } while (play_again());
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
    // draw playing field
    draw_playing_field(game_data, PLAYER_1);
    // ships positioning
    place_ships_on_board(game_data, PLAYER_1);
    place_ships_on_board(game_data, PLAYER_2);
    // update player turn on screen
    draw_playing_field(game_data, PLAYER_1);

    // game play
    player_turn turn = PLAYER_1;
    do {
        player_move(game_data, turn); // TODO
        draw_playing_field(game_data, turn);
        switch_player(turn);

    } while (!game_is_over(game_data));

    // game results
    // display_results(game_data);
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

void switch_player(player_turn &t) {
    (t == PLAYER_1) ? t = PLAYER_2 : t = PLAYER_1;
}


