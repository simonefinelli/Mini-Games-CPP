/**
 * @file spaceship.h
 * @brief This file and the relative header collect all the support functions
 * required by the game.
 * @author SimoX
 * @date 2023-11-04
 */

#include <algorithm>
#include <random>
#include "utils.h"

/**
 * @brief Generate a random integer in a specific range (extremes included).
 *
 * @param min The minimum in the range.
 * @param max The maximum in the range.
 * @return the generated integer in the range.
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
 * @brief Generate a random real number in a specific range (extremes included).
 *
 * @param min The minimum in the range.
 * @param max The maximum in the range.
 * @return the generated integer in the range.
 */
double generate_number(double min, double max) {
    std::random_device rd; // obtain a random seed from hardware
    std::mt19937 gen(rd()); // Standard Mersenne Twister engine seeded with rd()

    // set the range
    std::uniform_real_distribution<double> distribution(min, max);

    // get random double
    double random_num = distribution(gen);

    return random_num;
}