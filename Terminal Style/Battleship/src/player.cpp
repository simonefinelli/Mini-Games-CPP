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


void place_ships_on_board(const GameData &gd, player_turn t) {
    // get current player
    Player p = (t == PLAYER_1) ? gd.player1 : gd.player2;
    std::string coordinates {};
    std::string orientation;


    std::cout << p.name << std::endl;
    for (Ship s : p.ships) {
        int i = 0;
        do {
            std::cout << "Enter the coordinates (A-z1-10) of the " <<
            get_ship_name(s.type) << ": ";
            std::cin >> coordinates;
            std::cout << "Enter the orientation (o or v) of the " <<
                      get_ship_name(s.type) << ": ";
            std::cin >> orientation;


            s.coordinates.x = i;
            s.coordinates.y = 2;
            s.orientation = HORIZONTAL;

            // Ship Board
            p.ship_board[0][0].type = s.type;
            p.ship_board[0][0].is_hit = false;

            // TODO check why the ship doesnt show on the board


        } while (!is_valid_placement());

        // update playing field
        draw_playing_field(gd, t);
    }





//    // set the ship placeholder on correct position on the board acording to
//    // coordinates.x and coordinates.y
//    if (orientation == HORIZONTAL) {
//
//    } else {
//
//    }
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
