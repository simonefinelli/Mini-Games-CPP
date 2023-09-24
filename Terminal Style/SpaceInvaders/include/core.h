/**
 * @file core.h
 * @brief This file and the relative implementation handle the core functions
 * to init and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "battlefield.h"
#include "spaceship.h"
#include "gui.h"

#ifndef SPACEINVADERS_CORE_H
#define SPACEINVADERS_CORE_H

const char QUIT_CHAR_LOWER = 'q';
const char QUIT_CHAR_UPPER = 'Q';
#define IS_QUIT_CHAR(x) ((x == QUIT_CHAR_UPPER) || (x == QUIT_CHAR_LOWER))

struct GameData {
    FieldGame field_game {};
    Hero hero {};
};

GameData initialize_game();

int get_user_input();

void update_game_data(GameData &gd, key user_choice);

void draw_screen_game(const GameData &gd);

#endif //SPACEINVADERS_CORE_H
