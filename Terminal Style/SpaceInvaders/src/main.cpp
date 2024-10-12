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
    game_loop();

    // shutdown graphics
    gui::shutdown_curses();

    return 0;

}

/**
 * @brief Executes the core game loop for Space Invaders.
 * 
 * This function runs the main loop for the game, managing user input, updating
 * the game state, and rendering the updated state at each frame. It maintains 
 * a target frame rate (FPS) by calculating frame time and sleeping as needed.
 * 
 * Detailed Workflow:
 * - Initializes the game state by calling `initialize_game()`.
 * - Initially draws the game state on the screen using `draw_screen_game()`.
 * - Enters a continuous loop that:
 *   - Captures user input via `get_user_input()`.
 *   - Checks for the quit condition with `IS_QUIT_CHAR()`.
 *   - Updates the game state by calling `update_game_data()` with the user's input.
 *   - Monitors the game state for game over or win conditions using `check_game_status()`.
 *   - Redraws the updated game state on the screen.
 *   - Pauses the game as needed through `pause_game()`.
 *   - Manages timing to maintain consistent FPS by calculating the elapsed time 
 *     and adjusting the sleep duration to match `FRAME_DURATION`.
 * - Exits the loop and terminates the game when the quit condition is met.
 * 
 * Performance Considerations:
 * - The loop calculates the exact duration taken by each iteration, subtracts 
 *   that from the target frame duration, and sleeps for the remainder. This 
 *   ensures smooth gameplay by adhering closely to the desired FPS (~30).
 * - Game logic and rendering are optimized to prevent unnecessary delays 
 *   within each iteration.
 */
void game_loop() {
    int user_choice;

    // game initialization
    auto game_data = initialize_game();

    // refresh on screen game data
    draw_screen_game(game_data);
    while (true) {
        // get current time
        auto curr_time = std::chrono::high_resolution_clock::now();

        // get user choice
        user_choice = get_user_input();
        if (IS_QUIT_CHAR(user_choice)) { break; }
        // update game data
        update_game_data(game_data, static_cast<key>(user_choice));
        // check game status
        check_game_status(game_data);
        // refresh on screen game data
        draw_screen_game(game_data);
        // check if we have to pause the game
        pause_game(game_data);

        // calculate how long to sleep to achieve the desired FPS
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - curr_time;
        std::chrono::duration<double> sleep_duration = FRAME_DURATION - elapsed;
        if (sleep_duration > std::chrono::duration<double>(0)) {
            std::this_thread::sleep_for(sleep_duration);
        }
    }
}
