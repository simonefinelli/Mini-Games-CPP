/**
 * @file core.h
 * @brief This file and the relative header handle the core functions to init
 * and terminate the game correctly.
 * @author SimoX
 * @date 2023-09-18
 */
#include <thread>
#include "core.h"

// prototypes - internal access between the core file
void draw_hero_on_field(const Hero& h);
void move_hero(Hero& h, int peace);
void hero_init_shoot(Hero& h);
void draw_alien_fleet(const AlienFleet& f);
void draw_alien_ufo(const UFO& ufo);
void update_hero_explosion_status(GameData& gd);
void pause_game(GameData& gd);
void draw_level_change_screen(GameData& gd);
void draw_game_over_screen(GameData& gd);
void draw_welcome_screen(GameData& gd);
void draw_player_info(GameData& gd);

/**
 * @brief Initializes the game state for a new session of Space Invaders.
 * 
 * This function sets up the initial game data, including the game field, 
 * alien fleet, shields, and player (hero) for the first level of the game. 
 * It prepares all necessary components before the game loop starts.
 * 
 * @return GameData Returns a fully initialized `GameData` object containing 
 *                  the starting state of the game.
 */

GameData initialize_game() {
    GameData gd{};

    // define game field characteristics
    gd.field_game.window_size = {W_WIDTH, W_HEIGHT};
    gd.field_game.state = WELCOME_SCREEN;
    gd.field_game.level = 1;  // first level
    gd.field_game.wait_time = 0;

    // define fleet
    init_fleet(gd.alien_fleet);
    // define UFO (special alien spaceship)
    init_alien(gd.ufo, INITIAL_UFO_X_POSITION, INITIAL_UFO_Y_POSITION);
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
 * @param gd A reference to `GameData` that contains the current game state to 
 *           be drawn.
 */
void draw_screen_game(GameData& gd) {
    gui::clear_screen(); // clear the terminal screen

    // draw elements
    switch (gd.field_game.state) {
        case WELCOME_SCREEN:
            draw_welcome_screen(gd);
            break;
        case PLAY_SCREEN:
            draw_player_info(gd);
            draw_shields_on_field(gd.field_game.shields);
            draw_hero_on_field(gd.hero);
            draw_alien_fleet(gd.alien_fleet);
            draw_alien_ufo(gd.ufo);
            break;
        case INTERVAL_LEVEL_SCREEN:
            draw_level_change_screen(gd);
            break;
        case GAME_OVER_SCREEN:
            draw_game_over_screen(gd);
            break;
        default: break;
    }

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
 * - `NEW_GAME_CHAR_UPPER` or `NEW_GAME_CHAR_LOWER` (Start game)
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
        case NEW_GAME_CHAR_UPPER:
        case NEW_GAME_CHAR_LOWER:
            return input;
        default:
            return -1;
    }
}

/**
 * @brief Updates the game state based on user input and ongoing events.
 * 
 * This function handles game state transitions and updates all relevant 
 * elements within the game based on the current state and user input. It 
 * manages the hero's actions, interactions with enemies, and environmental 
 * effects like collisions with shields, aliens, and UFOs.
 * 
 * @param gd Reference to the `GameData` object containing the game's current state 
 *           and elements (e.g., hero, alien fleet, UFO, shields).
 * @param user_choice The `key` input from the user which determines the hero's action.
 * 
 * @note This function does not return a value but modifies the `GameData` object in-place.
 */
void update_game_data(GameData &gd, key user_choice) {
    if (gd.field_game.state == WELCOME_SCREEN and IS_NEW_GAME_CHAR(user_choice))  { 
        gd.field_game.state = PLAY_SCREEN; 
    }

    if (gd.hero.status == ALIVE and gd.field_game.state == PLAY_SCREEN) {
        // update hero info
        refresh_hero_on_playfield(gd.hero, user_choice);
        refresh_missile_position(gd.hero);
        check_shield_collision(gd.field_game.shields, gd.hero.missile);
        check_fleet_collision(gd.alien_fleet, gd.hero);
        check_ufo_collision(gd.ufo, gd.hero);
        // update alien info
        check_alien_explosion(gd.alien_fleet.aliens);
        check_ufo_explosion(gd.ufo);
        make_fleet_movement(gd.alien_fleet);
        make_ufo_movement(gd.ufo);
        make_fleet_shoot(gd.alien_fleet);
        refresh_bombs_position(gd.alien_fleet);
        check_shield_collision(gd.field_game.shields, gd.alien_fleet);
        check_hero_collision(gd.alien_fleet, gd.hero);

    } else {
        // update exploding frame of the hero
        update_hero_explosion_status(gd);
    }
}

/**
 * @brief This function handles all the conditions to restart and reset the game,
 *        make a new level etc.
 *
 * @param gd The Game Data.
 */
