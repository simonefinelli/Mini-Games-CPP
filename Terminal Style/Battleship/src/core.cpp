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


Player create_player(const std::string &name = "Player");
bool all_ships_sunk(const Player &p);

/**
 * @brief Create the two Players.
 *
 * @return The game data of the two Players.
 */
GameData initialize_game() {
    Player p1 {};
    Player p2 {};

    // players and boards initialization
    p1 = create_player();
    p2 = create_player();

    return {.player1 = p1, .player2 = p2};
}

Player create_player(const std::string &name) {
    // Players' IDs
    static int player_counter = 1;

    Player p {
        .name = name + std::to_string(player_counter),
        .ships = generate_ships(),
        .ship_board = generate_ship_board(),
        .guess_board = generate_guess_board()
    };

    player_counter++; // increase the progressive number of IDs
    return p;
}

bool game_is_over(const GameData &gd) {

    return all_ships_sunk(gd.player1) or all_ships_sunk(gd.player2);
}

bool all_ships_sunk(const Player &p) {
//    for (const Ship &ship : p.ships) {
//        if (ship.status == ALIVE) {
//            return false;
//        }
//    }



    return std::all_of(p.ships.begin(), p.ships.end(), [](Ship s) {
        return s.status != ALIVE;
    });

//    return true;
}
