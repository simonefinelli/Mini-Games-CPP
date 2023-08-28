/**
 * @file player.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include "player.h"
#include "gui.h"

bool is_valid_placement();
std::tuple<int, int, ship_orientation> get_player_choice(const Ship &s);

void place_ships_on_board(GameData &gd, player_turn t) {
    // get current player
    Player &p = (t == PLAYER_1) ? gd.player1 : gd.player2;

    for (Ship &s : p.ships) {
        std::cout << " -- " << p.name << " -- \n" << std::endl;
        // get users input
        do {
            auto [x, y, o] = get_player_choice(s);
            s.coordinates.x = x;
            s.coordinates.y = y;
            s.orientation = o;
        } while (!is_valid_placement());

        // put ship on Ship Board
        for (int i = 0; i < s.length; i++) {
            if (s.orientation == HORIZONTAL)
                p.ship_board[s.coordinates.x][s.coordinates.y + i].type = s.type;
            else
                p.ship_board[s.coordinates.x + i][s.coordinates.y].type = s.type;
        }

        // update playing field
        draw_playing_field(gd, t);
    }
}

/**
 *
 * @param s The current ship.
 * @return The coordinates and orientation to put the Ship on the board.
 */
std::tuple<int, int, ship_orientation> get_player_choice(const Ship &s) {
    std::string coords {};
    std::string orient {};
    bool is_valid;

    // TODO Check why the second time the input checker doesnt work
    // get ship coordinates
    do {
        std::cout << " > Enter the coordinates for the " << get_ship_name(s.type)
                << ": "; std::cin >> coords;
        std::transform(coords.begin(), coords.end(), coords.begin(), ::toupper);

        if (coords.length() != 2 and (!(coords.at(0) >= 'A' and coords.at(0) <= 'J'))) {
            std::cout << " > Coordinates not valid!" << std::endl;
            is_valid = false;
        } else {
            is_valid = true;
        }

        // clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // clear any error flags
        std::cin.clear();
    } while (!is_valid);

    // get ship orientation
    do {
        std::cout << " > Enter the orientation for the " << get_ship_name(s.type)
                  << ": "; std::cin >> orient;
        std::transform(orient.begin(), orient.end(), orient.begin(), ::tolower);

        if (orient.length() != 1 and (orient.at(0) != 'H' or orient.at(0) != 'V')) {
            std::cout << " > Orientation not valid!" << std::endl;
            is_valid = false;
        } else {
            is_valid = true;
        }

        // clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // clear any error flags
        std::cin.clear();
    } while (!is_valid);

    // transform strings to specific types
    int x = row_to_number(coords.substr(0, 2).c_str()[0]);
    int y = std::stoi(coords.substr(1)) - 1;
    ship_orientation o = (orient == "h") ? HORIZONTAL : VERTICAL;

    return std::make_tuple(x, y, o);
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
