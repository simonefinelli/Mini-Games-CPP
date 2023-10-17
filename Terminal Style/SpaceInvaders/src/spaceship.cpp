/**
 * @file spaceship.h
 * @brief This file and the relative header collect oll the data and operation
 * of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <array>
#include <iostream>
#include "spaceship.h"

bool is_collision(const coords &shot_pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c);
void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position);
bool is_collision(const coords &shot_pos, const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens, alien_collision &c);
void reset_fleet_speed(AlienFleet &fleet);

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
 * @brief Checks if there is a shield_collision between a missile/bomb and one of the
 * shields.
 *
 * @param shot_pos Position of the Hero missile or the Alien bomb.
 * @param shields Shields in the playing field.
 * @param c with a shield_collision the structure is filled using the index of the
 *          Shield hit, and the coordinates of the its hit part, -1 otherwise.
 * @return True if there was an hit, False otherwise.
 */
bool is_collision(const coords &shot_pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c) {
    c.shield_idx = NO_COLLISION;
    c.shield_part_hit = {NO_COLLISION, NO_COLLISION};

    if (shot_pos.y == NOT_ON_FIELD) {
        return false;
    }

    // if the missile/bomb is in the field check there is a shield_collision with a shield
    for (const FieldShield &s : shields) {
        if (
            (shot_pos.x >= s.position.x and shot_pos.x < (s.position.x + SHIELD_SPRITE_WIDTH)) and  // shot in shield width
            (shot_pos.y >= s.position.y and shot_pos.y < (s.position.y + SHIELD_SPRITE_HEIGHT)) and  // shot in shield height
            (s.sprite[shot_pos.y - s.position.y][shot_pos.x - s.position.x] != ' ')  // shield_collision with a shield part
        ) {
            // shield collision
            c.shield_idx = s.id;
            c.shield_part_hit = {shot_pos.x - s.position.x, shot_pos.y - s.position.y};  // get part index using row,column tuple
            return true;
        }
    }

    return false;
}

/**
 * @brief Checks if there is a collision between a hero missile and the shields.
 *
 * @param shields The shields on the playing field.
 * @param missile The hero missile.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile &m) {
    shield_collision c {};
    if (is_collision(m.position, shields, c)) {
        // remove hit part
        shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
        // reset hero missile
        m.position = {NOT_ON_FIELD, NOT_ON_FIELD};
    }
}

/**
 * @brief Creates the Alien Fleet.
 * The Fleet is created by placing the highest ranking aliens in the first
 * positions and then the lowest ranking aliens in order to emphasize the way in
 * which they are displayed on the playing field.
 *
 * @param f
 */
void init_fleet(AlienFleet &f) {
    f.start_position = {INITIAL_FLEET_X_POSITION, INITIAL_FLEET_Y_POSITION};
    f.bombs_in_play = 0;
    f.movement_speed = 30;
    f.attack_direction = RIGHT_DIRECTION;
    f.population = int(std::end(f.aliens) - std::begin(f.aliens) );
    f.animation_frame = FRAME_1;
    // init aliens based on fleet starting position
    int attack_line = ALIEN_ROWS;
    int x_offset = 0, y_offset = 0;
    for (auto &aliens_line : f.aliens) {
        for (auto &alien : aliens_line) {
            if (attack_line == 5) {
                init_alien(alien, FIRST_CLASS, x_offset, y_offset, f.start_position);
            } else if (attack_line == 4 or attack_line == 3) {
                init_alien(alien, SECOND_CLASS, x_offset, y_offset, f.start_position);
            } else {  // line 2 and line 1
                init_alien(alien, THIRD_CLASS, x_offset, y_offset, f.start_position);
            }
            x_offset += X_OFFSET_BETWEEN_ALIEN;
        }
        y_offset += Y_OFFSET_BETWEEN_ALIEN;
        x_offset = 0;  // reset column index
        attack_line--;
    }
}

/**
 * @brief Initializes the single Alien taking into account its Class.
 *
 * @param a The Alien object.
 * @param type The Class of the Alien.
 */
void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position) {
    switch (type) {
        case FIRST_CLASS:
            a.type = FIRST_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {{{"/oo\\", "<  >"}, {"/oo\\", "/^^\\"}}};
            a.points = FIRST_CLASS_PTS;
            break;
        case SECOND_CLASS:
            a.type = SECOND_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {{{" 66 ", "|\\/|"}, {"|66|", "/  \\"}}};
            a.points = SECOND_CLASS_PTS;
            break;
        case THIRD_CLASS:
            a.type = THIRD_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {{{"(--)", "/  \\"}, {"(--)", " <> "}}};
            a.points = THIRD_CLASS_PTS;
            break;
        default: ;
    }
    a.status = ALIVE;
}

