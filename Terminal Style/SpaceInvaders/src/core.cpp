/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include <chrono>
#include <iostream>
#include "core.h"

void draw_hero_on_field(const Hero &h);
void move_hero(Hero &h, int peace);
void hero_init_shoot(Hero &h);
void draw_alien_fleet(AlienFleet &f);

/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    GameData gd {};

    // define game field characteristics TODO make a function in appropriate object
    gd.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gd.field_game.state = PLAY_SCREEN; // TODO after change with WELCOME_SCREEN
    gd.field_game.level = 1;  // first level

    // init shields
    init_shields(gd.field_game.shields);

    // define Hero
    init_hero(gd.hero);

    // define fleet
    init_fleet(gd.alien_fleet);

    return gd;
}

/**
 * @brief Gets the user input to move the Hero left or right.
 * The user is allowed to go only in the left or right position during the game,
 * so the input is a arrow keys. In ncurses arrow keys are treated with integer
 * type.
 * @return the
 */
int get_user_input() {
    int input = gui::get_char();
    // int input = ' ';

    switch (input) {
        case QUIT_CHAR_UPPER:
        case QUIT_CHAR_LOWER:
        case LEFT:
        case RIGHT:
        case SPACE:
            return input;
        default:
            return -1;
    }
}

/**
 * @brief Updates game data structure while the game is going on.
 *
 * @param gm Game data.
 */
void update_game_data(GameData &gd, key user_choice) {
    switch (user_choice) {
        case LEFT:
            // move hero to left
            move_hero(gd.hero, -HER0_MOVEMENT_OFFSET);
            break;
        case RIGHT:
            // move hero to right
            move_hero(gd.hero, HER0_MOVEMENT_OFFSET);
            break;
        case SPACE:
            hero_init_shoot(gd.hero);  // set initial position of the missile
            break;
        default:
            // ignore input
            break;
    }

    // update hero missile position
    refresh_missile_position(gd.hero);

    // check shield collision with Hero
    check_shield_collision(gd.field_game.shields, gd.hero.missile);

    // check aliens collision in fleet
    check_fleet_collision(gd.alien_fleet, gd.hero);

    // handle alien explosion
    check_alien_explosion(gd.alien_fleet.aliens);

    // move fleet
    make_fleet_movement(gd.alien_fleet);

}

/**
 * @brief Uses the graphical library (ncurses - gui.h) to draw the game on
 * terminal screen.
 */
void draw_screen_game(GameData &gd) {
    // clear the terminal screen
    gui::clear_screen();

    // draw shields
    draw_shields_on_field(gd.field_game.shields);

    // draw hero data
    draw_hero_on_field(gd.hero);

    // draw alien fleet
    draw_alien_fleet(gd.alien_fleet);

    // refresh the terminal screen
    gui::refresh_screen();
}

/**
 * @brief Shows the Hero player components on the playing field. Also the
 * missile is shown using this function.
 *
 * @param h The Hero object.
 */
void draw_hero_on_field(const Hero &h) {
    // hero spaceship
    gui::draw_sprite(h.position.x, h.position.y, h.sprite);
    // hero missile
    if (h.missile.position.x != NOT_ON_FIELD) {
        gui::draw_char(h.missile.position.x, h.missile.position.y, h.missile.frame0);
    }
}

/**
 * @brief Draws the alien fleet according to their position in the playing field.
 *
 * @param fleet The Fleet object.
 */
void draw_alien_fleet(AlienFleet &f) {
    for (auto &aliens_line : f.aliens) {
        for (auto &alien : aliens_line) {
            if (alien.status == EXPLODING) {
                gui::draw_sprite(alien.position.x, alien.position.y, alien.explosion.frame0);  // explosion animation
            }
            if (alien.status == ALIVE)
                gui::draw_sprite(alien.position.x, alien.position.y, alien.sprite[f.animation_frame]);
        }
    }
}
