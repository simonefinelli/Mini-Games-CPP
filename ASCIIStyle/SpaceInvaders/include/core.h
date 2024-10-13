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
#define IS_NEW_GAME_CHAR(x) ((x == NEW_GAME_CHAR_UPPER) || (x == NEW_GAME_CHAR_LOWER))

const char QUIT_CHAR_LOWER = 'q';
const char QUIT_CHAR_UPPER = 'Q';
const char NEW_GAME_CHAR_LOWER = 's';
const char NEW_GAME_CHAR_UPPER = 'S';

struct FieldGame {
    size window_size{0, 0};
    game_state state{WELCOME_SCREEN};
    int level{0};
    std::array<FieldShield, SHIELD_NUMBER> shields{};
    int wait_time{0}; // milliseconds
};

struct GameData {
    FieldGame field_game{};
    Hero hero{};
    AlienFleet alien_fleet{};
    UFO ufo{};

    // overload copy assignment operator
    GameData& operator=(const GameData& other) {
        if (this != &other) {  // Avoid self-assignment
            this->field_game = other.field_game;
            this->hero = other.hero;
            this->alien_fleet = other.alien_fleet;
            this->ufo = other.ufo;
        }
        return *this;
    }
};


// prototypes - external access to the core file
GameData initialize_game();
int get_user_input();
void update_game_data(GameData& gd, key user_choice);
void draw_screen_game(GameData& gd);
void check_game_status(GameData& current_gd);
void pause_game(GameData& gd);

#endif // SPACEINVADERS_CORE_H
