/**
 * @file board.cpp
 * @brief Includes board game graphic behaviour.
 *
 * This file includes all the principal functions to manipulates the Game Board.
 *
 * @author SimoX
 * @date 2023-08-10
 */

#include <iostream>
#include <string>
#include <iterator>
#include "board.h"

const std::string TITLE = R"(
        ╔╗ ╔╗                              ╔═══╗
        ║║ ║║                              ║╔═╗║
        ║╚═╝║╔══╗ ╔═╗ ╔══╗╔╗╔╗╔══╗ ╔═╗     ║║ ╚╝╔══╗ ╔╗╔╗╔══╗
        ║╔═╗║╚ ╗║ ║╔╗╗║╔╗║║╚╝║╚ ╗║ ║╔╗╗    ║║╔═╗╚ ╗║ ║╚╝║║╔╗║
        ║║ ║║║╚╝╚╗║║║║║╚╝║║║║║║╚╝╚╗║║║║    ║╚╩═║║╚╝╚╗║║║║║║═╣
        ╚╝ ╚╝╚═══╝╚╝╚╝╚═╗║╚╩╩╝╚═══╝╚╝╚╝    ╚═══╝╚═══╝╚╩╩╝╚══╝
                      ╔═╝║
                      ╚══╝
)";
const std::string GALLOWS_0 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||       /|\
  ||       / \
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_1 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||       /|\
  ||       /
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_2 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||       /|\
  ||
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_3 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||       /|
  ||
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_4 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||        |
  ||
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_5 = R"(
  /\
= ++ ====== +
  ||        |
  ||        Q
  ||
  ||
 /||\   _________
//||\\  \/\/\/\/\
)";
const std::string GALLOWS_6 = R"(
  /\
= ++ ====== +
  ||        |
  ||
  ||
  ||
 /||\   _________
//||\\  \/\/\/\/\
)";

void clear_board();

/**
 * @brief Draw the title, the gallows and the dying body
 */
void draw_board(const GameData &game_data) {
    clear_board();

    // draw title
    std::cout << TITLE << std::endl;

    // draw gallows
    std::string body_gallows;
    switch (game_data.errors_left) {
        case 0:
            body_gallows = GALLOWS_0;
            break;
        case 1:
            body_gallows = GALLOWS_1;
            break;
        case 2:
            body_gallows = GALLOWS_2;
            break;
        case 3:
            body_gallows = GALLOWS_3;
            break;
        case 4:
            body_gallows = GALLOWS_4;
            break;
        case 5:
            body_gallows = GALLOWS_5;
            break;
        default:
            body_gallows = GALLOWS_6;
    }
    std::cout << body_gallows << std::endl;

    std::cout << "Hidden Sentence: " << game_data.hidden_sentence << std::endl;
    std::cout << std::endl;
    std::cout << "Tested letters: ";
    std::copy(game_data.tested_letters.begin(),
              game_data.tested_letters.end(),
              std::ostream_iterator<char>(std::cout, " "));
    std::cout << std::endl;
}

void display_results(const GameData &game_data) {
    if (game_data.secret_sentence == game_data.hidden_sentence){
        std::cout << "YOU WIN!" << std::endl;
    } else {
        std::cout << "YOU LOOSE! The hidden sentence was: " <<
                  game_data.secret_sentence << std::endl;
    }
}

/**
 * Clear the terminal screen based on the operating system.
 */
void clear_board() {
#ifdef _WIN32 // Windows
    system("cls");
#else // Unix-like systems (Linux, macOS, etc.)
    system("clear");
#endif
}
