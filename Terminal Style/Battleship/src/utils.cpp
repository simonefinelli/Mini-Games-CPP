/**
 * @file core.cpp
 * @brief
 *
 * @author SimoX
 * @date 2023-08-29
 */


#include <algorithm>
#include <random>
#include <regex>
#include "utils.h"

#define COORDS_CHECK_PATTERN "^[a-jA-J](?:[1-9]|10)?$"
#define ORIENT_CHECK_PATTERN "^[HhVv]$"
const std::regex COORDINATES_PATTERN {COORDS_CHECK_PATTERN};
const std::regex ORIENTATION_PATTERN {ORIENT_CHECK_PATTERN};

/**
 * @brief Generate a random integer in a specific range (extremes included).
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

/**
 *
 * @param coords
 * @return
 */
bool coordinates_validation(std::string &coords) {
    if (coords.length() >= 2 and std::regex_match(coords, COORDINATES_PATTERN)) {
        std::transform(coords.begin(), coords.end(),
                       coords.begin(), ::toupper);
        return true;
    } else {
        return false;
    }
}