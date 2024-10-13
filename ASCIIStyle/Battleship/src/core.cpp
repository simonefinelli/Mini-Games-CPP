/**
 * @file core.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <algorithm>
#include <string>
#include "board.h"
#include "core.h"
#include "gui.h"
#include "player.h"


Player create_player(const std::string &name);
bool all_ships_sunk(const Player &p);


/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    Player p1 {};
    Player p2 {};

    // players and boards initialization
    p1 = create_player("Player 1");
    p2 = create_player("AI");

    return {.player1 = p1, .player2 = p2};
}

/**
 * @brief Creates an empty Player.
 *
 * @param name The name of the Player.
 * @return a new Player.
 */
Player create_player(const std::string &name) {
    Player p {
        .name = name,
        .ships = generate_ships(),
        .ship_board = generate_board<ship_unit_area>(),
        .guess_board = generate_board<guess_unit_area>()
    };
    return p;
}

/**
 * @brief Checks if the game is over.
 *
 * The game is over when all the ships of a Player are sunk.
 *
 * @param gd Game data contains all the game session info.
 * @return True if the game is over, False otherwise.
 */
bool game_is_over(const GameData &gd) {
    return all_ships_sunk(gd.player1) or all_ships_sunk(gd.player2);
}

/**
 * @brief Checks for a single Player if all his ships are sunk.
 *
 * @param p Player.
 * @return True if the all ships are sunk, False otherwise.
 */
bool all_ships_sunk(const Player &p) {
    return std::all_of(p.ships.begin(), p.ships.end(),
                       [](Ship s) {return s.status != ALIVE;});
}
