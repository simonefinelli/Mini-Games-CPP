#include "graphics_utils.h"

#include <iostream>
#include <cmath>
#include <algorithm>

/**
 * 
 */
unsigned int calculate_number_of_segments(float radius) {
    unsigned number_of_segments = std::max(3u, static_cast<unsigned>(std::ceil(M_PI * std::sqrt(radius))));
    std::cout << "number of segments: " << number_of_segments << std::endl;

    return number_of_segments;
}