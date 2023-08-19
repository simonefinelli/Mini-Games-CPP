/**
 * @file board.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <vector>
#include "board.h"
#include "player.h"

using std::vector;


/**
 * @brief Create an empty Ship Board.
 *
 * A Ship Board is a playing field where are handled the ships of the current
 * Player.
 *
 * @return board The empty board.
 */
vector<vector<ship_unit_area>> generate_ship_board() {
    // create the empty Ship Board
    vector<vector<ship_unit_area>> board (FIELD_SIZE,
        vector<ship_unit_area>(FIELD_SIZE));

    return board;
}

/**
 * @brief Create an empty Guess Board.
 *
 * A Guess Board is a playing field where are handled the hits or misses of the
 * current Player against the other Player.
 *
 * @return The empty board.
 */
vector<vector<guess_unit_area>> generate_guess_board() {
    // create the empty Guess Board
    vector<vector<guess_unit_area>> board(FIELD_SIZE,
        vector<guess_unit_area>(FIELD_SIZE, UNEXPLORED));

    return board;
}



//update_board(guess, current_player, other_player) {
//    // if current_plaer guess the postion of one of the other player boat we have
//    // an HIT
//        // update the Guess Board with a 'X' in the unit area of the other player
//        //
//        // otherwise '~' (MISS)
//    if () {
//        // hit
//        // when a ship is all sunk then status is setted to SUNK
//        return ShipType  // the ship hit
//    } else {
//        // miss
//        return NO_TYPE;
//    }
//}
