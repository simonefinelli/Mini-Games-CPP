/**
 * @file core.h
 * @brief This file and the relative implementation handle the core functions
 * to init and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "battlefield.h"
#include "spaceship.h"

#ifndef SPACEINVADERS_CORE_H
#define SPACEINVADERS_CORE_H

struct GameData {
    FieldGame field_game {};
    Hero hero {};

};

GameData initialize_game();

#endif //SPACEINVADERS_CORE_H
