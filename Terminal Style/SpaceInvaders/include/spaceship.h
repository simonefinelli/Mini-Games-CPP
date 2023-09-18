/**
 * @file spaceship.h
 * @brief This file handles oll the data and operation of the spaceships that are
 * involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <string>
#include <vector>
#include "common.h"

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H

#define MAX_ALIEN_AMMO 3  // max alien's ammo per screen/levelC
#define NOT_ON_FIELD (-1)


/// Hero Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct HeroMissile {
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    std::string frame0 =  "|";
} Missile;

typedef struct HeroExplosionAnimation {
    std::string frame0 = ".^-_.\n=====";
    std::string frame1 = "._-^.\n=====";
    int active_frame = 0;  // frame0: 0 - frame2: 1  // TODO make sense?
} hero_exp_anim;

/// Aliens Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef enum AlienType {
    NONE = 0,
    FIRST_CLASS,  // 30 points type
    SECOND_CLASS, // 20 points type
    THIRD_CLASS   // 10 points type
} alien_type;

typedef enum AlienStatus {
    ALIVE = 0,
    DEAD,
    EXPLODING
} alien_status;

typedef struct AlienBombAnimation {
    std::string frame0 = "<";
    std::string frame1 = ">";
    int active_frame = 0;  // frame0: 0 - frame2: 1
} bomb_anim;

typedef struct AlienBomb {
    coords position {0, 0};
    bomb_anim animation {};
} Bomb;

typedef enum FleetDirection {
    RIGHT = 0,
    LEFT
} direction;

/// Gameplay Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
struct Hero {
    std::string name {};
    coords position {0, 0};
    Missile equipment {};
    size dimension {0, 0};
    hero_exp_anim animation {};
    int lives = 0;
    int score = 0;
};

struct Alien {
    alien_type type {};
    coords position {0, 0};
    alien_status status {};
    size dimension {0, 0};
    std::vector<Bomb> equipment {MAX_ALIEN_AMMO};
    int ammo = MAX_ALIEN_AMMO;
    int points = 0;
};

struct AlienFleet {
    std::vector<std::vector<Alien>> aliens {};
    direction attack_direction = RIGHT;
    int bombs_in_play = 0;
    float speed_movement = 0.0; // how fast Aliens should be move down against the Hero
    float explosion_duration = 0.0;
    int population = 0;  // number of Aliens in the fleet
    int line_position = 0;  // fleet height in the Playing Field
};

struct SpecialAlien {
    coords position {0, 0};
    size dimension {0, 0};
    int points = 0;  // 50 - 100 - 150 - 200 randomly
};

#endif //SPACEINVADERS_SPACESHIP_H
