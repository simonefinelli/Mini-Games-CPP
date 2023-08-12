/**
 * @file core.cpp
 * @brief Includes core game functions.
 *
 * This file includes all the principal functions of the game.
 *
 * @author SimoX
 * @date 2023-08-10
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "config.h"
#include "core.h"

#define MAX_RETRIES 6

std::string retrieve_sentence();
std::string make_hidden_sentence(const std::string &sentence);
int generate_number(int min, int max);

/**
 * @brief Configure the game information.
 *
 * @return errors_left, secret_sentence, hidden_sentence in a structure.
 */
GameData initialize_game() {
    int errors_left = MAX_RETRIES;
    std::string secret_sentence = retrieve_sentence();
    std::string hidden_sentence = make_hidden_sentence(secret_sentence);

    return GameData {errors_left, secret_sentence, hidden_sentence};
}

/**
 * @brief Get the letter chosen by the Player.
 *
 * @return letter The letter to check.
 */
std::string get_player_choice() {
    std::string player_input;

    bool correct_input = false;
    do {
        std::cout << "Enter a letter: ";
        std::cin >> player_input;

        // player input to upper
        std::transform(player_input.begin(), player_input.end(),
                       player_input.begin(), ::toupper);

        if (player_input.size() != 1) {
            std::cout << "The input must be a single letter!" << std::endl;
            continue;
        }
        if (player_input.front() < 'A' or player_input.front() > 'Z') {
            std::cout << "The input must be an alphabetic character!"
            << std::endl;
            continue;
        }
        correct_input = true;

    } while (!correct_input);

    return player_input;
}

/**
 * @brief Check if the Player has a match or not, then update the hidden
 * sentence or the error lefts. In the end update the letters already tested
 */
void update_board(const std::string &player_guess, GameData &game_data) {
    std::size_t pos = game_data.secret_sentence.find(player_guess, 0);
    if (pos != std::string::npos) {
        // update hidden sentence
        while (pos != std::string::npos) {
            game_data.hidden_sentence[pos] = player_guess.front();
            pos = game_data.secret_sentence.find(player_guess, pos + 1);
        }
    } else {
        // no matches found
        game_data.errors_left--;
    }

    // update tested letters
    game_data.tested_letters.insert(player_guess.front());
}

/**
 * @brief The Game is over when the errors done by the Player are 6, or when
 * he guess the entire sentence.
 */
bool game_is_over(const GameData &game_data) {
    return game_data.errors_left == 0 or
           (game_data.secret_sentence == game_data.hidden_sentence);
}

/**
 * @brief Retrieve a random sentence from sentences.txt file.
 *
 * @return sentence The sentence to guess.
 */
std::string retrieve_sentence() {
    std::string sentence;

    // open stream
    std::ifstream file {FILE_PATH};
    if (!file.is_open()) {
        std::cerr << "Failed to open sentences.txt using " << FILE_PATH <<
        " path." << std::endl;
        exit(1);
    }
    // get the random sentence
    int row = generate_number(1, FILE_ELEMENTS);
    int curr_cursor = 1;
    std::string line;
    while (std::getline(file, sentence)) {
        if (curr_cursor == row)
            break;
        curr_cursor++;
    }
    // close stream
    file.close();

    return sentence;
}

/**
 * @brief Make a mask sentence from the original using '_' characters.
 *
 * @param secret_sentence The original sentence.
 * @return hidden The transformed sentence.
 */
std::string make_hidden_sentence(const std::string &secret_sentence) {
    std::string hidden = secret_sentence;
    for (char &c : hidden) {
        if (std::isalpha(c))
            c = '_';
    }
    return hidden;
}

/**
 * @brief Generate a random integer in a specific range.
 *
 * @param min The minimum in the range.
 * @param max The maximum in the range.
 * @return The generated integer in the range.
 */
int generate_number(int min, int max) {
    std::random_device rd; // obtain a random seed from hardware
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()

    // set the range
    std::uniform_int_distribution<> distribution(min, max);

    // get random int
    int random_num = distribution(gen);

    return random_num;
}


