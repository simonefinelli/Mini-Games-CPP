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
const std::regex COORDINATES_PATTERN {COORDS_CHECK_PATTERN};
const std::regex ORIENTATION_PATTERN {ORIENT_CHECK_PATTERN};


bool is_valid_placement(const std::vector<std::vector<ship_unit_area>> &ship_board,
                        const Ship &c_ship, player_turn t);
std::tuple<int, int, ship_orientation> ship_position_choice(const Ship &s);


/**
 * @brief Places the Player's Ships on the Ship Board.
 *
 * This board contains all ships that belong to the current player.
 *
 * @param gd Game data contains all the game session info.
 * @param t The current Player turn.
 */
void place_ships_on_board(GameData &gd, player_turn t) {
    Player &p = (t == PLAYER_1) ? gd.player1 : gd.player2;

    for (Ship &s : p.ships) {
        // get users input or AI choice
        do {
            if (t == PLAYER_1) {
                auto [x, y, o] = ship_position_choice(s);
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
        std::cout << " > I'm thinking ... " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

/**
 * @brief Allows to the Player 1 to chose safely the coordinates of the current
 * ship on the Ship Board.
 *
 * @param s The current ship.
 * @return the coordinates and orientation to put the Ship on the board.
 */
std::tuple<int, int, ship_orientation> ship_position_choice(const Ship &s) {
    std::string coords {};
    std::string orient {};
    bool is_valid;

    // get ship coordinates
    do {
        std::cout << " > Enter the coordinates for the "
                  << get_ship_name(s.type) << ": "; std::cin >> coords;
        if (coordinates_validation(coords)){
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

        if (orient.length() == 1 and std::regex_match(orient, ORIENTATION_PATTERN)) {
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


/**
 * @brief Allows the Players make their attack moves.
 *
 * For Player 1 the choice is made by the user, while for Player 2 (AI) a simple
 * random policy has been implemented.
 *
 * @param gd Game data contains all the game session info.
 * @param t The current Player turn.
 */
void player_move(GameData &gd, player_turn t) {
    if (t == PLAYER_1) {
        std::string coords {};
        int x, y;
        bool is_valid;

        // get coordinates of the location to hit
        do {
            std::cout << " > Where do you want to hit? "; std::cin >> coords;

            if (coordinates_validation(coords)){
                is_valid = true;
            } else {
                std::cout << " > Coordinates not valid!" << std::endl;
                is_valid = false; continue;
            }

            // get coordinates
            x = row_to_number(coords.substr(0, 2).c_str()[0]);
            y = std::stoi(coords.substr(1)) - 1;

            // check if the cell has already been viewed
            if (gd.player1.guess_board[x][y] != UNEXPLORED) {
                std::cout << " > Coordinates already checked!" << std::endl;
                is_valid = false;
            }
        } while (!is_valid);

        // check if an opponent ship is hit and update the Guess Board
        if (gd.player2.ship_board[x][y].type != NO_TYPE) {
            gd.player2.ship_board[x][y].is_hit = true;
            gd.player1.guess_board[x][y] = HIT;

            // update hit ship status
            ship_type curr_ship_type = gd.player2.ship_board[x][y].type;
            auto s = std::find_if(
                gd.player2.ships.begin(),
                gd.player2.ships.end(),
                [curr_ship_type](const Ship& s) {
                    return s.type == curr_ship_type;
                }
            );
            if (s != gd.player2.ships.end()) {
                // Found the struct
                s->sunken_parts++;
                if (s->sunken_parts == s->length) s->status = SUNK;
            }
        } else {
            gd.player1.guess_board[x][y] = MISSED;
        }
    } else {
        // TODO duplicate code
        std::cout << " > I'm thinking ... " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        int x, y;
        bool is_valid;

        do {
            // get coordinates of the location to hit
            x = generate_number(0, FIELD_SIZE - 1);
            y = generate_number(0, FIELD_SIZE - 1);

            // check if the cell has already been viewed
            is_valid = gd.player2.guess_board[x][y] == UNEXPLORED;
        } while (!is_valid);

        // check if an opponent ship is hit and update the Guess Board
        if (gd.player1.ship_board[x][y].type != NO_TYPE) {
            gd.player1.ship_board[x][y].is_hit = true;
            gd.player2.guess_board[x][y] = HIT;

            // update hit ship status
            ship_type curr_ship_type = gd.player1.ship_board[x][y].type;
            auto s = std::find_if(
                    gd.player1.ships.begin(),
                    gd.player1.ships.end(),
                    [curr_ship_type](const Ship& s) {
                        return s.type == curr_ship_type;
                    }
            );
            if (s != gd.player1.ships.end()) {
                // found the ship
                s->sunken_parts++;
                if (s->sunken_parts == s->length) s->status = SUNK;
            }
        } else {
            gd.player2.guess_board[x][y] = MISSED;
        }
    }
}
