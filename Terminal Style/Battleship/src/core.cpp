/**
 * @file core.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <string>
#include "board.h"
#include "config.h"
#include "core.h"
#include "gui.h"
#include "player.h"


Player create_player(const std::string &name = "Player");
void setup_board(const Player& p);


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

    // draw playing field
    draw_boards(p1);

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

//
//void setup_ships(const Player &p) {
//
//    // ShipBoard
//    // for each ship place on the wanted postion
//    for (int i=0; i < SHIPS_NUMBER; i++) {
//        do {
//            // get user coordinates
//            position = get ship coordinates
//            orientation = get ship orientation
//            if is_valid_placement(p, current_ship, position, orientation) {
//
//                break;
//            }
//        } while (true);
//
//        // place the ship on board
//        place_ship_on_board(player, current_ship, position, oerientation);
//
//        // refresh board_game
//        update_board(game_data);
//    }
//
//    // Guess board
//    // empty the board
//}
//
///**
// * @brief Get the Player's Guess.
// *
// * Get the choice of attack of the current Player.
// *
// * @return letter The letter to check.
// */
//std::string get_player_choice(const Player &curr_p) {
//
//    bool correct_input = false;
//    do {
//
//
//    } while (!correct_input);
//
//    return player_input;
//}
//
//bool game_is_over(game_data) {
//
//    return all_ships_sunk(player1) or all_ships_sunk(player2);
//}
//
//bool all_ships_sunk(const Player &p) {
//    for (const Ship &ship : p.ships) {
//        if (ship.status == ALIVE) {
//            return false;
//        }
//    }
//    return true;
//}
