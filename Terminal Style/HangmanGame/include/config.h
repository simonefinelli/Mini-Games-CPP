#include <set>
#include <string>

#ifndef HANGMANGAME_CONFIG_H
#define HANGMANGAME_CONFIG_H

// path of the file containing the sentences for the game
#define FILE_PATH "../data/sentences.txt"
#define FILE_ELEMENTS 100  // number of sentences in the file

struct GameData {
    int errors_left = 0;
    std::string secret_sentence {};
    std::string hidden_sentence {};
    std::set<char> tested_letters;
};

#endif //HANGMANGAME_CONFIG_H
