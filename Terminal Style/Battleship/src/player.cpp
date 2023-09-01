/**
 * @file player.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <algorithm>
#include <iostream>
#include <regex>
#include <thread>
#include <tuple>
#include "gui.h"
#include "player.h"
#include "utils.h"

#define COORDS_CHECK_PATTERN "^[a-jA-J](?:[1-9]|10)?$"
#define ORIENT_CHECK_PATTERN "^[HhVv]$"
const std::regex coordinates_pattern {COORDS_CHECK_PATTERN};
const std::regex orientation_pattern {ORIENT_CHECK_PATTERN};


bool is_valid_placement(const std::vector<std::vector<ship_unit_area>> &ship_board,
                        const Ship &c_ship, player_turn t);
std::tuple<int, int, ship_orientation> get_player_choice(const Ship &s);


/**
 *
 * @param gd
 * @param t
 */
void place_ships_on_board(GameData &gd, player_turn t) {
    Player &p = (t == PLAYER_1) ? gd.player1 : gd.player2;

    for (Ship &s : p.ships) {
        // get users input or PC choice
        do {
            if (t == PLAYER_1) {
                auto [x, y, o] = get_player_choice(s);
                s.coordinates.x = x;
                s.coordinates.y = y;
                s.orientation = o;
            } else {
                // generate random coordinates and orientation for the Player2
                s.coordinates.x = generate_number(0, FIELD_SIZE - 1);
                s.coordinates.y = generate_number(0, FIELD_SIZE - 1);
                s.orientation = static_cast<ShipOrientation>(generate_number(1,2));
            }
        } while (!is_valid_placement(p.ship_board, s, t));

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

    // simulate PC thinking sleeping for 3 seconds
    if (t == PLAYER_2) {
        std::cout << " > I'm thinking ..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
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

    // get ship coordinates
    do {
        std::cout << " > Enter the coordinates for the "
                  << get_ship_name(s.type) << ": "; std::cin >> coords;

        if (coords.length() >= 2 and std::regex_match(coords, coordinates_pattern)) {
            std::transform(coords.begin(), coords.end(),
                           coords.begin(), ::toupper);
            is_valid = true;
        } else {
            std::cout << " > Coordinates not valid!" << std::endl;
            is_valid = false;
        }
    } while (!is_valid);

    // get ship orientation
    do {
        std::cout << " > Enter the orientation for the "
                  << get_ship_name(s.type) << ": "; std::cin >> orient;

        if (orient.length() == 1 and std::regex_match(orient, orientation_pattern)) {
            std::transform(orient.begin(), orient.end(),
                           orient.begin(), ::toupper);
            is_valid = true;
        } else {
            std::cout << " > Orientation not valid!" << std::endl;
            is_valid = false;
        }
    } while (!is_valid);

    // transform strings to specific types
    int x = row_to_number(coords.substr(0, 2).c_str()[0]);
    int y = std::stoi(coords.substr(1)) - 1;
    ship_orientation o = (orient == "H") ? HORIZONTAL : VERTICAL;

    return std::make_tuple(x, y, o);
}


/**
 * @brief Check if the current ship overlaps other ships or if cannot be
 * placed because exceeds the game board.
 *
 * @param ship_board The Ship Board.
 * @param c_ship The current Ship to be positioning.
 * @return True if the ship can be places, False otherwise.
 */
bool is_valid_placement(const std::vector<std::vector<ship_unit_area>> &ship_board,
                        const Ship &c_ship, player_turn t) {
    std::string info {};

    if (c_ship.orientation == HORIZONTAL) {
        // the ship will be off the board horizontally
        if (c_ship.coordinates.y + c_ship.length > FIELD_SIZE) {
            info = " > The ship cannot be placed as it exceeds the playing field "
                   "horizontally!";
            if (t == PLAYER_1) std::cout << info<< std::endl;
            return false;
        }
        // ship overlap other ships
        for (int i = 0; i < c_ship.length; i++) {
            if (ship_board[c_ship.coordinates.x][c_ship.coordinates.y + i].type != NO_TYPE) {
                info = " > The ship cannot be placed as it overlaps another ship!";
                if (t == PLAYER_1) std::cout << info<< std::endl;
                return false;
            }
        }
    } else {
        // the ship will be off the board horizontally
        if (c_ship.coordinates.x + c_ship.length > FIELD_SIZE) {
            info = " > The ship cannot be placed as it exceeds the playing field "
                   "vertically!";
            if (t == PLAYER_1) std::cout << info<< std::endl;
            return false;
        }
        // ship overlap other ships
        for (int i = 0; i < c_ship.length; i++) {
            if (ship_board[c_ship.coordinates.x + i][c_ship.coordinates.y].type != NO_TYPE) {
                info = " > The ship cannot be placed as it overlaps another ship!";
                if (t == PLAYER_1) std::cout << info<< std::endl;
                return false;
            }
        }
    }

    return true;
}
