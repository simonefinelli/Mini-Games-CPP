/**
 * @file board.h
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include "ship.h"

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#define FIELD_SIZE 10

 /*
  *  Ship Board Type
  *  Used to create the field game that contains the ships of the current
  *  Player.
  */
typedef struct ShipUnitAreaStatus {
    ship_type type = NO_TYPE;
    bool is_hit = false;
} ship_unit_area;

/*
 * Guess Board Type
 * Used to create the field game that contains the (hidden) ships of the other
 * Player and the ongoing game of the current Player.
 */
typedef enum GuessUnitAreaStatus {
    /*
     * for each piece of the attacker board we can have 3 status: hit, missed
     * and unexplored.
     */
    UNEXPLORED = 0,
    MISSED,
    HIT
} guess_unit_area;

/**
 * @brief Creates either an empty Ship Board or a empty Guess Board.
 *
 * A Ship Board is a playing field where are handled the ships of the current
 * Player.
 *
 * A Guess Board is a playing field where are handled the hits or misses of the
 * current Player against the other Player.
 *
 * @return the an empty Ship or Guess Board.
 */
template <typename T>
std::vector<std::vector<T>> generate_board() {
    // create the empty board
    std::vector<std::vector<T>> board(FIELD_SIZE, std::vector<T>(FIELD_SIZE));

    // reserve space for rows to improve performance
    board.reserve(FIELD_SIZE);
    for (int i = 0; i < FIELD_SIZE; ++i) {
        // reserve space for columns in each row to improve performance
        board[i].reserve(FIELD_SIZE);
    }

    return board;
}

int row_to_number(char l);

#endif //BATTLESHIP_BOARD_H
