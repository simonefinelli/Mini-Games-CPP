/**
 * @file battlefield.h
 * @brief This file contains common structures shared between different game
 * objects.
 * @author SimoX
 * @date 2023-09-09
 */

#ifndef SPACEINVADERS_COMMON_H
#define SPACEINVADERS_COMMON_H

/**
 * @brief Game coordinates are calculated starting form 0.
 */
typedef struct GameCoordinates {
    int x = -1;  // cols
    int y = -1;  // rows
} coords;

typedef struct ObjectSize {
    int width = 0;
    int height = 0;
} size;

#endif //SPACEINVADERS_COMMON_H
