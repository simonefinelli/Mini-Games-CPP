/**
 * @file player.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <iostream>
#include "player.h"
#include "gui.h"

bool is_valid_placement();


void place_ships_on_board(GameData &gd, player_turn t) {
    // get current player
    Player &p = (t == PLAYER_1) ? gd.player1 : gd.player2;
    std::string coordinates {};
    std::string orientation;

    std::cout << p.name << std::endl;
    for (Ship &s : p.ships) {
        // get users input
        do {
            // TODO check if the user's input is correct
            std::cout << "Enter the coordinates (A-z1-10) for the " <<
            get_ship_name(s.type) << ": ";
            std::cin >> coordinates;
            std::cout << "Enter the orientation (h or v) for the " <<
                      get_ship_name(s.type) << ": ";
            std::cin >> orientation;

            s.coordinates.x = row_to_number(coordinates.substr(0, 2).c_str()[0]);
            s.coordinates.y = std::stoi(coordinates.substr(1)) - 1;
            s.orientation = (orientation == "h") ? HORIZONTAL : VERTICAL;
        } while (!is_valid_placement());

        // draw ship on Ship Board
        if (s.orientation == HORIZONTAL) {

        } else {

        }

        // update playing field
        draw_playing_field(gd, t);
    }
}

bool is_valid_placement() {
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
    return true;
}
