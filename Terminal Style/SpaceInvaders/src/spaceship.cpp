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

// prototypes - internal access
void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position);
bool is_collision(const coords &shot_pos, const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens, alien_collision &c);
void reset_fleet_speed(AlienFleet &fleet);
bool is_alien_overflow(const AlienFleet &fleet);
bool should_shoot(int aliens_left);
bool is_hero_collision(const coords &pos, Hero &h);
void move_hero(Hero& h, int peace);
void hero_init_shoot(Hero& h);

/**
 * @brief Initializes the player's hero character for the Space Invaders game.
 * 
 * This function sets up the initial properties of the hero, including 
 * the hero's name, status, lives, score, and starting position. It also 
 * initializes the hero's missile to be off the field at the start of the game.
 * 
 * Workflow:
 * - Sets the hero's name to `HERO_NAME`.
 * - Initializes the hero's status to `ALIVE`.
 * - Assigns the hero the starting number of lives (`HERO_LIVES`).
 * - Resets the hero's score to 0.
 * - Sets the hero's starting position on the game field using 
 *   `INITIAL_HERO_X_POSITION` and `INITIAL_HERO_Y_POSITION`.
 * - Places the hero's missile off the field by initializing its position to 
 *   `{NOT_ON_FIELD, NOT_ON_FIELD}`.
 * 
 * @param h Reference to the `Hero` object to be initialized.
 */
void init_hero(Hero &h) {
    h.name = HERO_NAME;
    h.status = ALIVE;
    h.lives = HERO_LIVES;
    h.score = 0;
    h.position = {INITIAL_HERO_X_POSITION, INITIAL_HERO_Y_POSITION};
    h.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
}

/**
 * @brief Updates the Hero's position and actions based on user input.
 * 
 * This function processes the user's input to move the Hero or fire a missile. 
 * It moves the Hero left or right on the playfield, or launches a missile if 
 * the spacebar is pressed. Any other input is ignored.
 * 
 * @param h A reference to the `Hero` object whose position and actions will be updated.
 * @param user_choice The key input from the user, indicating which action to take (move left, 
 *                    right, or fire a missile).
 */
void refresh_hero_on_playfield(Hero& h, key user_choice) {
    switch (user_choice) {
        case LEFT:
            move_hero(h, -HER0_MOVEMENT_OFFSET); // to left
            break;
        case RIGHT:
            move_hero(h, HER0_MOVEMENT_OFFSET);  // to right
            break;
        case SPACE:
            // set initial position of the missile
            hero_init_shoot(h);
            break;
        default:
            break; // ignore input
    }
}

/**
 * @brief Checks if the new hero spaceship position is in the game boundaries,
 * than update the hero position.
 *
 * @param h The Hero object.
 * @param peace The offset to apply to the current hero position.
 */
