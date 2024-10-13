/**
 * @file battlefield.h
 * @brief This file contains common structures shared between different game
 * objects and files.
 * @author SimoX
 * @date 2023-09-09
 */

#ifndef SPACEINVADERS_COMMON_H
#define SPACEINVADERS_COMMON_H

#define FPS 30

// playing field
#define W_WIDTH 80 // columns
#define W_HEIGHT 42 // rows
#define FIELD_TOP_BOUNDARY_OFFSET 3

// spaceships height
#define SPRITE_HEIGHT 2
#define SPRITE_WIDTH 4
#define UFO_SPRITE_WIDTH 7
#define UFO_SPRITE_HEIGHT 2

/**
 * @brief Game coordinates are calculated starting form 0.
 */
typedef struct GameCoordinates {
    int x = -1;  // cols
    int y = -1;  // rows
} coords;

/**
 * @brief Game objects sizes are defined as width and height units.
 */
typedef struct ObjectSize {
    int width = 0;
    int height = 0;
} size;

#endif //SPACEINVADERS_COMMON_H
