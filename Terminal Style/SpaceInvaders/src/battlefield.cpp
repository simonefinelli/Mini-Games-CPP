/**
 * @file battlefield.cpp
 * @brief This file and the relative header handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */

#include "battlefield.h"

// prototypes
bool is_shield_collision(const coords& pos, const std::array<FieldShield, SHIELD_NUMBER>& shields, shield_collision& c);

/**
 * @brief Initializes the defensive shields on the game field.
 * 
 * This function sets up the initial positions and IDs for each shield 
 * in the game. It places the shields at a specific distance from the 
 * game boundaries and spaces them evenly across the field.
 * 
 * @param shields A reference to an array of `FieldShield` objects that will be 
 *                initialized.
 */
void init_shields(std::array<FieldShield, SHIELD_NUMBER>& shields) {
    int p = SHIELD_INITIAL_PADDING;  // distance between shields and game boundaries
    int offset = SHIELD_SPACING;  // distance between shields

    for (auto& s : shields) {
        s.id = int(&s - &shields[0]);  // to retrieve the index
        s.position = {p, SHIELD_DISTANCE};
        p += offset;
    }
}

/**
 * @brief Renders all 4 shields on the playing field.
 * 
 * This function iterates over the array of shields and draws each shield 
 * at its respective position on the field using the `gui::draw_sprite()`
 * function.
 * 
 * @param shields A constant reference to an array of `FieldShield` objects 
 *        representing the defensive shields in the game. Each shield's position
 *        and sprite are used to render it on the screen.
 */
void draw_shields_on_field(const std::array<FieldShield, SHIELD_NUMBER>& shields) {
    for (const auto& s: shields) {
        gui::draw_sprite(s.position.x, s.position.y, s.sprite);
    }
}

/**
 * @brief Checks if there is a collision between a hero missile and the shields.
 *
 * @param shields The shields on the playing field.
 * @param missile The hero's missile.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile& m) {
    shield_collision c {};
    if (is_shield_collision(m.position, shields, c)) {
        // remove hit part
        shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
        // reset hero missile
        m.position = {NOT_ON_FIELD, NOT_ON_FIELD};
    }
}

/**
 * @brief Detects and handles collisions between the Alien fleet and shields on 
 *        the playing field.
 * 
 * This function checks for collisions between the aliens and shields, as well as 
 * collisions between the aliens' bombs and shields. The collision detection is 
 * done by examining only the second row of the alien sprite and the bottom row 
 * of the bombs. When a collision is detected, the corresponding part of the 
 * shield is removed, and in the case of a bomb collision, the bomb is also 
 * removed from the field.
 * 
 * @param shields A reference to an array of `FieldShield` objects representing 
 *        the shields on the playing field.
 * @param fleet A reference to the `AlienFleet` object, which contains the aliens 
 *        and their bombs.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER>& shields, AlienFleet& fleet) {
    shield_collision c{};
    coords curr_position;

    // check the Aliens' body and the shields
    int x, y;
    for (const auto& aliens_line : fleet.aliens) {
        for (const auto& a : aliens_line) {
            // check a collision with the bottom row of the Alien
            for (int i = 0; i < SPRITE_WIDTH; i++) {
                x = a.position.x + i;
                y = a.position.y + 1;
                curr_position = {x, y};
                if (a.status == ALIVE and is_shield_collision(curr_position, shields, c)) {
                    // remove hit part
                    shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
                }
            }
        }
    }

    // check the Aliens' bombs and the shields
    for (auto& aliens_line : fleet.aliens) {
        for (auto& a : aliens_line) {
            // check a collision with the bottom row of the bomb
            for (auto& bomb : a.bombs) {
                if (bomb.position.y == NOT_ON_FIELD) continue;
                if (is_shield_collision({bomb.position.x, bomb.position.y + 1}, shields, c)) {
                    // remove hit part
                    shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
                    // remove the bomb from the playing field
                    bomb.position = {NOT_ON_FIELD, NOT_ON_FIELD};
                    fleet.bombs_in_play--;
                }
            }
        }
    }
}

/**
 * @brief Determines if a given position collides with any part of a shield on 
 *        the field.
 * 
 * This function checks whether a specific position (e.g., a missile or bomb's 
 * position) overlaps with any active part of a shield. If a collision is detected,
 * the function records the index of the shield and the specific part that was 
 * hit. If no collision occurs, it returns `false`.
 * 
 * @param pos The coordinates (`coords`) representing the current position 
 *            (e.g., of a missile or bomb) to be checked.
 * @param shields A constant reference to an array of `FieldShield` objects 
 *        representing the shields on the field.
 * @param c A reference to a `shield_collision` object that will be updated with
 *        the shield index and part hit if a collision occurs.
 * 
 * @return bool Returns `true` if a collision with a shield is detected, otherwise 
 *         returns `false`.
 */

bool is_shield_collision(const coords& pos, const std::array<FieldShield, SHIELD_NUMBER>& shields, shield_collision& c) {
    c.shield_idx = NO_SHIELD_COLLISION;
    c.shield_part_hit = {NO_SHIELD_COLLISION, NO_SHIELD_COLLISION};

    if (pos.y == NOT_ON_FIELD) {
        return false;
    }

    // if the missile/bomb is in the field check there is a shield_collision with a shield
    for (const FieldShield& s : shields) {
        if (
            (pos.x >= s.position.x and pos.x < (s.position.x + SHIELD_SPRITE_WIDTH)) and  // shot in shield width
            (pos.y >= s.position.y and pos.y < (s.position.y + SHIELD_SPRITE_HEIGHT)) and  // shot in shield height
            (s.sprite[pos.y - s.position.y][pos.x - s.position.x] != ' ')  // shield_collision with a shield part
            ) {
            // shield collision
            c.shield_idx = s.id;
            c.shield_part_hit = {pos.x - s.position.x, pos.y - s.position.y};  // get part index using row,column tuple
            return true;
        }
    }

    return false;
}
