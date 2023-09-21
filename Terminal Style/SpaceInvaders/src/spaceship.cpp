/**
 * @file spaceship.h
 * @brief This file and the relative header collect oll the data and operation
 * of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <array>
#include "spaceship.h"

// Hero
const std::string HERO_SPRITE[] {" /^\\ ", "==~=="};

/**
 * @brief Populates the Hero structure.
 */
void define_hero(Hero &h) {
    h.name = HERO_NAME;
    h.sprite = {HERO_SPRITE[0], HERO_SPRITE[1]};
    h.lives = HERO_LIVES;
    h.score = 0;
    h.position = {((W_WIDTH / 2 - HERO_SPRITE_WIDTH / 2) - 1),   // -1 because coors starts from 0
                  ((W_HEIGHT - (SPRITE_HEIGHT / 2)) - 1)};  // centre of the screen
    h.equipment.position = {NOT_ON_FIELD, NOT_ON_FIELD};
}

/**
 * Call during game to refresh the state and characteristics of the Hero, like
 * the initial position at every new level.
 */
void refresh_hero(Hero &hero) {
    // TODO to implement
}

/**
 * Call during game to refresh the position of hero's missile.
 */
void refresh_missile(Hero &hero) {
    // TODO to implement
}