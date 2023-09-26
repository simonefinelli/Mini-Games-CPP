/**
 * @file battlefield.cpp
 * @brief This file and the relative header handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */

#include "battlefield.h"


/**
 * @brief Calculates the right position of each 4 shields in the game.
 *
 * @param shields
 */
void init_shields(std::array<FieldShield, SHIELD_NUMBER> &shields) {
    int offset = SHIELD_SPACING;  // distance between shields
    int x = SHIELD_PADDING;  // distance between shields and game boundaries

    for (auto &s : shields) {
        s.position = {x, SHIELD_DISTANCE};
        x += offset;
    }
}

/**
 *
 * @param field_game
 */
void draw_shields_on_field(const std::array<FieldShield, SHIELD_NUMBER> &shields) {
    for (const auto &s: shields) {
        gui::draw_sprite(s.position.x, s.position.y, s.sprite);
    }
}