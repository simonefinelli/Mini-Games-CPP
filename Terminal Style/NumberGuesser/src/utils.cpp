//
// Created by SimoX on 04/08/23.
//

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include "config.h"
#include "gui.h"
#include "utils.h"

/**
 * @brief Check if the Player's input is 'y', 'yes' or 'Yes'.
 * @param input Pointer to the player's input string.
 */
bool check_response(const std::string &input) {
    std::string lowercase = input;
    std::transform(lowercase.begin(), lowercase.end(),
                   lowercase.begin(), ::tolower);

    return lowercase == "y" || lowercase == "yes";
}

/**
 * @brief Get a Random integer.
 */
int generate_secret_number() {
    std::random_device rd; // obtain a random seed from hardware
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()

    // set the range
    std::uniform_int_distribution<> distribution(RANGE_MIN, RANGE_MAX);

    // get random int
    int random_num = distribution(gen);

    return random_num;
}

/**
 * @brief Calculate the maximum number of attempts for the Player.
 */
int calculate_attempts() {
    double best_attempts = round(static_cast<double>(log2(RANGE_MAX)));
    double bonus_attempts = round(static_cast<double>(best_attempts * 0.3));
    int attempts = static_cast<int>(best_attempts + bonus_attempts);

    return attempts;
}

/**
 * @brief Get Player choice.
 */
int retrieve_player_input() {
    int player_guess;

    while (true) {
        gui::show_insert_message();
        std::cin >> player_guess;
        if (std::cin.fail()) {
            gui::show_warning_message();
            std::cin.clear(); // clear the error state of cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // ignore the remaining input
            continue;
        } else {
            break;
        }
    }

    return player_guess;
}
