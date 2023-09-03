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
int row_to_number(char l);
void display_results(const GameData &gd, player_turn t);


#endif //BATTLESHIP_GUI_H
