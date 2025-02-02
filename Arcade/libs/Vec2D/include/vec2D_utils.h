#ifndef VEC2D_UTILS_H
#define VEC2D_UTILS_H

static const float EPSILON = 1e-4f;  // tolerance for floating-point calculations

bool is_equal(float x, float y);
bool is_greaten_than_or_equal(float x, float y);
bool is_less_than_or_equal(float x, float y);

#endif // VEC2D_UTILS_H