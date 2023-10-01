/**
 * @file spaceship.h
 * @brief This file and the relative header collect oll the data and operation
 * of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <array>
#include "spaceship.h"

bool is_collision(const coords &shot_pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, collision &c);

/**
 * @brief Populates the Hero structure.
 */
void init_hero(Hero &h) {
    h.name = HERO_NAME;
    h.lives = HERO_LIVES;
    h.score = 0;
    h.position = {((W_WIDTH / 2 - HERO_SPRITE_WIDTH / 2) - 1),   // -1 because coords start from 0
                  ((W_HEIGHT - (SPRITE_HEIGHT / 2)) - 1)};  // centre of the screen
    h.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
}

/**
 * @brief Set the first position of the Hero missile.
 * Note that a missile can only be launched if there is no other missile
 * previously launched in the game screen.
 * A missile is destroyed when it hits an alien spaceship or when it reaches the
 * end of the playing field.
 *
 * @param h The Hero object.
 */
void hero_init_shoot(Hero &h) {
    if (h.missile.position.x == NOT_ON_FIELD or h.missile.position.y == NOT_ON_FIELD) {
        // set initial position if the missile is not on field
        h.missile.position.y = h.position.y;  // same position of hero spaceship head
        h.missile.position.x = h.position.x + (HERO_SPRITE_WIDTH / 2);  // center of the hero
    }
}

/**
 * @brief Checks if the new hero spaceship position is in the game boundaries,
 * than update the hero position.
 *
 * @param h The Hero object.
 * @param peace The offset to apply to the current hero position.
 */
void move_hero(Hero &h, int peace) {
    if ((h.position.x + peace < 0) or ((h.position.x + peace + HERO_SPRITE_WIDTH) > W_WIDTH))
        return;
    h.position.x = h.position.x + peace;
}

/**
 * @brief Updates the position of the Hero missile at each frame.
 * The missile will be launched towards upwards, until it reaches an alien or
 * the end of the playing field.
 *
 * @param h The Hero object.
 */
void refresh_missile_position(Hero &h) {
    if (h.missile.position.x != NOT_ON_FIELD) {
        h.missile.position.y -= MISSILE_PACE;

        // check if the missile exits from boundaries
        if (h.missile.position.y < 0) {
            h.missile.position.x = NOT_ON_FIELD;
            h.missile.position.y = NOT_ON_FIELD;
        }
    }
}

/**
 * @brief Checks if there is a collision between a missile/bomb and one of the
 * shields.
 *
 * @param shot_pos Position of the Hero missile or the Alien bomb.
 * @param shields Shields in the playing field.
 * @param c with a collision the structure is filled using the index of the
 *          Shield hit, and the coordinates of the its hit part, -1 otherwise.
 * @return True if there was an hit, False otherwise.
 */
bool is_collision(const coords &shot_pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, collision &c) {
    c.shield_idx = NO_COLLISION;
    c.shield_part_hit = {NO_COLLISION, NO_COLLISION};

    // if the missile/bomb is in the field check there is a collision with a shield
    if (shot_pos.y != NOT_ON_FIELD) {
        for (const FieldShield &s : shields) {
            if (
                (shot_pos.x >= s.position.x and shot_pos.x < (s.position.x + SHIELD_SPRITE_WIDTH)) and  // shot in shield width
                (shot_pos.y >= s.position.y and shot_pos.y < (s.position.y + SHIELD_SPRITE_HEIGHT)) and  // shot in shield height
                (s.sprite[shot_pos.y - s.position.y][shot_pos.x - s.position.x] != ' ')  // collision with a shield part
            ) {
                // collision
                c.shield_idx = s.id;
                c.shield_part_hit = {shot_pos.x - s.position.x, shot_pos.y - s.position.y};  // get part index using row,column tuple
                return true;
            }
        }
    }

    c.shield_idx = -1;
    c.shield_part_hit = {NO_COLLISION, NO_COLLISION};
    return false;
}

/**
 * TODO
 * @param shields
 * @param missile
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile &m) {
    collision c {};
    if (is_collision(m.position, shields, c)) {
        // remove hit part
        shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
        // reset hero missile
        m.position = {NOT_ON_FIELD, NOT_ON_FIELD};
    }
}

/**
 * TODO
 * @param f
 */
void init_fleet(AlienFleet &f) {

}
