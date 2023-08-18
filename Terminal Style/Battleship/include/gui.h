/**
 * @file gui.h
 *
 * @author SimoX
 * @date 2023-08-17
 */

#include "player.h"

#ifndef BATTLESHIP_GUI_H
#define BATTLESHIP_GUI_H

void draw_boards(const Player &p);

void draw_info_desk(const Player &p1, const Player &p2, player_turn turn);

#endif //BATTLESHIP_GUI_H
