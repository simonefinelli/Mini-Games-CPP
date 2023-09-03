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


std::vector<std::vector<ship_unit_area>> generate_ship_board();

std::vector<std::vector<guess_unit_area>> generate_guess_board();

#endif //BATTLESHIP_BOARD_H
