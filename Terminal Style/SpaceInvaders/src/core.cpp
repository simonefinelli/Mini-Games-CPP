/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include <array>
#include "core.h"

void draw_hero_on_field(const Hero &h);
void move_hero(Hero &h, int peace);
void hero_init_shoot(Hero &h);

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
    define_hero(gd.hero);

    // define fleet
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
            // move hero to left
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

}

/**
 * @brief Uses the graphical library (ncurses - gui.h) to draw the game on
 * terminal screen.
 */
void draw_screen_game(const GameData &gd) {
    // clear the terminal screen
    gui::clear_screen();

    // draw shields
    draw_shields_on_field(gd.field_game.shields);

    // draw hero data
    draw_hero_on_field(gd.hero);

    // draw alien fleet

    // refresh the terminal screen
    gui::refresh_screen();
}

/**
 * TODO
 * @param h
 */
void draw_hero_on_field(const Hero &h) {
    // hero spaceship
    gui::draw_sprite(h.position.x, h.position.y, h.sprite);
    // hero missile
    if (h.missile.position.x != NOT_ON_FIELD) {
        // draw missile
        gui::draw_char(h.missile.position.x, h.missile.position.y, h.missile.frame0);
    }
}
