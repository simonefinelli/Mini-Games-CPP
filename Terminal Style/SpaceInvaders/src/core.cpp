/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "core.h"

void move_hero(Hero &h, int peace);

/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    GameData gd {};
    // define game field characteristics
    gd.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gd.field_game.state = PLAY_SCREEN; // TODO after change with WELCOME_SCREEN
    gd.field_game.level = 1;  // first level

    // define Hero
    define_hero(gd.hero);

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

    switch (input) {
        case QUIT_CHAR_UPPER:
        case QUIT_CHAR_LOWER:
            return input;
        case KEY_LEFT:
            return LEFT;
        case KEY_RIGHT:
            return RIGHT;
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
            break;
    }
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

/**
 * @brief Checks if the new hero spaceship position is in the game boundaries,
 * than update the hero position.
 *
 * @param h The Hero object.
 * @param peace The offset to apply to the current hero position.
 */
void move_hero(Hero &h, int peace) {
    if ((h.position.x + peace < 0) or ((h.position.x + peace + h.sprite[0].size()) > W_WIDTH))
        return;
    h.position.x = h.position.x + peace;
}
