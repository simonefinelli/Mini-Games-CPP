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
    gd.field_game.state = WELCOME_SCREEN; // TODO after change with WELCOME_SCREEN
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
        case NEW_GAME_CHAR_LOWER:
        case NEW_GAME_CHAR_UPPER:
            return input;
        default:
            return -1;
    }
}

// todo update docstring
/**
 * @brief Updates the game state based on user input and game logic.
 * 
 * This function manages all the updates necessary for each frame of the game. 
 * It processes the Hero's movements, missile updates, collision detection, alien 
 * fleet movements, and bomb interactions. If the Hero is alive, it continuously 
 * updates the game state based on the user input. If the Hero is exploding, it 
 * updates the Hero's explosion status. It also checks the overall game status 
 * and handles game pausing when necessary.
 * 
 * Workflow:
 * - If the Hero is `ALIVE`:
 *   - Moves the Hero based on the user's input (`LEFT`, `RIGHT`, or `SPACE` for
 *      shooting).
 *   - Updates the position of the Hero's missile.
 *   - Checks for collisions between the Hero's missile and shields, aliens, and
 *      bombs.
 *   - Handles alien explosions and fleet movement.
 *   - Manages alien fleet bomb drops and updates their positions.
 *   - Checks for shield collisions with alien bombs and hero collisions with 
 *      alien bombs.
 * 
 * - If the Hero is in an `EXPLODING` state:
 *   - Updates the Hero's explosion animation frame.
 * 
 * Additional game checks:
 * - `check_game_status()`: Determines if the game is over or if the level is complete.
 * - `pause_game()`: Checks if the game needs to be paused based on internal state or 
 *     player actions.
 * 
 * @param gd A reference to the `GameData` object that contains the current game state.
 * @param user_choice The key input from the user, used to control the Hero's actions.
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
        // update exploding frame of the Hero
        update_hero_explosion_status(gd);
    }

    // // check game status
    // check_game_status(gd);

    // // check if we have to pause the game
    // pause_game(gd);
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
            current_gd.field_game.wait_time = 3000;  // todo: make a constant
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
            current_gd.field_game.wait_time = 3000; // todo: make a constant
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
 * //todo
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
        gd.field_game.wait_time = 300;  // milliseconds  //todo make constant
    }
}

/**
 * // todo: complete docstring
 * interval in milliseconds
 */
void pause_game(GameData& gd) {
    if (gd.field_game.wait_time == 0) return;

    std::this_thread::sleep_for(std::chrono::milliseconds(gd.field_game.wait_time));
    // reset waiting time
    gd.field_game.wait_time = 0;
}

/**
 * // todo
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
 * //todo
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
 * //todo
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
 * //todo
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