void check_game_status(GameData& current_gd) {
    /**************************************************************************
     * Check game status conditions                                           *
     **************************************************************************/
    // continue the game after clear a level
    if (current_gd.hero.status == ALIVE and current_gd.field_game.state == INTERVAL_LEVEL_SCREEN) {
        current_gd.field_game.state = PLAY_SCREEN;
    }
    // all aliens eliminated: go to the next level
    if (current_gd.alien_fleet.population == 0 and no_alien_explosion(current_gd.alien_fleet.aliens)) {
        current_gd.field_game.state = INTERVAL_LEVEL_SCREEN;
    }
    // the have lost a live
    if (current_gd.hero.status == DEAD and current_gd.hero.lives != 0) {
        current_gd.field_game.state = PLAYER_DEAD_SCREEN;
    }
    // the hero is dead: restart the game
    if (current_gd.hero.status == DEAD and current_gd.hero.lives == 0) {
        current_gd.field_game.state = GAME_OVER_SCREEN;
    }
    // ufo alien
    check_ufo_spawn(current_gd.ufo);

    /**************************************************************************
     * create a behaviour for each game status condition                      *
     **************************************************************************/
    switch (current_gd.field_game.state) {
        case INTERVAL_LEVEL_SCREEN:  // set the right game data to go to the next level
            // make sure that all the dropped bombs have been erased
            reset_all_alien_bombs(current_gd.alien_fleet);
            // resume game and go to next level
            current_gd.field_game.level++; // set next level
            /// current_gd.field_game.wait_time = 0; // reset waiting time
            // re-define fleet
            init_fleet(current_gd.alien_fleet);
            // re-define Hero
            current_gd.hero.position = {INITIAL_HERO_X_POSITION, INITIAL_HERO_Y_POSITION};
            current_gd.hero.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
            current_gd.field_game.wait_time = INTERVAL_TIME;
            // re-initialize ufo
            init_alien(current_gd.ufo, INITIAL_UFO_X_POSITION, INITIAL_UFO_Y_POSITION);
            break;
        
        case PLAYER_DEAD_SCREEN:  // the hero has lost all the lives.
            // resume game
            current_gd.field_game.state = PLAY_SCREEN;
            //reposition the hero at center
            current_gd.hero.status = ALIVE;
            current_gd.hero.position = {INITIAL_HERO_X_POSITION, INITIAL_HERO_Y_POSITION};
            current_gd.hero.missile.position = {NOT_ON_FIELD, NOT_ON_FIELD};
            current_gd.hero.explosion.timer = FPS * ALIEN_EXPLOSION_DURATION;
            break;
        
        case GAME_OVER_SCREEN: // the hero has lost all the lives. reset the game from the beginning!
            // make sure that all the dropped bombs have been erased
            reset_all_alien_bombs(current_gd.alien_fleet);
            // create a new blank game data object
            current_gd = initialize_game();
            // pause the game
            current_gd.field_game.wait_time = INTERVAL_TIME;
            break;
    
        default: break;
    }
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
 * @param f A reference to the `AlienFleet` object containing all the aliens and
 *          their bombs.
 */
void draw_alien_fleet(const AlienFleet &f) {
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
 * @brief Renders the UFO on the screen based on its current status.
 * 
 * This function draws the UFO at its current position using the appropriate 
 * sprite. If the UFO is in the `EXPLODING` state, it renders an explosion 
 * frame to simulate the explosion animation. Otherwise, it displays the 
 * standard UFO sprite when the UFO is `ALIVE`.
 * 
 * @param ufo A constant reference to the `UFO` object containing the current 
 *            status, position, and sprite information for the UFO.
 * 
 * @note This function uses `gui::draw_sprite()` to render sprites based on 
 *       the UFO's current state and location.
 */
void draw_alien_ufo(const UFO& ufo) {
    if (ufo.status == EXPLODING)
        gui::draw_sprite(ufo.position.x, ufo.position.y, ufo.explosion.frame1);  // explosion animation
    if (ufo.status == ALIVE)
        gui::draw_sprite(ufo.position.x, ufo.position.y, ufo.sprite);
}

/**
 * @brief Updates the game state when the Hero is in the exploding state.
 * 
 * This function checks if the Hero is currently exploding and, if so, 
 * sets a pause time for the game field to allow the explosion animation to play.
 * The wait time effectively pauses the game for a brief period, 
 * providing a visual pause to show the Hero's explosion.
 * 
 * @param gd A reference to the `GameData` object containing the Hero and field 
 *           game data, which is used to set the game's pause duration during 
 *           the explosion.
 */
void update_hero_explosion_status(GameData& gd) {
    if (is_hero_exploding(gd.hero)) {
        // pause animation setting the entire field pause
        gd.field_game.wait_time = INTERVAL_TIME_FOR_HERO;  // milliseconds
    }
}

/**
 * @brief Pauses the game for a specified duration if a wait time is set.
 * 
 * This function temporarily halts the game by pausing execution for the 
 * duration specified in `gd.field_game.wait_time`. After the pause, it resets 
 * `wait_time` to zero. If no wait time is set (`wait_time` equals zero), the 
 * function returns immediately without pausing.
 * 
 * @param gd Reference to the `GameData` object containing the current wait time 
 *           and other game state information.
 * 
 * @note This function uses `std::this_thread::sleep_for()` to pause execution 
 *       based on the wait time specified in milliseconds.
 */
void pause_game(GameData& gd) {
    if (gd.field_game.wait_time == 0) return;

    std::this_thread::sleep_for(std::chrono::milliseconds(gd.field_game.wait_time));
    // reset waiting time
    gd.field_game.wait_time = 0;
}

/**
 * @brief Displays the player's current level, score, and remaining lives on the screen.
 * 
 * This function formats and draws a string that shows the player's game progress,
 * including the current level, score, and a visual representation of remaining lives.
 * The lives are represented by visual symbols ("|-V-|" for alive and "X" for lost).
 * 
 * Display Details:
 * - The number of lives is represented as:
 *   - `"|-V-|  |-V-|"` if the player has full lives.
 *   - `"  X    |-V-|"` if the player has two lives remaining.
 *   - `"  X      X  "` if the player has one life remaining.
 * 
 * @param gd Reference to the `GameData` object containing the player's level, score,
 *           and remaining lives information.
 * 
 * @note The function assumes the screen width (`W_WIDTH`) is sufficient for the 
 *       formatted player info string.
 */
void draw_player_info(GameData& gd) {
    const char* lives;
    if (gd.hero.lives == HERO_LIVES) {
        lives = "|-V-|  |-V-|";
    } else if (gd.hero.lives == 2) {
        lives = "  X    |-V-|";
    } else {
        lives = "  X      X  ";
    }
    char player_info[W_WIDTH];
    std::sprintf(
        player_info,
        "    LEVEL %3d                     SCORE %5d                  %s    ",
        gd.field_game.level,
        gd.hero.score,
        lives
    );

    gui::draw_string(1, 0, player_info);
}

/**
 * @brief Renders the welcome screen with introductory text at specified positions.
 * 
 * This function displays the welcome screen text and a prompt to start a new game, 
 * centered on the screen. It calculates the horizontal positioning for each text 
 * string based on the window dimensions, ensuring both messages are centered.
 * 
 * @param gd Reference to the `GameData` object containing the window size, 
 *           which is used to determine the position of the text.
 * 
 * @note This function assumes that the screen dimensions in `window_size` are 
 *       sufficient to display the messages centered within the window.
 */
void draw_welcome_screen(GameData& gd) {
    // calculate positions
    const int welcome_y_pos = gd.field_game.window_size.width/2 - WELCOME_STRING.length()/2;
    const int new_game_y_pos = gd.field_game.window_size.width/2 - START_NEW_GAME_STRING.length()/2;
    const int x_pos = gd.field_game.window_size.height/2;
    // view sentences on screen
    gui::draw_string(x_pos - 5, welcome_y_pos, WELCOME_STRING);
    gui::draw_string(x_pos - 3, new_game_y_pos, START_NEW_GAME_STRING);
}

/**
 * @brief Displays the level transition screen with the current level number.
 * 
 * This function renders a level change message and the current level number 
 * centered on the screen. The level string is displayed just above the level 
 * number, both horizontally centered within the window.
 * 
 * @param gd Reference to the `GameData` object containing the current level 
 *           and window size, used for determining the display position.
 * 
 * @note This function assumes the screen dimensions are sufficient for 
 *       centering the messages based on the calculated coordinates.
 */
void draw_level_change_screen(GameData& gd) {
    std::string level = std::to_string(gd.field_game.level);
    // calculate positions
    const int level_y_pos = gd.field_game.window_size.width/2 - LEVEL_STRING.length()/2;
    const int level_num_y_pos = gd.field_game.window_size.width/2;
    const int x_pos = gd.field_game.window_size.height/2;
    // view sentences on screen
    gui::draw_string(x_pos - 5, level_y_pos, LEVEL_STRING);
    gui::draw_string(x_pos - 3, level_num_y_pos, level);
}

/**
 * @brief Renders the game over screen with an option to start a new game.
 * 
 * This function displays a "Game Over" message and a prompt to start a new game,
 * both centered on the screen. The messages are positioned relative to the 
 * screen's width and height to ensure they are aligned in the middle.
 * 
 * @param gd Reference to the `GameData` object containing the window size, 
 *           which is used to determine the positioning of the text.
 * 
 * @note This function assumes the screen has sufficient dimensions to display 
 *       the messages centered within the window.
 */
void draw_game_over_screen(GameData& gd) {
    // calculate positions
    const int x_pos = gd.field_game.window_size.height/2;
    const int game_over_y_pos = gd.field_game.window_size.width/2 - GAME_OVER_STRING.length()/2;
    const int new_game_y_pos = gd.field_game.window_size.width/2 - START_NEW_GAME_STRING.length()/2;
    // view sentences on screen
    gui::draw_string(x_pos - 5, game_over_y_pos, GAME_OVER_STRING);
    gui::draw_string(x_pos - 3, new_game_y_pos, START_NEW_GAME_STRING);
}
