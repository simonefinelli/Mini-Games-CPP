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
 * @brief Transforms a board raw in an integer.
 *
 * @param l Letter that indicates the row of the Board.
 * @return the relative numerical index.
 */
int row_to_number(char l) {
    switch (l) {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        default:
            return -1;
    }
}

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
