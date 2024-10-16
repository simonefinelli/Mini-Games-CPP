#include "vec2D_utils.h"
#include <cmath>

static const float EPSILON = 0.0001f;  // tolerance for floating-point calculations

bool is_equal(float x, float y) {
    return fabs(x - y) < EPSILON;
}

bool is_greaten_than_or_equal(float x, float y) {
    return (x > y) or is_equal(x, y);    
}

bool is_less_than_or_equal(float x, float y) {
    return x < y || is_equal(x, y);
}