/**
 * @brief Checks if there is a collision between a missile and one of the
 * Alien in the fleet.
 *
 * @param shot_pos Position of the Hero missile or the Alien bomb.
 * @param shields Shields in the playing field.
 * @param c with a shield_collision the structure is filled using the index of the
 *          Shield hit, and the coordinates of the its hit part, -1 otherwise.
 * @return True if there was an hit, False otherwise.
 */
bool is_collision(const coords &shot_pos, const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens, alien_collision &c) {
    c.alien_idx = {NO_COLLISION, NO_COLLISION};

    if (shot_pos.y == NOT_ON_FIELD) {
        // c.ship_part_hit = {NO_COLLISION, NO_COLLISION};
        return false;
    }

    // check all aliens in the fleet
    int x_offset = 0, y_offset = 0;
    int x = 0;
    for (auto &aliens_line : aliens) {
        int y = 0;
        for (auto &a : aliens_line) {
            if ((shot_pos.x >= a.position.x and shot_pos.x < (a.position.x + SPRITE_WIDTH)) and  // shot in spaceship width
                (shot_pos.y >= a.position.y and shot_pos.y < (a.position.y + SPRITE_HEIGHT)) and // shot in spaceship height
                a.status == ALIVE) {
                // collision
                c.alien_idx = {x,  y};
                return true;
            }
            y++;
            x_offset += X_OFFSET_BETWEEN_ALIEN;
        }
        x++;
        y_offset += Y_OFFSET_BETWEEN_ALIEN;
        x_offset = 0;  // reset column index
    }

    return false;
}

/**
 * @brief Checks the collision between the hero missile and the Aliens in the
 * fleet.
 *
 * @param aliens Aliens objects in the Fleet.
 * @param m The hero missile.
 */
void check_fleet_collision(AlienFleet &f, Hero &h) {
    alien_collision c {};
    if (is_collision(h.missile.position, f.aliens, c)) {
        // remove the alien spaceship
        Alien &a = f.aliens[c.alien_idx.x][c.alien_idx.y];
        // update alien status
        a.status = EXPLODING;
        // update fleet population
        f.population--;
        // reset hero missile
        h.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
        // update hero score
        h.score += a.points;
    }
}

/**
 * @brief Checks if an Alien is hit and decrease the explosion timer.
 * When the explosion timer is less than 0, then the alien status is set to
 * DEAD.
 *
 * @param aliens Alien Fleet.
 */
void check_alien_explosion(std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens) {
    for (auto &aliens_line : aliens) {
        for (auto &a : aliens_line) {
            if (a.status == EXPLODING and a.explosion.timer > 0) {
                a.explosion.timer--; // decrease explosion show time
                if (a.explosion.timer <= 0) {
                    a.status = DEAD;
                }
            }
        }
    }
}

/**
 * @brief Moves the alien Fleet right or left and refresh/reset the fleet speed.
 *
 * @param aliens Alien Fleet.
 */
void make_fleet_movement(AlienFleet &fleet) {
    int x_offset = 1, y_offset = 1;

    if (fleet.movement_speed == 0.0) {
        for (auto &aliens_line : fleet.aliens) {
            for (auto &a : aliens_line) {
                    if (a.status == ALIVE) {
                        if (a.position.x + x_offset > (W_WIDTH - SPRITE_WIDTH) or (a.position.x + x_offset < 0)) { // check alien for boundaries
                            // change attack direction
                            fleet.attack_direction == RIGHT_DIRECTION ? fleet.attack_direction = LEFT_DIRECTION : fleet.attack_direction = RIGHT_DIRECTION;
                        }

                        if (fleet.attack_direction == RIGHT_DIRECTION) {
                            x_offset = 1;
                        } else {
                            x_offset = -1;
                        }

                        a.position.x += x_offset;
                    }
                }
            }
        // change frame
        fleet.animation_frame == FRAME_1 ? fleet.animation_frame = FRAME_2 : fleet.animation_frame = FRAME_1;
    }
    fleet.movement_speed--;

    if (fleet.movement_speed < 0.0) {
        reset_fleet_speed(fleet);
    }

}

/**
 * @brief Every time the alien fleet speed is reset, the velocity of aliens will
 * increase, in according the field line and the number of Aliens left.
 *
 * @param fleet The alien Fleet.
 */
void reset_fleet_speed(AlienFleet &fleet) {
    // fleet.movement_speed = float(fleet.game_line * 2.0 + (float(fleet.population) / float(ALIEN_PER_ROW * ALIEN_ROWS)));
    fleet.movement_speed = 15;
}
