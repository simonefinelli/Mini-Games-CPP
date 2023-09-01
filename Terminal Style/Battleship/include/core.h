/**
 * @file core.h
 *
 * @author SimoX
 * @date 2023-08-14
 */

#include <string>
#include "player.h"

#ifndef HANGMANGAME_CORE_H
#define HANGMANGAME_CORE_H

GameData initialize_game();
bool game_is_over(const GameData &gd);

#endif //HANGMANGAME_CORE_H
