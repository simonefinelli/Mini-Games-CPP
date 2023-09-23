/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "core.h"
#include "gui.h"

/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    // define field size (window size)
    GameData gd {};
    gd.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gd.field_game.state = PLAY_SCREEN; // TODO after change with WELCOME_SCREEN
    gd.field_game.level = 1;  // first level

    // define Hero
    define_hero(gd.hero);

    return gd;
}

/**
 * @brief Updates game data structure while the game is going on.
 *
 * @param gm Game data.
 */
void update_game_data(GameData gm) {

}

/**
 * @brief Gets the user input to move the Hero left or right.
 * The user is allowed to go only in the left or right position during the game,
 * so the input is a arrow keys. In ncurses arrow keys are treated with integer
 * type.
 * @return the
 */
int get_user_input() {
    return gui::get_char();
}

/**
 * @brief Uses the graphical library (ncurses - gui.h) to draw the game on
 * terminal screen.
 */
void draw_screen_game(const GameData &gd) {
    const Hero &h = gd.hero;
    // clear the terminal screen
    gui::clear_screen();

    gui::draw_sprite(h.position.x, h.position.y, h.sprite);
    // refresh the terminal screen
    gui::refresh_screen();
}
