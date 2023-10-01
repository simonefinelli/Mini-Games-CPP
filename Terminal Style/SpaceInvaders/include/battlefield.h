/**
 * @file battlefield.h
 * @brief This file and the relative implementation handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */

#include <array>
#include <string>
#include <vector>
#include "common.h"
#include "gui.h"

#ifndef SPACEINVADERS_BATTLEFIELD_H
#define SPACEINVADERS_BATTLEFIELD_H

#define SHIELD_NUMBER 4
#define SHIELD_DISTANCE 36
#define SHIELD_PADDING 8
#define SHIELD_INITIAL_PADDING 10
#define SHIELD_SPRITE_HEIGHT 3
#define SHIELD_SPRITE_WIDTH 7
#define SHIELD_SPACING (SHIELD_SPRITE_WIDTH + SHIELD_PADDING)

typedef enum FieldGameState {
    WELCOME_SCREEN = 0,
    PLAY_SCREEN,
    PLAYER_DEAD_SCREEN,
    GAME_OVER_SCREEN,
    HIGH_SCORES_SCREEN,
    PAUSE_SCREEN
} game_state;

struct FieldShield {
    int id = 0;
    coords position = {0, 0};
    std::array<std::string, SHIELD_SPRITE_HEIGHT> sprite = {
            "/#####\\",
            "#######",
            "#/   \\#"
    };
};

struct FieldGame {
    size window_size {0, 0};
    game_state state {WELCOME_SCREEN};
    int level = 0;
    std::array<FieldShield, SHIELD_NUMBER> shields {};
};

void init_shields(std::array<FieldShield, SHIELD_NUMBER> &shields);

void draw_shields_on_field(const std::array<FieldShield, SHIELD_NUMBER> &shields);

#endif //SPACEINVADERS_BATTLEFIELD_H
