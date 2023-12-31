/**
 * @file core.h
 * @brief This file and the relative implementation handle the core functions
 * to init and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */



#ifndef SPACEINVADERS_CORE_H
#define SPACEINVADERS_CORE_H

#include "battlefield.h"
#include "spaceship.h"
#include "gui.h"

#define IS_QUIT_CHAR(x) ((x == QUIT_CHAR_UPPER) || (x == QUIT_CHAR_LOWER))

const char QUIT_CHAR_LOWER = 'q';
const char QUIT_CHAR_UPPER = 'Q';

struct FieldGame {
    size window_size{0, 0};
    game_state state{WELCOME_SCREEN};
    int level{0};
    std::array<FieldShield, SHIELD_NUMBER> shields {};
    int wait_time{0}; // milliseconds
};

struct GameData {
    FieldGame field_game{};
    Hero hero{};
    AlienFleet alien_fleet{};
};

GameData initialize_game();

int get_user_input();

void update_game_data(GameData &gd, key user_choice);

void draw_screen_game(GameData &gd);

#endif //SPACEINVADERS_CORE_H
