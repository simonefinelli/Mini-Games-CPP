/**
 * @file core.cpp
 * @brief Includes core game functions.
 *
 * This file includes all the principal functions of the game.
 *
 * @author SimoX
 * @date 2023-08-10
 */

#include <string>
#include <iostream>
#include "core.h"

struct InitData {
    int errors_left = 0;
    std::string secret_sentence {};
    std::string hidden_sentence {};
};

InitData initialize_game();
std::string retrieve_sentence();
std::string make_hidden_sentence(const std::string &sentence);


void play_game() {

    // game initialization
    auto game_data = initialize_game();

//    do {
//        char player_guess = get_player_letter();
//        update_boad(player_guess, game_data); // update_board
//        draw_board(game_data); //draw title and the empty gallows
//    } while (!game_is_over());
//
//    display_result(game_data);
}

/**
 * @brief Configure the game information.
 *
 * @return errors_left, secret_sentence, hidden_sentence in a structure.
 */
InitData initialize_game() {
    int errors_left = 6;
    std::string secret_sentence = retrieve_sentence();
    std::string hidden_sentence = make_hidden_sentence(secret_sentence);
    // draw_board(hidden_sentence); //draw title and the empty gallows

    return InitData {errors_left, secret_sentence, hidden_sentence};
}

/**
 * @brief Retrieve a random sentence from sentences.txt file.
 *
 * @return sentence The sentence to guess.
 */
std::string retrieve_sentence() {
    // TODO connection and retrieve to sentences.txt file
    std::string sentence = "THE BROWN'S FOX!";
    return sentence;
}

/**
 * @brief Make a mask sentence from the original using '_' characters.
 *
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

bool end_game() {
    return true;
}