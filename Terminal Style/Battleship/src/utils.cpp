//
// Created by simox on 29/08/23.
//

#include <random>
#include "utils.h"

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