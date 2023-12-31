/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include <thread>
#include "core.h"

void draw_hero_on_field(const Hero &h);
void move_hero(Hero &h, int peace);
void hero_init_shoot(Hero &h);
void draw_alien_fleet(AlienFleet &f);
void check_game_status(GameData &gd);
void update_hero_explosion_status(GameData &gd);
void pause_game(GameData &gd);

/**
 * @brief Creates the two Players.
 *
 * @return the game data of the two Players.
 */
GameData initialize_game() {
    GameData gd{};

    // define game field characteristics TODO make a function in appropriate object
    gd.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gd.field_game.state = PLAY_SCREEN; // TODO after change with WELCOME_SCREEN
    gd.field_game.level = 1;  // first level

    // define fleet
    init_fleet(gd.alien_fleet);

    // init shields
    init_shields(gd.field_game.shields);

    // define Hero
    init_hero(gd.hero);

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
    if (gd.hero.status == ALIVE) {
        // TODO make a function
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
                // set initial position of the missile
                hero_init_shoot(gd.hero);
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

        // shot bomb from aliens
        make_fleet_shoot(gd.alien_fleet);

        // update bombs position
        refresh_bombs_position(gd.alien_fleet);

        // check shield collision with bombs' Fleet
        check_shield_collision(gd.field_game.shields, gd.alien_fleet);

        // check collision between bombs' Fleet and Hero
        check_hero_collision(gd.alien_fleet, gd.hero);

    } else {
        // update exploding frame of the Hero
        update_hero_explosion_status(gd);
    }

    // check game status
    check_game_status(gd);

    // check if we have to pause the game
    pause_game(gd);
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
    draw_hero_on_field(gd.hero); // todo check if possible to move to spaceship

    // draw alien fleet
    draw_alien_fleet(gd.alien_fleet); // todo check if possible to move to spaceship

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

    if (h.status == ALIVE) {
        gui::draw_sprite(h.position.x, h.position.y, h.sprite);
    }
    if (h.status == EXPLODING) {
        gui::draw_sprite(h.position.x, h.position.y, h.explosion.curr_frame);
    }

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
    // draw fleet
    for (const auto &aliens_line : f.aliens) {
        for (const auto &alien : aliens_line) {
            // fleet spaceships
            if (alien.status == EXPLODING)
                gui::draw_sprite(alien.position.x, alien.position.y, alien.explosion.frame0);  // explosion animation

            if (alien.status == ALIVE)
                gui::draw_sprite(alien.position.x, alien.position.y, alien.sprite[f.animation_frame]);
        }
    }

    // draw aliens' bombs
    for (const auto &aliens_line : f.aliens) {
        for (const auto &alien : aliens_line) {
            for (const auto &bomb : alien.bombs) {
                if (bomb.position.x != NOT_ON_FIELD) {
                    gui::draw_sprite(bomb.position.x, bomb.position.y, bomb.sprite[bomb.animation_frame]);
                }
            }
        }
    }
}

/**
 * todo
 * @param gd
 */
void update_hero_explosion_status(GameData &gd) {
    if (is_hero_exploding(gd.hero)) {
        // pause animation setting the entire field pause
        gd.field_game.wait_time = 300;  // milliseconds
    }
}

/**
 * @brief This function handles all the conditions to restart and reset the game,
 * make a new level etc.
 *
 * @param gd The Game Data.
 */
void check_game_status(GameData &gd) {
    // after level cleaning
    if (gd.field_game.state == INTERVAL_LEVEL_SCREEN and gd.field_game.wait_time == 0) {
        // reset game todo make a function
        gd.field_game.state = PLAY_SCREEN;
        gd.field_game.level++;
        gd.alien_fleet.population = ALIEN_FLEET_N;
        // re-define fleet
        init_fleet(gd.alien_fleet);
        // re-init shields
        init_shields(gd.field_game.shields);
        // re-define Hero
        init_hero(gd.hero);
        // clear all bomb on screen todo make a function in spaceship.cpp
        for (auto &aliens_line : gd.alien_fleet.aliens) {
            for (auto &a : aliens_line) {
                for (auto &bomb : a.bombs) {
                    bomb.position = {NOT_ON_FIELD, NOT_ON_FIELD};
                }
            }
        }

    }

    // all aliens eliminated
    if (gd.alien_fleet.population == 0 and no_alien_explosion(gd.alien_fleet.aliens)) {  //todo no aliens are exploding (all dead)
        gd.field_game.state = INTERVAL_LEVEL_SCREEN;
        gd.field_game.wait_time = 5000;
    }
}

void reset_game() {

}

/**
 * todo
 *
 * interval in milliseconds
 */
void pause_game(GameData &gd) {
    if (gd.field_game.wait_time == 0) return;

    std::this_thread::sleep_for(std::chrono::milliseconds(gd.field_game.wait_time));
    // reset waiting time
    gd.field_game.wait_time = 0;
}
