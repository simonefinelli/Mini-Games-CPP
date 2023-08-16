/**
 * @file core.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include "config.h"
#include "core.h"
#include "player.h"

void setup_board(const Player& p);

/**
 * @brief Create the two Players.
 */
GameData initialize_game() {
    // initialize the players
    // init_player("Player1"); //TODO set this string as default
    // init_player("Player2"); //TODO set this string as default

    // initialize the boards
    // setup_board(Player p); // Player1
    // setup_board(Player p); // Player2
}

Player init_player(const std::string &name) {
    Player p {
        .name = name,
        .ships = generate_ships(),
        .ship_board = generate_ship_board(),
        .guess_board = generate_guess_board()
    };
    return p;
}

void setup_board(const Player &p) {
    // clear_board();

}

/**
 * @brief Get the Player's Guess.
 *
 * Get the choice of attack of the current Player.
 *
 * @return letter The letter to check.
 */
std::string get_player_choice(const Player &curr_p) {

    bool correct_input = false;
    do {


    } while (!correct_input);

    return player_input;
}
