/**
 * @file spaceship.h
 * @brief This file and the relative header collect oll the data and operation
 * of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <array>
#include <thread>
#include "spaceship.h"


void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position);
bool is_collision(const coords &shot_pos, const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens, alien_collision &c);
void reset_fleet_speed(AlienFleet &fleet);
bool is_alien_overflow(const AlienFleet &fleet);
bool no_alien_explosion(const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens);
bool should_shoot(int aliens_left);
bool is_hero_collision(const coords &pos, Hero &h);

/**
 * @brief Populates the Hero structure.
 */
void init_hero(Hero &h) {
    h.name = HERO_NAME;
    h.status = ALIVE;
    h.lives = HERO_LIVES;
    h.score = 0;
    h.position = {INITIAL_HERO_X_POSITION,INITIAL_HERO_Y_POSITION};
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
            a.sprite = {{{"/oo\\", "<  >"}, {"/oo\\", "/^^\\"}}};  // todo make sprite as other elements
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
void check_fleet_collision(AlienFleet &fleet, Hero &h) {
    alien_collision c {};
    if (is_collision(h.missile.position, fleet.aliens, c)) {
        // remove the alien spaceship
        Alien &a = fleet.aliens[c.alien_idx.x][c.alien_idx.y];
        // update alien status
        a.status = EXPLODING;
        // update fleet population
        fleet.population--;
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
            // update advancing flag
            fleet.advancing = true;
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
            // update advancing flag
            fleet.advancing = false;
            // change animation frame
            fleet.animation_frame == FRAME_1 ? fleet.animation_frame = FRAME_2 : fleet.animation_frame = FRAME_1;
        }
    }
    // update and/or reset movement time
    fleet.movement_speed -= FLEET_ADVANCE_STEP;
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
        fleet.movement_speed = new_speed > 5 ? 30 : 5;  // todo make consts
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

/**
 * @brief The functions checks for each Alien in the Fleet if it is allowed to
 * make a shot.
 *
 * There are at most only 3 bombs at the same time in play.
 * Only when
 *
 * @param fleet The alien Fleet.
 */
void make_fleet_shoot(AlienFleet &fleet) {
    // pause fleet attack for a random time at each attack cycle
    static int pause_fleet_attack = generate_number(70, 100);  // initial pause todo make consts

    if (pause_fleet_attack == 0) {
        // shoot only if the Fleet is not advancing and there is not too many bombs in play
        if (!fleet.advancing and fleet.bombs_in_play < MAX_BOMBS_IN_PLAY) {
            for (auto alien_line = fleet.aliens.rbegin(); alien_line != fleet.aliens.rend(); alien_line++) {
                for(auto &alien : *alien_line) {
                    if (alien.status == ALIVE and should_shoot(fleet.population)
                        and alien.ammo != 0 and fleet.bombs_in_play < MAX_BOMBS_IN_PLAY) {
                        // shoot bomb
                        alien.bombs[alien.ammo-1] = {alien.position.x,alien.position.y+2};  // set initial position for the bomb
                        alien.ammo--;
                        fleet.bombs_in_play++;
                    }
                }
            }
        }
        pause_fleet_attack = generate_number(30, 50);  // reset pause counter todo make consts
    }
    pause_fleet_attack--;
}

/**
 * @brief Makes an Alien shot with a certain probability.
 */
bool should_shoot(int aliens_left) {
    return generate_number(0.0, 1.0) > (0.85 - (aliens_left / 1000.0));  // todo make defines or conts
}

/**
 * @brief TODO
 *
 * @param fleet The alien Fleet object.
 */
void refresh_bombs_position(AlienFleet &fleet) {
    static int delay_bombs_reposition = 1;

    if (delay_bombs_reposition == 0) {
        for (auto &aliens_line : fleet.aliens) {
            for (auto &a : aliens_line) {
                for (auto &bomb : a.bombs) {
                    if (bomb.position.x != NOT_ON_FIELD and delay_bombs_reposition == 0) {

                        bomb.position.y += 1;  // todo change this into a define
                        // change animation frame
                        bomb.animation_frame = (bomb.animation_frame == FRAME_1) ? FRAME_2: FRAME_1;

                        // check if the missile exits from boundaries
                        if (bomb.position.y > W_HEIGHT) {
                            bomb.position.x = NOT_ON_FIELD;
                            bomb.position.y = NOT_ON_FIELD;
                            fleet.bombs_in_play--;
                        }
                    }
                }
            }
        }
    }
    delay_bombs_reposition++;
    if (delay_bombs_reposition > 10) delay_bombs_reposition = 0;
}

/**
 * @brief Checks the collision between the hero missile and the Aliens in the
 * fleet.
 *
 * @param fleet The Fleet object.
 * @param hero The Hero object.
 */
void check_hero_collision(AlienFleet &fleet, Hero &hero) {
    // check the Aliens' bombs and the Hero spaceship
    for (auto &aliens_line : fleet.aliens) {
        for (auto &a : aliens_line) {
            // check a collision with the bottom row of the bomb
            for (auto &bomb : a.bombs) {
                if (bomb.position.y != NOT_ON_FIELD and is_hero_collision({bomb.position.x, bomb.position.y + 1}, hero)) {
                    hero.status = EXPLODING;
                    hero.lives--;
                    // remove the bomb from the playing field
                    bomb.position = {NOT_ON_FIELD, NOT_ON_FIELD};
                    fleet.bombs_in_play--;
                }
            }
        }
    }

    // check the collision between Aliens and Hero spaceship
    coords curr_position;
    int x, y;
    for (const auto &aliens_line : fleet.aliens) {
        for (const auto &a : aliens_line) {
            // check all the alien sprite
            for (int i = 0; i < SPRITE_HEIGHT; i++) {
                for (int j = 0; j < HERO_SPRITE_WIDTH; j++) {
                    x = a.position.x + j;
                    y = a.position.y + i;
                    curr_position = {x, y};
                    if (a.status == ALIVE and is_hero_collision(curr_position, hero)) {
                        hero.status = EXPLODING;
                        hero.lives--;
                        return;
                    }
                }
            }
        }
    }
}


/**
 * todo
 */
bool is_hero_collision(const coords &pos, Hero &h) {
    // check if the bomb hits the boundaries of the spaceship
    if ((pos.x >= h.position.x) and (pos.x <= (h.position.x + HERO_SPRITE_WIDTH - 1))
        and ((pos.y >= h.position.y) and (pos.y <= h.position.y + 1))) {
        return true;
    } else {
        return false;
    }
}


/**
 * Updates the explosion animation of the Hero object.
 * Because the sprite is changed at every frame, to slow the animation we use a
 * sleep of 0.3 seconds. This approach is good in this case because the entire
 * game is stopped.
 *
 * @param hero The Hero object.
 */
bool is_hero_exploding(Hero &hero) {
    if (hero.status == EXPLODING and hero.explosion.timer > 0) {
        // update exploding frame of the Hero
        if (hero.explosion.curr_frame_idx == 0) {
            hero.explosion.curr_frame = hero.explosion.frame0;
            hero.explosion.curr_frame_idx = 1;
        } else {
            hero.explosion.curr_frame = hero.explosion.frame1;
            hero.explosion.curr_frame_idx = 0;
        }
        // update timer
        hero.explosion.timer--;
        if (hero.explosion.timer <= 0) {
            hero.status = DEAD;
        }
        return true;
    } else {
        return false;
    }
}