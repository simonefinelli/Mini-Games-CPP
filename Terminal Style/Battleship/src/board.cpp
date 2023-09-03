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
 * @brief Creates an empty Ship Board.
 *
 * A Ship Board is a playing field where are handled the ships of the current
 * Player.
 *
 * @return the empty Ship Board.
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
 * @return the empty Guess Board.
 */
vector<vector<guess_unit_area>> generate_guess_board() {
    // create the empty Guess Board
    vector<vector<guess_unit_area>> board(FIELD_SIZE,
        vector<guess_unit_area>(FIELD_SIZE, UNEXPLORED));

    return board;
}