void move_hero(Hero& h, int peace) {
    if ((h.position.x + peace < 0) or ((h.position.x + peace + HERO_SPRITE_WIDTH) > W_WIDTH))
        return;
    h.position.x = h.position.x + peace;
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
void hero_init_shoot(Hero& h) {
    if (h.missile.position.x == NOT_ON_FIELD or h.missile.position.y == NOT_ON_FIELD) {
        h.missile.position.y = h.position.y;  // same position of hero spaceship head
        h.missile.position.x = h.position.x + (HERO_SPRITE_WIDTH / 2);  // center of the hero
    }
}


/**
 * @brief Updates the position of the Hero's missile during each frame.
 * 
 * This function moves the missile upwards at a constant speed (`MISSILE_PACE`) 
 * on the playfield. If the missile reaches the top of the screen (out of bounds), 
 * it is removed from the field. The missile will continue to move upwards until 
 * it either hits an alien or goes beyond the playing boundaries.
 * 
 * Workflow:
 * - If the missile is currently on the field, its y-position is decremented by `MISSILE_PACE`.
 * - If the missile moves beyond the top boundary (y < 0), its position is reset 
 *   to `{NOT_ON_FIELD, NOT_ON_FIELD}` to indicate that it is no longer active.
 * 
 * @param h A reference to the `Hero` object, whose missile's position is being updated.
 */
void refresh_missile_position(Hero& h) {
    if (h.missile.position.x != NOT_ON_FIELD) {
        h.missile.position.y -= MISSILE_PACE;

        // check if the missile exits from boundaries
        if (h.missile.position.y < FIELD_TOP_BOUNDARY_OFFSET) {
            h.missile.position.x = NOT_ON_FIELD;
            h.missile.position.y = NOT_ON_FIELD;
        }
    }
}

/**
 * @brief Initializes the alien fleet for the Space Invaders game.
 * 
 * This function sets up the starting properties of the alien fleet, 
 * including its position, speed, direction, population, and animation frame.
 * It then iterates over the fleet's rows of aliens, assigning each alien its 
 * class and position based on its row and column within the fleet.
 * 
 * Workflow:
 * - Sets the fleet's starting position to `INITIAL_FLEET_X_POSITION` and 
 *    `INITIAL_FLEET_Y_POSITION`.
 * - Resets the number of bombs in play (`bombs_in_play`) to 0.
 * - Initializes the movement speed to `INITIAL_FLEET_SPEED` and sets the attack
 *    direction to `RIGHT_DIRECTION`.
 * - Defines the fleet population size as `ALIEN_FLEET_N` and sets the initial
 *    animation frame.
 * - Iterates through the rows of the fleet, initializing each alien:
 *   - Aliens in row 5 are initialized as `FIRST_CLASS` aliens.
 *   - Aliens in rows 3 and 4 are initialized as `SECOND_CLASS` aliens.
 *   - Aliens in rows 1 and 2 are initialized as `THIRD_CLASS` aliens.
 * - Positions each alien in the fleet based on its row and column using
 *    `init_alien()`, with offsets calculated by `X_OFFSET_BETWEEN_ALIEN` and 
 *    `Y_OFFSET_BETWEEN_ALIEN`.
 * 
 * @param f Reference to the `AlienFleet` object to be initialized.
 */
void init_fleet(AlienFleet& f) {
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
 * @brief Initializes an alien with specific attributes based on its type and position.
 * 
 * This function sets up an `Alien` object by configuring its status, type, position,
 * sprite, and point value according to the specified `alien_type`. The alien's 
 * position is determined relative to the fleet's position with provided offsets.
 * 
 * @param a Reference to the `Alien` object that will be initialized.
 * @param type The `alien_type` of the alien (e.g., `FIRST_CLASS`, `SECOND_CLASS`, or `THIRD_CLASS`).
 * @param x_offset The horizontal offset from the fleet's position for the alien's placement.
 * @param y_offset The vertical offset from the fleet's position for the alien's placement.
 * @param fleet_position A `coords` object representing the base position of the alien fleet.
 */
void init_alien(Alien &a, alien_type type, int x_offset, int y_offset, const coords &fleet_position) {
    switch (type) {
        case FIRST_CLASS:
            a.status = ALIVE;
            a.type = FIRST_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {FIRST_CLASS_ALIEN_SPRITE[0],
                        FIRST_CLASS_ALIEN_SPRITE[1],
                        FIRST_CLASS_ALIEN_SPRITE[2],
                        FIRST_CLASS_ALIEN_SPRITE[3]};
            a.points = FIRST_CLASS_PTS;
            break;
        case SECOND_CLASS:
            a.status = ALIVE;
            a.type = SECOND_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {SECOND_CLASS_ALIEN_SPRITE[0],
                        SECOND_CLASS_ALIEN_SPRITE[1],
                        SECOND_CLASS_ALIEN_SPRITE[2],
                        SECOND_CLASS_ALIEN_SPRITE[3]};
            a.points = SECOND_CLASS_PTS;
            break;
        case THIRD_CLASS:
            a.status = ALIVE;
            a.type = THIRD_CLASS;
            a.position = {fleet_position.x + x_offset, fleet_position.y + y_offset};
            a.sprite = {THIRD_CLASS_ALIEN_SPRITE[0],
                        THIRD_CLASS_ALIEN_SPRITE[1],
                        THIRD_CLASS_ALIEN_SPRITE[2],
                        THIRD_CLASS_ALIEN_SPRITE[3]};
            a.points = THIRD_CLASS_PTS;
            break;
        default: ;
    }
    a.status = ALIVE;
    a.explosion.timer = FPS * ALIEN_EXPLOSION_DURATION;
}

/**
 * @brief Initializes a UFO object with default values for its properties.
 *
 * This function sets the status of the UFO to DEAD, assigns it a type,
 * initializes its position based on the given offsets, and configures 
 * other properties such as sprite, points, spawn delay, movement speed, 
 * and explosion timer.
 *
 * @param u Reference to the UFO object to be initialized.
 * @param x_offset The x-coordinate offset for the UFO's position.
 * @param y_offset The y-coordinate offset for the UFO's position.
 */
void init_alien(UFO &u, int x_offset, int y_offset) {
    u.status = DEAD;
    u.type = SPECIAL_CLASS;
    u.position = {x_offset, y_offset};
    u.sprite = {UFO_SPRITE[0], UFO_SPRITE[1]};
    u.points = UFO_CLASS_PTS;
    u.spawn_delay = UFO_SPAWN_DELAY;
    u.movement_speed = UFO_SPEED_DELAY;
    u.explosion.timer = FPS * UFO_EXPLOSION_DURATION;
}

/**
 * @brief Checks for a collision between a shot (missile or bomb) and any alien 
 *        in the fleet.
 * 
 * This function determines if a shot, represented by its position (`shot_pos`),
 * hits any alien in the fleet. It iterates over all the aliens and checks if 
 * the shot's coordinates fall within the boundaries of an alien's sprite. If a 
 * collision is detected, it updates the `alien_collision` object with the 
 * alien's index and returns `true`. If no collision occurs, it returns `false`.
 * 
 * @param shot_pos The coordinates (`coords`) of the shot (missile or bomb) being 
 *                 checked for collisions.
 * @param aliens A constant reference to a 2D array of `Alien` objects representing
 *               the alien fleet.
 * @param c A reference to an `alien_collision` object, which will be updated 
 *          with the alien's index if a collision occurs.
 * 
 * @return bool Returns `true` if a collision is detected, otherwise returns `false`.
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
 * @brief Detects and handles collisions between the Hero's missile and the 
 *        alien fleet.
 * 
 * This function checks if the Hero's missile collides with any alien in the fleet. 
 * If a collision is detected, it updates the alien's status to `EXPLODING`, reduces 
 * the fleet population, resets the Hero's missile, and increases the Hero's score 
 * based on the points value of the destroyed alien.
 * 
 * @param fleet A reference to the `AlienFleet` object, representing the current 
 *        alien fleet on the field.
 * @param h A reference to the `Hero` object, used to check the missile position 
 *        and update the score.
 */
void check_fleet_collision(AlienFleet& fleet, Hero& h) {
    alien_collision c {};
    if (is_collision(h.missile.position, fleet.aliens, c)) {
        // get the alien spaceship
        Alien& a = fleet.aliens[c.alien_idx.x][c.alien_idx.y];
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
 * @brief Checks for collisions between a UFO and a Hero's missile.
 *
 * This function determines if the Hero's missile has collided with the UFO. 
 * If a collision is detected, the UFO's status is changed to EXPLODING, 
 * and the missile's position is reset. The Hero's score is updated based 
 * on the points associated with the UFO. Additionally, it checks if the 
 * UFO has moved out of the game boundaries, in which case it is marked as DEAD 
 * and reset to its initial position.
 *
 * @param ufo Reference to the UFO object to check for collisions.
 * @param h Reference to the Hero object whose missile is checked against the UFO.
 */
void check_ufo_collision(UFO& ufo, Hero& h) {
    // collision with hero's missile
    if ((h.missile.position.x >= ufo.position.x and h.missile.position.x < (ufo.position.x + UFO_SPRITE_WIDTH)) and 
        (h.missile.position.y >= ufo.position.y and h.missile.position.y < (ufo.position.y + UFO_SPRITE_HEIGHT)) and
         ufo.status == ALIVE) {
        // remove the alien spaceship
        ufo.status = EXPLODING;
        ufo.explosion.timer = FPS * UFO_EXPLOSION_DURATION;
        // reset hero missile
        h.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
        // update hero score
        h.score += ufo.points;
    }

    // ufo out of boundaries
    if (ufo.status == ALIVE and ufo.position.x + LATERAL_MOVEMENT_STEP > (W_WIDTH - UFO_SPRITE_WIDTH)) {
        ufo.status = DEAD;
        ufo.spawn_delay = UFO_SPAWN_DELAY;
        ufo.position = {INITIAL_UFO_X_POSITION, INITIAL_UFO_Y_POSITION};
    }
}


/**
 * @brief Manages the explosion animation and status updates for aliens in the 
 *        fleet.
 * 
 * This function iterates through the alien fleet and checks if any aliens are 
 * in the `EXPLODING` state. If an alien is exploding, the explosion timer is 
 * decremented to manage the duration of the explosion animation. Once the timer
 * reaches zero, the alien's status is updated to `DEAD`, marking the end of the 
 * explosion.
 * 
 * @param aliens A reference to a 2D array of `Alien` objects representing the 
 *               alien fleet. The function will check and update the status of 
 *               each alien.
 */
void check_alien_explosion(std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS>& aliens) {
    for (auto& aliens_line : aliens) {
        for (auto& a : aliens_line) {
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
 * @brief Updates the explosion state of a UFO.
 *
 * This function checks if the UFO is in the EXPLODING state and has a 
 * remaining explosion timer. If so, it decrements the timer. Once the 
 * timer reaches zero, the UFO's status is changed to DEAD, and its 
 * position is reset to the initial values. The spawn delay is also 
 * reset to allow the UFO to be spawned again.
 *
 * @param ufo Reference to the UFO object to update its explosion state.
 */
void check_ufo_explosion(UFO& ufo) {
     if (ufo.status == EXPLODING and ufo.explosion.timer > 0) {
        ufo.explosion.timer--;
        if (ufo.explosion.timer <= 0) {
            ufo.status = DEAD;
            ufo.spawn_delay = UFO_SPAWN_DELAY;
            ufo.position = {INITIAL_UFO_X_POSITION, INITIAL_UFO_Y_POSITION};
        }
    }
}

/**
 * @brief Controls the alien fleet's movement, alternating between vertical and 
 *        horizontal steps.
 * 
 * This function manages the movement of the alien fleet based on its current 
 * speed and position. It alternates between vertical steps (moving down) and 
 * horizontal steps (swiping left or right) whenever the fleet reaches the 
 * boundary of the game field. The function also updates the fleet's advancing 
 * status, direction, and animation frame to create the fleet's movement pattern.
 * 
 * @param fleet A reference to the `AlienFleet` object, which contains the current 
 *              state and position of the fleet.
 */
void make_fleet_movement(AlienFleet& fleet) {
    static bool make_a_step_forward = true;

    // update fleet position at the end of each movement time
    if (fleet.movement_speed == 0 and no_alien_explosion(fleet.aliens)) {
        if (is_alien_overflow(fleet) and make_a_step_forward) {
            fleet.game_line++;
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
            //
            make_a_step_forward = false;
        } else {
            make_a_step_forward = true;
            // chose offset with regard the current fleet direction
            // update horizontal fleet position
            for (auto &aliens_line : fleet.aliens) {
                for (auto &a : aliens_line) {
                    a.position.x += fleet.attack_direction ? LATERAL_MOVEMENT_STEP : -LATERAL_MOVEMENT_STEP;
                }
            }
            // update advancing flag
            fleet.advancing = false;
            // change animation frame
            fleet.animation_frame == FRAME_1 ? fleet.animation_frame = FRAME_2 : fleet.animation_frame = FRAME_1;
        }
    }

    // update and/or reset movement time
    fleet.movement_speed -= FLEET_ADVANCE_STEP;  // how fast the feet will move
    if (fleet.movement_speed < 0) reset_fleet_speed(fleet);
}

/**
 * @brief Checks and updates the spawn status of a UFO.
 *
 * This function determines if a UFO can be spawned based on its current 
 * status and spawn delay. If the spawn delay has expired and the UFO 
 * is DEAD (but not EXPLODING), its status is changed to ALIVE, allowing 
 * it to re-enter the game. If the UFO cannot be spawned, the spawn 
 * delay is decremented.
 *
 * @param ufo Reference to the UFO object to check its spawn status.
 */
void check_ufo_spawn(UFO& ufo) {
    // UFO status
    if (ufo.spawn_delay <= 0 and ufo.status == DEAD and ufo.status != EXPLODING) {
        ufo.status = ALIVE;
    } else {
        ufo.spawn_delay--;
    }
}

/**
 * @brief Updates the movement of a UFO on the game field.
 *
 * This function controls the horizontal movement of the UFO. If the UFO is 
 * currently alive and its movement speed is set to zero, it will move one 
 * unit to the right. The movement speed is then decreased by a predefined 
 * step. If the movement speed falls below zero, it is reset to the 
 * default speed, allowing for controlled movement pacing.
 *
 * @param ufo Reference to the UFO object to update its movement.
 */
void make_ufo_movement(UFO& ufo) {
    if (ufo.movement_speed == 0 and ufo.status == ALIVE) {  // the UFO is spowned on field
        ufo.position.x++;
    }
    // update and/or reset movement time
    ufo.movement_speed -= UFO_ADVANCE_STEP;  // how fast the feet will move
    if (ufo.movement_speed < 0) ufo.movement_speed = UFO_SPEED_DELAY;
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
    // if (fleet.population >= 2) {
    //     int new_speed = INITIAL_FLEET_SPEED - (ALIEN_FLEET_N - fleet.population);
    //     fleet.movement_speed = new_speed > 5 ? INITIAL_FLEET_SPEED : 5;  // todo make consts
    // } else {
    //     fleet.movement_speed = 1;
    // }

    if (fleet.population == ALIEN_FLEET_N) {
        fleet.movement_speed = INITIAL_FLEET_SPEED;
    } else if (fleet.population >= 45) {
        fleet.movement_speed = FLEET_45_SPEED;
    } else if (fleet.population >= 35) {
        fleet.movement_speed = FLEET_35_SPEED;
    } else if (fleet.population >= 25) {
        fleet.movement_speed = FLEET_25_SPEED;
    } else if (fleet.population >= 15) {
        fleet.movement_speed = FLEET_15_SPEED;
    } else if (fleet.population >= 5) {
        fleet.movement_speed = FLEET_05_SPEED;
    } else if (fleet.population >= 2) {
        fleet.movement_speed = FLEET_02_SPEED;
    } else if (fleet.population == 1) {
        fleet.movement_speed = FLEET_01_SPEED;
    }
}

/**
 * @brief Checks if there are any ongoing alien explosions in the fleet.
 * 
 * This function iterates over the alien fleet and determines whether any aliens 
 * are in the `EXPLODING` state. If at least one alien is currently exploding, 
 * the function returns `false`. If no aliens are in the explosion state, it 
 * returns `true`.
 * 
 * @param aliens A constant reference to a 2D array of `Alien` objects 
 *               representing the alien fleet.
 * 
 * @return bool Returns `true` if no aliens are exploding, otherwise returns 
 *         `false`.
 */
bool no_alien_explosion(const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS>& aliens) {
    for (auto& aliens_line : aliens) {
        for (auto& a : aliens_line) {
            if (a.status == EXPLODING) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Manages the alien fleet's shooting behavior by launching bombs from 
 *        alive aliens.
 * 
 * This function handles the alien fleet's shooting cycle, introducing a pause 
 * between attack cycles to simulate random firing intervals. When conditions 
 * allow, bombs are launched from random aliens, with a maximum limit on active 
 * bombs in play.
 * 
 * @param fleet A reference to the `AlienFleet` object, containing the aliens, bombs, 
 *              and other attributes related to fleet behavior.
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
        pause_fleet_attack = generate_number(30, 50);  // todo: reset pause counter todo make consts
    }
    pause_fleet_attack--;
}

/**
 * @brief Makes an Alien shot with a certain probability.
 */
bool should_shoot(int aliens_left) {
    return generate_number(0.0, 1.0) > (0.85 - (aliens_left / 1000.0));
}

/**
 * @brief Updates the positions of active bombs in the alien fleet, animating 
 *        their movement down the screen.
 * 
 * This function moves each bomb in the alien fleet downward by one unit at 
 * regular intervals controlled by a static delay counter. It also toggles the 
 * animation frame for each bomb, creating an animated effect as they fall. If a
 * bomb reaches the bottom of the screen, it is removed from play.
 * 
 * @param fleet A reference to the `AlienFleet` object, which contains the alien 
 *              bombs and tracks the number of bombs currently in play.
 */
void refresh_bombs_position(AlienFleet &fleet) {
    static int delay_bombs_reposition = 1;

    if (delay_bombs_reposition == 0) {
        for (auto &aliens_line : fleet.aliens) {
            for (auto &a : aliens_line) {
                for (auto &bomb : a.bombs) {
                    if (bomb.position.x != NOT_ON_FIELD and delay_bombs_reposition == 0) {

                        bomb.position.y += 1;  // todo: change this into a define
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
 * @brief Detects and handles collisions between the Hero and both alien bombs 
 *        and alien ships.
 * 
 * This function checks for two types of collisions that can affect the Hero:
 * 1. Collisions between the Hero and bombs dropped by the aliens.
 * 2. Direct collisions between the Hero and alien ships.
 * 
 * If a collision is detected in either case, the Hero's status is updated to 
 * `EXPLODING`, their lives are decremented, and the respective bomb or alien is
 * removed or flagged as collided with the Hero.
 * 
 * @param fleet A reference to the `AlienFleet` object, containing the aliens and 
 *              bombs that are checked for collisions with the Hero.
 * @param hero A reference to the `Hero` object, whose status and lives are 
 *             updated in the event of a collision with an alien or a bomb.
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
                        hero.lives = 0;  // game over when an alien hit the hero 
                        return;
                    }
                }
            }
        }
    }
}


/**
 * @brief Checks if a given position collides with the Hero's spaceship.
 * 
 * This function determines whether a specified position (e.g., a bomb or alien) 
 * intersects with the boundaries of the Hero's spaceship. It checks if the 
 * position falls within the horizontal and vertical limits of the Hero's sprite.
 * 
 * @param pos The coordinates (`coords`) of the position to be checked for 
 *            collision with the Hero.
 * @param h A reference to the `Hero` object, whose position and sprite width 
 *          are used for collision detection.
 * 
 * @return bool Returns `true` if the position collides with the Hero's spaceship,
 *         otherwise returns `false`.
 */
bool is_hero_collision(const coords& pos, Hero& h) {
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
 * @param hero A reference to the `Hero` object.
 */
bool is_hero_exploding(Hero &hero) {
    // if (hero.status == EXPLODING and hero.explosion.timer > 0) {
    if (hero.status == EXPLODING) {
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
            hero.explosion.timer = 0;
        }
        return true;
    } else if (hero.explosion.timer == 0) {
        // hero.status = ALIVE;  // todo check this
        return false;
    } else {
        return false;
    }
}

/**
 * @brief Resets the positions of all bombs in the alien fleet, removing them 
 *        from the field.
 * 
 * This function iterates over each alien in the fleet and sets the position of 
 * every bomb to `{NOT_ON_FIELD, NOT_ON_FIELD}`, effectively clearing all active 
 * bombs from the playing field. It ensures that no bombs remain in play after 
 * calling this function.
 * 
 * @param alien_fleet A reference to the `AlienFleet` object, containing all 
 *                    aliens and their bombs.
 */
void reset_all_alien_bombs(AlienFleet& alien_fleet) {
    for (auto& aliens_line : alien_fleet.aliens) {
        for (auto& a : aliens_line) {
            for (auto& bomb : a.bombs) {
                bomb.position = {NOT_ON_FIELD, NOT_ON_FIELD};
            }
        }
    }
}