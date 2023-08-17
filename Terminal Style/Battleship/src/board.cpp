/**
 * @file board.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <iostream>
#include <vector>
#include "board.h"
#include "player.h"

using std::vector;


void draw_ship_board(const vector<vector<ship_unit_area>> &ship_board);


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

//bool is_valid_placement(player, current_ship, coordiantes, orientation) {
//    if (orientation == HORIZONTAL) {
//        for (each clolumns) {
//            if (ship overlap other ships or the ship will be off the board horizontally)
//                return false
//        }
//    } else {
//        for (each rows) {
//            if (ship overlap other ships or the ship will be off the board vertically)
//                return false
//        }
//    }
//    return true;
//}

//void place_ship_on_board(player, Ship ship, coordiantes, orientation) {
//    ship.coordinates = coordiantes;
//    ship.orientation = orientation;
//
//
//    // set the ship placeholder on correct position on the board acording to
//    // coordinates.x and coordinates.y
//    if (orientation == HORIZONTAL) {
//
//    } else {
//
//    }
//}

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



