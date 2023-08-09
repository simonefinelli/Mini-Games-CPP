#include <string>

#ifndef NUMBER_GUESSER_UTILS_H
#define NUMBER_GUESSER_UTILS_H

int calculate_attempts();

int generate_secret_number();

bool check_response(const std::string &input);

int retrieve_player_input();

#endif //NUMBER_GUESSER_UTILS_H
