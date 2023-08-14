/**
 * @file player.h
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <string>
#include "ship.h"
#include "board.h"

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

struct Player {
    std::string name;
    Ship ships[SHIPS_NUMBER];
    ship_unit_area ship_board[FIELD_SIZE][FIELD_SIZE] {};
    board_unit_area guess_board[FIELD_SIZE][FIELD_SIZE] {};
};

#endif //BATTLESHIP_PLAYER_H
