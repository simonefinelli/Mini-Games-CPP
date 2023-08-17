/**
 * @file player.h
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <vector>
#include <string>
#include "ship.h"
#include "board.h"

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H


struct Player {
    std::string name;
    std::vector<Ship> ships {};
    std::vector<std::vector<ship_unit_area>> ship_board {};
    std::vector<std::vector<guess_unit_area>> guess_board {};
};

#endif //BATTLESHIP_PLAYER_H
