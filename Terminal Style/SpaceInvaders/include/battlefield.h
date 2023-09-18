/**
 * @file battlefield.h
 * @brief This file and the relative implementation handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */

#include <string>
#include <vector>
#include "common.h"

#ifndef SPACEINVADERS_BATTLEFIELD_H
#define SPACEINVADERS_BATTLEFIELD_H

typedef enum FieldGameState {
    WELCOME_SCREEN = 0,
    PLAY_SCREEN,
    PLAYER_DEAD_SCREEN,
    GAME_OVER_SCREEN,
    HIGH_SCORES_SCREEN,
    PAUSE_SCREEN
} game_state;

struct FieldShield {
    coords position = {0, 0};
    const std::vector<std::string> sprite = {
            "/#####\\",
            "#######",
            "#/   \\#"
    };
};

struct FieldGame {
    size window_size {0, 0};
    game_state state {WELCOME_SCREEN};
    int level = 0;
};

#endif //SPACEINVADERS_BATTLEFIELD_H
