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

bool is_collision(const coords &pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c);
void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position);
bool is_collision(const coords &shot_pos, const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens, alien_collision &c);
void reset_fleet_speed(AlienFleet &fleet);
bool is_alien_overflow(const AlienFleet &fleet);
bool no_alien_explosion(const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens);

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
 * @brief Checks if there is a collision between a missile, a bomb or an Alien
 * and one of the shields.
 *
 * @param pos Position of the Hero missile, the Alien bomb or Alien spaceship.
 * @param shields Shields in the playing field.
 * @param c with a shield_collision the structure is filled using the index of the
 *          Shield hit, and the coordinates of the its hit part, -1 otherwise.
 * @return True if there was an hit, False otherwise.
 */
bool is_collision(const coords &pos, const std::array<FieldShield, SHIELD_NUMBER> &shields, shield_collision &c) {
    c.shield_idx = NO_COLLISION;
    c.shield_part_hit = {NO_COLLISION, NO_COLLISION};

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
 * @brief The function checks if there was a collision Alien with shields.
 * To check fo a collision we only check for the second row of the sprite.
 *
 * @param shields Shields into the playing field.
 * @param fleet The Alien Fleet.
 */
void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, AlienFleet &fleet) {
    shield_collision c {};
    coords curr_position;
    int x, y;

    for (const auto &aliens_line : fleet.aliens) {
        for (const auto &a : aliens_line) {
            // check a collision with the bottom row of the Alien
            for (int i = 0; i < SPRITE_WIDTH; i++) {
                x = a.position.x + i;
                y = a.position.y + 1;
                curr_position = {x, y};
                if (a.status == ALIVE and is_collision(curr_position, shields, c)) {
                    // remove hit part
                    shields[c.shield_idx].sprite[c.shield_part_hit.y][c.shield_part_hit.x] = ' ';
                }
            }
        }
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
    f.movement_speed = INITIAL_FLEET_SPEED;
    f.attack_direction = RIGHT_DIRECTION;
    f.population = ALIEN_FLEET_N;
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
 * The function at each clock game (frame) checks for the movement speed of the
 * fleet.
 *
 * When the movement time is finished (0), then the position is update. If an
 * Alien hit the playing field edge, then the Fleet is shifted vertically by one.
 * In this occasion also the clock counter is updated. The clock counter is used
 * to know how many steps the Fleet must advance forward. Finally the attack
 * direction is updated.
 *
 * If the movement time is not finished, then is decremented and when it turns
 * minor of zero the movement itself is updated.
 *
 * @param aliens Alien Fleet.
 */
void make_fleet_movement(AlienFleet &fleet) {
    int x_offset;
    static int clock_counter = FLEET_ADVANCE_STEP;

    // update fleet position at the end of each movement time
    if (fleet.movement_speed == 0 and no_alien_explosion(fleet.aliens)) {
        if (is_alien_overflow(fleet) and clock_counter >= 1) {
            fleet.game_line++;
            clock_counter--;
            // update vertical fleet position
            for (auto &aliens_line : fleet.aliens) {
                for (auto &a : aliens_line) {
                    a.position.y += VERTICAL_MOVEMENT_STEP;
                }
            }
            // change attack direction
            fleet.attack_direction = fleet.attack_direction ? LEFT_DIRECTION : RIGHT_DIRECTION;

        } else {
            // reset clock counter
            clock_counter = FLEET_ADVANCE_STEP;
            // chose offset with regard the current fleet direction
            x_offset = fleet.attack_direction ? LATERAL_MOVEMENT_STEP : -LATERAL_MOVEMENT_STEP;
            // update horizontal fleet position
            for (auto &aliens_line : fleet.aliens) {
                for (auto &a : aliens_line) {
                    a.position.x += x_offset;
                }
            }
            // change animation frame
            fleet.animation_frame == FRAME_1 ? fleet.animation_frame = FRAME_2 : fleet.animation_frame = FRAME_1;
        }
    }
    // update and/or reset movement time
    fleet.movement_speed -= 1;
    if (fleet.movement_speed < 0) reset_fleet_speed(fleet);
}

/**
 * @brief Check if an Alien in the Fleet went outside the boundaries of the
 * playing field.
 *
 * @return True if an Alien hit the boundaries, False otherwise.
 */
bool is_alien_overflow(const AlienFleet &fleet) {
    for (auto &aliens_line : fleet.aliens) {
        for (auto &a : aliens_line) {
            if (a.status == ALIVE) {
                if ((a.position.x + LATERAL_MOVEMENT_STEP > (W_WIDTH - SPRITE_WIDTH)) or
                   (a.position.x - LATERAL_MOVEMENT_STEP < 0)) { // alien out of boundaries
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Every time the alien fleet speed is reset, the velocity of aliens will
 * increase, in according the field line and the number of Aliens left.
 *
 * Note that in the Original Game the Aliens' speed only increase when an Alien
 * is hit, and not when the fleet advances. So we follow that approach.
 *
 * @param fleet The alien Fleet.
 */
void reset_fleet_speed(AlienFleet &fleet) {
    if (fleet.population >= 2) {
        int new_speed = INITIAL_FLEET_SPEED - (ALIEN_FLEET_N - fleet.population);
        fleet.movement_speed = new_speed > 5 ? 10 : 5;
    } else {
        fleet.movement_speed = 1;
    }
}

/**
 * @brief TODO
 *
 * @param aliens Aliens of the Fleet.
 */
bool no_alien_explosion(const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens) {
    for (auto &aliens_line : aliens) {
        for (auto &a : aliens_line) {
            if (a.status == EXPLODING) {
                return false;
            }
        }
    }
    return true;
}