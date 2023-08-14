/**
 * @file core.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include "player.h"
#include "core.h"

/**
 * @brief Create the two Players.
 */
GameData initialize_game() {
    // init_player("Player1"); //TODO set this string as default
    // init_player("Player2"); //TODO set this string as default
}

Player init_player(std::string name) {
    Player p {
        .name = name,
        .ships = generate_ships(),
        .ship_board = generate_ship_board(),
        .guess_board = generate_guess_board()
    };
    return p;
}
