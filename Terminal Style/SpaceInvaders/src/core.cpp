/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "core.h"

// playing field
#define W_WIDTH 68 // columns
#define W_HEIGHT 100 // rows

// hero
#define HERO_NAME "Player1"
#define HERO_SPRITE_WIDTH 5
#define HERO_SPRITE_HEIGHT 2
#define HERO_LIVES 3


/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    // define field size (window size)
    GameData gm {};
    gm.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gm.field_game.state = PLAY_SCREEN; // TODO after change with WELCOME_SCREEN
    gm.field_game.level = 1;  // first level

    // define Hero
    gm.hero.name = HERO_NAME;
    gm.hero.dimension = {HERO_SPRITE_WIDTH, HERO_SPRITE_HEIGHT};
    gm.hero.lives = HERO_LIVES;
    gm.hero.score = 0;
    gm.hero.position = {((W_WIDTH / 2 - HERO_SPRITE_WIDTH / 2) - 1),   // -1 because coors starts from 0
                        ((W_HEIGHT - (HERO_SPRITE_HEIGHT / 2)) - 1)};  // centre of the screen
    gm.hero.equipment.position = {NOT_ON_FIELD, NOT_ON_FIELD};


    return {};
}


