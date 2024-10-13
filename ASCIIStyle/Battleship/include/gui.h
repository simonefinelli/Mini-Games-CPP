/**
 * @file gui.h
 *
 * @author SimoX
 * @date 2023-08-17
 */

#include "player.h"

#ifndef BATTLESHIP_GUI_H
#define BATTLESHIP_GUI_H

namespace gui {

    void draw_playing_field(const GameData &gd, player_turn t);

    void display_ai_message();

    void display_enter_coords_message(ship_type type);

    void display_enter_orient_message(ship_type type);

    void display_coords_not_valid_message();

    void display_orient_not_valid_message();

    void display_invalid_placement_message(const std::string &msg);

    void display_hit_message();

    void display_checked_coords_message();

    void display_results(const GameData &gd, player_turn t);

}

#endif //BATTLESHIP_GUI_H
