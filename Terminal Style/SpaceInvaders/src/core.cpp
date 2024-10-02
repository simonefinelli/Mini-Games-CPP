/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */

#include <thread>
#include "core.h"

// prototypes
void draw_hero_on_field(const Hero& h);
void move_hero(Hero& h, int peace);
void hero_init_shoot(Hero& h);
void draw_alien_fleet(AlienFleet& f);
void check_game_status(GameData& gd);
void update_hero_explosion_status(GameData& gd);
void pause_game(GameData& gd);

/**
 * @brief Initializes the game state for a new session of Space Invaders.
 * 
 * This function sets up the initial game data, including the game field, 
 * alien fleet, shields, and player (hero) for the first level of the game. 
 * It prepares all necessary components before the game loop starts.
 * 
 * Workflow:
 * - Initializes the game field dimensions (`window_size`) and starting state.
 *   - Currently sets the state to `PLAY_SCREEN` (TODO: change to `WELCOME_SCREEN`).
 * - Sets the starting level to 1.
 * - Initializes the alien fleet by calling `init_fleet()`.
 * - Sets up the game shields by calling `init_shields()`.
 * - Initializes the player's hero character by calling `init_hero()`.
 * 
 * @return GameData Returns a fully initialized `GameData` object containing 
 *                  the starting state of the game.
 */

GameData initialize_game() {
    GameData gd{};

    // define game field characteristics
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
 * @brief Renders the current state of the game on the terminal screen using the
 *        ncurses-based graphical library (gui.h).
 * 
 * This function clears the terminal and draws the game's shields, hero, and 
 * alien fleets based on the current game state stored in the `GameData` object.
 * After drawing all elements, it refreshes the screen to display the updated 
 * game state.
 * 
 * Workflow:
 * - Clears the terminal screen using `gui::clear_screen()`.
 * - Draws the defensive shields using `draw_shields_on_field()`.
 * - Draws the hero's spaceship using`draw_hero_on_field()` 
 * - Draws the alien fleet using `draw_alien_fleet()` 
 * - Refreshes the terminal screen with `gui::refresh_screen()` to update the
 *    terminal.
 * 
 * @param gd A reference to `GameData` that contains the current game state to 
 *           be drawn.
 */
void draw_screen_game(GameData& gd) {
    gui::clear_screen(); // clear the terminal screen

    // draw elements on terminal screen
    draw_shields_on_field(gd.field_game.shields);
    draw_hero_on_field(gd.hero);
    draw_alien_fleet(gd.alien_fleet);

    gui::refresh_screen();  // refresh the terminalbut when  screen
}

/**
 * @brief Captures and returns user input to control the Hero's movement or actions.
 * 
 * This function listens for the user's key presses to move the Hero left, right, 
 * or fire a missile. The valid inputs are the left and right arrow keys, spacebar 
 * (for firing), and quit keys (both uppercase and lowercase). The arrow keys are 
 * handled as integers by the ncurses library.
 * 
 * Valid inputs:
 * - `LEFT`  (Move hero left)
 * - `RIGHT` (Move hero right)
 * - `SPACE` (Fire missile)
 * - `QUIT_CHAR_UPPER` or `QUIT_CHAR_LOWER` (Quit game)
 * 
 * @return The integer value corresponding to a valid key press. Returns -1 if 
 *         the input is invalid.
 */
int get_user_input() {
    int input = gui::get_char();

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
        // update hero position in the game
        refresh_hero_on_playfield(gd.hero, user_choice);

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
 * @brief Renders the Hero and their missile on the playing field.
 * 
 * This function displays the hero's spaceship on the field, depending on the 
 * hero's current status (alive or exploding). If the hero is alive, it draws 
 * the spaceship sprite. If the hero is exploding, it displays the current frame 
 * of the explosion animation. Additionally, the function renders the hero's missile 
 * if it is currently on the field.
 * 
 * @param h A constant reference to the `Hero` object containing the hero's 
 *          position, status, sprites, and missile data.
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
 * @brief Renders the alien fleet and their bombs on the playing field.
 * 
 * This function iterates through the alien fleet and draws each alien based on 
 * its current status. Aliens that are alive have their current animation frame 
 * rendered, while exploding aliens display the current explosion frame. Additionally, 
 * the function renders any bombs that the aliens have dropped, displaying their 
 * current animation frame if they are on the field.
 * 
 * Workflow:
 * - Draws each alien in the fleet:
 *   - If the alien's status is `ALIVE`, it renders the alien's spaceship using the 
 *      current animation frame from `alien.sprite[]`.
 *   - If the alien's status is `EXPLODING`, it draws the explosion animation frame.
 * - Iterates through each alien's bombs:
 *   - If a bomb's position is valid (not `NOT_ON_FIELD`), it draws the bomb with 
 *      its current animation frame.
 * 
 * @param f A reference to the `AlienFleet` object containing all the aliens and
 *          their bombs.
 */
void draw_alien_fleet(AlienFleet &f) {
    // draw fleet
    for (const auto &aliens_line : f.aliens) {
        for (const auto &alien : aliens_line) {
            if (alien.status == EXPLODING)
                gui::draw_sprite(alien.position.x, alien.position.y, alien.explosion.frame0);  // explosion animation
            if (alien.status == ALIVE)
                gui::draw_sprite(alien.position.x, alien.position.y, alien.sprite[f.animation_frame]);
        }
    }

    // draw alien bombs
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
