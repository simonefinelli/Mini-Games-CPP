/**
 * @file gui.h
 *
 * @author SimoX
 * @date 2023-08-17
 */

#include "player.h"

#ifndef BATTLESHIP_GUI_H
#define BATTLESHIP_GUI_H

void draw_playing_field(const GameData &gd, player_turn t);

void display_results(const GameData &gd, player_turn t);

void display_ai_message();

void display_coords_not_valid_message();

#endif //BATTLESHIP_GUI_H
