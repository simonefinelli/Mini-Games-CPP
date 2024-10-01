/**
 * @file battlefield.cpp
 * @brief This file and the relative header handle the playing field.
 * @author SimoX
 * @date 2023-09-09
 */

#include "battlefield.h"

// prototypes
bool is_shield_collision(const coords &pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c);

/**
 * @brief Initializes the defensive shields on the game field.
 * 
 * This function sets up the initial positions and IDs for each shield 
 * in the game. It places the shields at a specific distance from the 
 * game boundaries and spaces them evenly across the field.
 * 
 * Workflow:
 * - Starts by setting the initial x-coordinate (`x`) to `SHIELD_INITIAL_PADDING`, 
 *    representing the padding between the first shield and the game boundary.
 * - Defines the spacing between shields using `SHIELD_SPACING`.
 * - Iterates over the array of shields:
 *   - Assigns each shield a unique ID based on its index within the array.
 *   - Sets the position of each shield using the current x-coordinate and 
 *      the constant horizontal distance `SHIELD_DISTANCE`.
 *   - Increments the x-coordinate by the spacing value to position the next 
 *      shield.
 * 
 * @param shields A reference to an array of `FieldShield` objects that will be 
 *                initialized.
 */
void init_shields(std::array<FieldShield, SHIELD_NUMBER> &shields) {
    int p = SHIELD_INITIAL_PADDING;  // distance between shields and game boundaries
    int offset = SHIELD_SPACING;  // distance between shields

    for (auto &s : shields) {
        s.id = int(&s - &shields[0]);  // to retrieve the index
        s.position = {p, SHIELD_DISTANCE};
        p += offset;
    }
}

/**
 * @brief Draws all 4 shields on the field.
 *
 * @param field_game Playing field.
 */
void draw_shields_on_field(const std::array<FieldShield, SHIELD_NUMBER> &shields) {
    for (const auto &s: shields) {
        gui::draw_sprite(s.position.x, s.position.y, s.sprite);
    }
}

/**
 * @brief Checks if there is a collision between a hero missile and the shields.
 *
 * @param shields The shields on the playing field.
 * @param missile The hero missile.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile &m) {
    shield_collision c {};
    if (is_shield_collision(m.position, shields, c)) {
        // remove hit part
        shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
        // reset hero missile
        m.position = {NOT_ON_FIELD, NOT_ON_FIELD};
    }
}

/**
 * @brief The function checks if there was a collision Alien with shields.
 * To check fo a collision we only check for the second row of the sprite.
 *
 * @param shields Shields into the playing field.
 * @param fleet The Alien Fleet.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, AlienFleet &fleet) {
    shield_collision c {};
    coords curr_position;

    // check the Aliens' body and the shields
    int x, y;
    for (const auto &aliens_line : fleet.aliens) {
        for (const auto &a : aliens_line) {
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
    for (auto &aliens_line : fleet.aliens) {
        for (auto &a : aliens_line) {
            // check a collision with the bottom row of the bomb
            for (auto &bomb : a.bombs) {
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
 * @brief Checks if there is a collision between a missile, a bomb or an Alien
 * and one of the shields.
 *
 * @param pos Position of the Hero missile, the Alien bomb or Alien spaceship.
 * @param shields Shields in the playing field.
 * @param c with a shield_collision the structure is filled using the index of the
 *          Shield hit, and the coordinates of the its hit part, -1 otherwise.
 * @return True if there was an hit, False otherwise.
 */
bool is_shield_collision(const coords &pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c) {
    c.shield_idx = NO_SHIELD_COLLISION;
    c.shield_part_hit = {NO_SHIELD_COLLISION, NO_SHIELD_COLLISION};

    if (pos.y == NOT_ON_FIELD) {
        return false;
    }

    // if the missile/bomb is in the field check there is a shield_collision with a shield
    for (const FieldShield &s : shields) {
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
