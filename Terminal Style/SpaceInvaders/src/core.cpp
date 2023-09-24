/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include "core.h"

void draw_hero_on_field(const Hero &h);
void move_hero(Hero &h, int peace);
void hero_init_shoot(Hero &h);
void update_missile_position(Hero &h);

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
            ;
    }

    // update hero missile position
    update_missile_position(gd.hero);
}

/**
 * @brief Uses the graphical library (ncurses - gui.h) to draw the game on
 * terminal screen.
 */
void draw_screen_game(const GameData &gd) {
    // clear the terminal screen
    gui::clear_screen();

    // draw hero data
    draw_hero_on_field(gd.hero);

    // draw alien fleet

    // refresh the terminal screen
    gui::refresh_screen();
}

void draw_hero_on_field(const Hero &h) {
    // hero spaceship
    gui::draw_sprite(h.position.x, h.position.y, h.sprite);
    // hero missile
    if (h.missile.position.x != NOT_ON_FIELD) {
        // draw missile
        gui::draw_char(h.missile.position.x, h.missile.position.y, h.missile.frame0);
    }
};


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
 * @brief Set the first position of the Hero missile.
 * Note that a missile can only be launched if there is no other missile
 * previously launched in the game screen.
 * A missile is destroyed when it hits an alien spaceship or when it reaches the
 * end of the playing field.
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
 * @brief Updates the position of the Hero missile at each frame.
 * The missile will be launched towards upwards, until it reaches an alien or
 * the end of the playing field.
 * @param h The Hero object.
 */
void update_missile_position(Hero &h) {
    if (h.missile.position.x != NOT_ON_FIELD) {
        h.missile.position.y -= MISSILE_PACE;

        // check if the missile exits from boundaries
        if (h.missile.position.y < 0) {
            h.missile.position.x = NOT_ON_FIELD;
            h.missile.position.y = NOT_ON_FIELD;
        }
    }
}
