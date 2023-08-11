/**
 * @file utils.cpp
 * @brief Graphical info.
 *
 * This file includes all the sentences used to show to the player
 * the game status.
 *
 * @author SimoX
 * @date 2023-08-04
 */


#include <iostream>
#include "config.h"
#include "gui.h"

void gui::show_title() {
    std::cout << "========== Welcome to Number Guesser Game ==========" <<
    std::endl;
}

void gui::show_subtitle(int range_min, int range_max) {
    std::cout << "The Secret Number must be found between " <<
              range_min << " and " << range_max << "."<< std::endl;
}

void gui::show_welcome() {
    gui::show_title();
    gui::show_subtitle();
}

void gui::show_greetings() {
    std::cout << "Congratulation you found the Secret Number!" << std::endl;
}

void gui::show_continue_game_message() {
    std::cout << "Want to play again? ";
}

void gui::show_end_game_message(int secret_number) {
    std::cout << "You loose! The secret number was " <<
              secret_number << "!" << std::endl;
}

void gui::show_feedback(int player_guess, int secret_number) {
    if (player_guess < RANGE_MIN or player_guess > RANGE_MAX) {
        std::cout << "The number is out of boundaries!" << std::endl;
    } else if (player_guess > secret_number) {
        std::cout << "The Guess is too high!" << std::endl;
    } else {
        std::cout << "The Guess is too low!" << std::endl;
    }
    gui::draw_blank_line();
}

void gui::show_leave_message() {
    std::cout << "\nBye, bye!" << std::endl;
}

void gui::show_ongoing_bar(int guess_counter, int attempts) {
    std::cout << "[" << guess_counter << "/" << attempts << "] ";
}

void gui::show_insert_message() {
    std::cout << "Insert your choice: ";
}

void gui::show_warning_message() {
    std::cout << "The number is not an integer." << std::endl;
}

void gui::draw_blank_line() {
    std::cout << std::endl;
}

/**
 * Clear the terminal screen based on the operating system.
 */
void gui::clear_board() {
    #ifdef _WIN32 // Windows
        system("cls");
    #else // Unix-like systems (Linux, macOS, etc.)
        system("clear");
    #endif
}