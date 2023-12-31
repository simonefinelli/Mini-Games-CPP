/**
 * @file ship.h
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <string>
#include <vector>

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#define SHIPS_NUMBER 5
#define AIRCRAFT_CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define CRUISER_LENGTH 3
#define SUBMARINE_LENGTH 3
#define DESTROYER_LENGTH 2

typedef enum ShipType {
    NO_TYPE = 0,
    AIRCRAFT_CARRIER,
    BATTLESHIP,
    CRUISER,
    SUBMARINE,
    DESTROYER
} ship_type;

typedef enum ShipOrientation {
    NO_ORIENTATION = 0,
    HORIZONTAL,
    VERTICAL
} ship_orientation;

typedef struct ShipCoordinates {
    int x = -1;  // rows (A-J)
    int y = -1;  // cols (1-10)
} ship_coordinates;

typedef enum ShipStatus {
    NO_STATUS = 0,
    SUNK,
    ALIVE
} ship_status;

struct Ship {
    ship_type type = NO_TYPE;
    int length = 0;
    ship_orientation orientation = NO_ORIENTATION;
    ship_coordinates coordinates;
    ship_status status = NO_STATUS;
    int sunken_parts = 0;
};


std::vector<Ship> generate_ships();

std::string get_ship_name(ship_type s);

std::string get_ship_name_length(ship_type s);

#endif //BATTLESHIP_SHIP_H
