/**
 * @file ship.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <vector>
#include <stdexcept>
#include <map>
#include "ship.h"


std::map<ship_type , int> ship_length = {
    {AIRCRAFT_CARRIER, AIRCRAFT_CARRIER_LENGTH},
    {BATTLESHIP, BATTLESHIP_LENGTH},
    {CRUISER, CRUISER_LENGTH},
    {DESTROYER, DESTROYER_LENGTH},
    {SUBMARINE, SUBMARINE_LENGTH},
};


void init_ship(Ship &s, ship_type t, int length);


/**
 * @brief Creates empty Ships.
 *
 * @return a vector contains the 5 Ships.
 */
std::vector<Ship> generate_ships() {

    std::vector<Ship> ships (SHIPS_NUMBER);

    for (ship_type s = AIRCRAFT_CARRIER; s <= SHIPS_NUMBER; s = static_cast<ShipType>(s + 1)) {
        init_ship(ships.at((int) s - 1), s, ship_length[s]);
    }

    return ships;
}

/**
 * @brief Initializes a Ship specifying the Type, the Length and the Status.
 *
 * @param s The Ship.
 * @param t The type of the Ship.
 * @param length The length of the Ship.
 */
void init_ship(Ship &s, ship_type t, int length) {
    s.type = t;
    s.length = length;
    s.status = ALIVE;
}

/**
 * @brief Converts enum type to the real Ship name.
 *
 * @param s The type of the Ship.
 * @return the real name.
 */
std::string get_ship_name(ship_type s) {
    switch (s) {
        case AIRCRAFT_CARRIER:
            return "AIRCRAFT CARRIER";
        case BATTLESHIP:
            return "BATTLESHIP";
        case CRUISER:
            return "CRUISER";
        case DESTROYER:
            return "DESTROYER";
        case SUBMARINE:
            return "SUBMARINE";
        default:
            throw std::runtime_error("The ship type do not exist!");
    }
}

/**
 * @brief Converts enum type to the real Ship name and add the length of the
 * ship well formatted.
 *
 * @param s The type of the Ship.
 * @return the real name with the length of the Ship.
 */
std::string get_ship_name_length(ship_type s) {
    switch (s) {
        case AIRCRAFT_CARRIER:
            return "AIRCRAFT CARRIER [5]";
        case BATTLESHIP:
            return "BATTLESHIP       [4]";
        case CRUISER:
            return "CRUISER          [3]";
        case DESTROYER:
            return "DESTROYER        [2]";
        case SUBMARINE:
            return "SUBMARINE        [3]";
        default:
            throw std::runtime_error("The ship type do not exist!");
    }
}
