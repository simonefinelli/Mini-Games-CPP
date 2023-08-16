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
    // players and boards initialization
    // init_player("Player1"); //TODO set this string as default
    // init_player("Player2"); //TODO set this string as default

    // ships positioning
    // setup_ships(Player p); // Player1
    // setup_ships(Player p); // Player2
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

void setup_ships(const Player &p) {

    // ShipBoard
    // for each ship place on the wanted postion
    for (int i=0; i < SHIPS_NUMBER; i++) {
        do {
            // get user coordinates
            position = get ship coordinates
            orientation = get ship orientation
            if is_valid_placement(p, current_ship, position, orientation) {

                break;
            }
        } while (true);

        // place the ship on board
        place_ship_on_board(player, current_ship, position, oerientation);

        // refresh board_game
        update_board(game_data);
    }

    // Guess board
    // empty the board
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

bool game_is_over(game_data) {

    return all_ships_sunk(player1) or all_ships_sunk(player2);
}

bool all_ships_sunk(const Player &p) {
    for (const Ship &ship : p.ships) {
        if (ship.status == ALIVE) {
            return false;
        }
    }
    return true;
}
