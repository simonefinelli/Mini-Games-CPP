/**
 * @file main.cpp
 * @brief Number guesser Game.
 *
 * This file includes the core of the Game.\n
 * It will take in input the player's choices and will handle all kind of
 * exceptions.
 *
 * @author SimoX
 * @date 2023-08-03
 */


#include <iostream>
#include <string>
#include "gui.h"
#include "utils.h"


bool restart_game();

int main() {
    int player_guess;

    // game initialization
    int secret_number = generate_secret_number();
    int attempts = calculate_attempts();
    int guess_counter = 1;

    gui::show_welcome();
    while (true) {
        gui::show_ongoing_bar(guess_counter, attempts);
        player_guess = retrieve_player_input();

        // game status check
        if (player_guess == secret_number) {
            gui::show_greetings();
        } else if (guess_counter == attempts) {
            gui::show_end_game_message(secret_number);
        } else {
            gui::show_feedback(player_guess, secret_number);
            guess_counter++;
            continue;
        }

        // game restart choice
        if (restart_game()) {
            gui::show_welcome();
            // game re-initialization
            secret_number = generate_secret_number();
            attempts = calculate_attempts();
            guess_counter = 1;
        } else {
            break;
        }
    }
    gui::show_leave_message();

    return 0;
}

bool restart_game() {
    std::string player_input;

    gui::draw_blank_line();
    gui::show_continue_game_message();

    std::cin >> player_input;
    if (check_response(player_input)) {
        gui::clear_board();
        return true;
    } else {
        return false;
    }
}
