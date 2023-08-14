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
typedef struct ShipUnitAreaStatus {  // ShipPartType
    ship_type type = NO_TYPE;
    bool is_hit = false;
} ship_unit_area;

/*
 * Guess Board Type
 * Used to create the field game that contains the (hidden) ships of the other
 * Player and the ongoing game of the current Player.
 */
typedef enum BoardUnitAreaStatus {  // GuessType
    /*
     * For each piece of the attacker board we can have 3 status: hit, missed
     * and unexplored.
     */
    UNEXPLORED = 0,
    MISSED,
    HIT
} board_unit_area;

#endif //BATTLESHIP_BOARD_H
