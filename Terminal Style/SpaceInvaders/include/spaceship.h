/**
 * @file board.h
 * @brief This file handles oll the data and operation of the spaceships that are
 * involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <string>
#include <vector>

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H

#define HERO_LIVES 3
#define MAX_ALIEN_AMMO 3  // max alien's ammo per screen/level

// shared characteristics between Aliens and Hero
typedef struct SpaceShipCoordinates {
    int x = -1;
    int y = -1;
} coords;

typedef struct SpaceShipSize {
    int width;
    int height;
} size;
// end shared characteristics

// Hero Objects
typedef struct HeroMissile {
    std::string frame0 =  "|";
} Missile;

typedef struct HeroExplosionAnimation {
    std::string frame0 = ".^-_.\n=====";
    std::string frame1 = "._-^.\n=====";
    int active_frame = 0;  // frame0: 0 - frame2: 1
} hero_exp_anim;
// end Hero objects

// Aliens Objects
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
// end Aliens Objects

struct Hero {
    std::string name {};
    coords position {0, 0}; // TODO init with the center of the screen
    Missile equipment {};
    size dimension {5, 2};
    hero_exp_anim animation {};
    int lives = HERO_LIVES;
    int score = 0;
};

struct Alien {
    coords position {0, 0};
    alien_status status {};
    size dimension {0, 0};
    std::vector<Bomb> equipment {MAX_ALIEN_AMMO};
    int ammo = MAX_ALIEN_AMMO;
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

struct Shield {
    coords position = {0, 0};
    const std::vector<std::string> sprite = {
            "/#####\\",
            "#######",
            "#/   \\#"
    };
};

#endif //SPACEINVADERS_SPACESHIP_H
