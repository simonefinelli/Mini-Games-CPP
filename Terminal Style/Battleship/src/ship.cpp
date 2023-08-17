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

void init_ship(Ship &s, ship_type t, int length );


/**
 *
 * @return
 */
std::vector<Ship> generate_ships() {

    std::vector<Ship> ships (SHIPS_NUMBER);

    for (ship_type s = AIRCRAFT_CARRIER; s <= SHIPS_NUMBER; s = static_cast<ShipType>(s + 1)) {
        init_ship(ships.at((int) s - 1), s, ship_length[s]);
    }

    return ships;
}

/**
 *
 * @param s
 * @param t
 * @param length
 */
void init_ship(Ship &s, ship_type t, int length) {
    s.type = t;
    s.length = length;
    s.status = ALIVE;
}
