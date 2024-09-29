/**
 * @file main.cpp
 * @brief Space Invaders main.
 * This file includes the overall logic of the Game.
 * @author SimoX
 * @date 2023-09-09
 */

#include <chrono>
#include <thread>
#include "common.h"
#include "core.h"
#include "gui.h"

const std::chrono::duration<double> FRAME_DURATION(1.0 / FPS); // get first time interval

// prototypes
void game_loop();
bool play_again();

/**
 * @brief Main entry point of the Space Invaders game.
 * 
 * This function initializes the graphical interface using curses library, 
 * runs the game loop repeatedly until the player chooses to stop, 
 * and then shuts down the graphical interface.
 * 
 * Workflow:
 * - Initializes the terminal graphics mode using `gui::initialize_curses()`.
 * - Repeatedly runs the `game_loop()` until the user decides not to play again.
 * - Calls `play_again()` to check if the player wants to continue after each 
 *    game loop iteration.
 * - Shuts down the terminal graphics mode using `gui::shutdown_curses()` before
 *    exiting.
 * 
 * @return int Returns 0 to indicate successful execution.
 */
int main() {
    // initialize graphics
    gui::initialize_curses();
    
    // game procedure
    do {
        game_loop();
    } while (play_again());

    // shutdown graphics
    gui::shutdown_curses();

    return 0;

}

/**
 * @brief Executes the core game loop for Space Invaders.
 * 
 * This function manages the main game loop, handling user input, 
 * updating game data, and rendering the game state on the screen at 
 * regular intervals to maintain a target frame rate (FPS).
 * 
 * Workflow:
 * - Initializes game state by calling `initialize_game()`.
 * - Displays the welcome screen (currently TODO).
 * - Continuously checks for user input (such as movement or quitting).
 * - Updates the game state based on user input using `update_game_data()`.
 * - Redraws the screen using `draw_screen_game()` after each update.
 * - Ensures the game loop runs at the desired frame rate by calculating
 *   and sleeping for the appropriate time.
 * - Exits the loop when the quit condition is met (`IS_QUIT_CHAR`).
 * 
 * Performance Considerations:
 * - The function ensures smooth gameplay by calculating the elapsed time 
 *   between frames and sleeping for the remaining duration to achieve 
 *   the desired FPS (~30).
 * 
 * @note The welcome screen is currently a TODO.
 */
void game_loop() {
    int user_choice;
    bool quit = false;

    // game initialization
    auto game_data = initialize_game();

    // show welcome screen
    // TODO

    // refresh on screen game data
    draw_screen_game(game_data);
    while (!quit) {
        // get current time
        auto curr_time = std::chrono::high_resolution_clock::now();

        // get user movement
        user_choice = get_user_input();
        // check for user input
        if (IS_QUIT_CHAR(user_choice)) { quit = true; continue; }
        // update game data
        update_game_data(game_data, static_cast<key>(user_choice));
        // refresh on screen game data
        draw_screen_game(game_data);

        // calculate how long to sleep to achieve the desired FPS
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - curr_time;
        std::chrono::duration<double> sleep_duration = FRAME_DURATION - elapsed;
        if (sleep_duration > std::chrono::duration<double>(0)) {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}

/**
 * @brief Determines whether the player wants to play the game again.
 * 
 * This function is responsible for prompting the player to decide whether they 
 * want to play another round of Space Invaders after a game session ends.
 * 
 * @return bool Returns `true` if the player chooses to play again, 
 *              otherwise returns `false`.
 * 
 * @note The current implementation is a placeholder and always returns `false`.
 * 
 * @todo Implement logic to determine if the player wish to continue playing or not.
 */
bool play_again() {
    return false;
}
