/**
 * @file battlefield.h
 * @brief This file and the relative implementation handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */


#ifndef SPACEINVADERS_BATTLEFIELD_H
#define SPACEINVADERS_BATTLEFIELD_H

#include <array>
#include <string>
#include <vector>
#include "gui.h"
#include "spaceship.h"

#define SHIELD_NUMBER 4
#define SHIELD_PADDING 10
#define SHIELD_INITIAL_PADDING 11
#define SHIELD_SPRITE_HEIGHT 3
#define SHIELD_SPRITE_WIDTH 7
#define SHIELD_SPACING (SHIELD_SPRITE_WIDTH + SHIELD_PADDING)
#define NO_SHIELD_COLLISION (-1)
#define SHIELD_DISTANCE (INITIAL_HERO_Y_POSITION - SHIELD_SPRITE_HEIGHT - 1)

const std::string WELCOME_STRING{"Welcome to ASCII Space Invaders"};
const std::string LEVEL_STRING{"LEVEL"};
const std::string GAME_OVER_STRING{"- Game Over -"};
const std::string START_NEW_GAME_STRING{"Press 'S' to start..."};

typedef struct ShieldCollisionInfo {
    int shield_idx = NO_SHIELD_COLLISION;
    coords shield_part_hit = {NO_SHIELD_COLLISION, NO_SHIELD_COLLISION};
} shield_collision;

typedef enum FieldGameState {
    WELCOME_SCREEN = 0,
    PLAY_SCREEN,
    PLAYER_DEAD_SCREEN,
    GAME_OVER_SCREEN,
    INTERVAL_LEVEL_SCREEN
} game_state;

struct FieldShield {
    int id = 0;
    coords position {0, 0};
    std::array<std::string, SHIELD_SPRITE_HEIGHT> sprite = {
            "/#####\\",
            "#######",
            "#/   \\#"
    };
};

/// Prototypes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void init_shields(std::array<FieldShield, SHIELD_NUMBER> &shields);

void draw_shields_on_field(const std::array<FieldShield, SHIELD_NUMBER> &shields);

void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, AlienFleet &fleet);

void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile &m);

#endif //SPACEINVADERS_BATTLEFIELD_H
