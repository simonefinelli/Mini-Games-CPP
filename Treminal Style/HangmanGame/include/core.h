#include <string>
#include "config.h"

#ifndef HANGMANGAME_CORE_H
#define HANGMANGAME_CORE_H

GameData initialize_game();
std::string get_player_choice();
void update_board(const std::string &player_guess, GameData &game_data);
bool game_is_over(const GameData &game_data);

#endif //HANGMANGAME_CORE_H
