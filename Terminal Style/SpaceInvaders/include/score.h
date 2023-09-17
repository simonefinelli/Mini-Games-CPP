/**
 * @file score.h
 * @brief This file handles the scores obtained during matches.
 * @author SimoX
 * @date 2023-09-17
 */

#include <string>
#include <vector>

#ifndef SPACEINVADERS_SCORE_H
#define SPACEINVADERS_SCORE_H

/**
 * @brief Current Score in a single match.
 */
struct Score {
    int score = 0;
    std::string hero_name {};

};

/**
 * @brief List of past scores. It includes the current score if the list is shown
 * at the end of the match.
 */
struct HighScoreList {
    std::vector<Score> scores {};
};

#endif //SPACEINVADERS_SCORE_H
