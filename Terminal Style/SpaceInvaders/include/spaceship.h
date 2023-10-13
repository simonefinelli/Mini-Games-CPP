/**
 * @file spaceship.h
 * @brief This file and the relative implementation collect oll the data and
 * operation of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#include <array>
#include <string>
#include <vector>
#include "battlefield.h"
#include "common.h"

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H

#define MAX_ALIEN_AMMO 3

// Hero
#define HERO_NAME "Player1"
#define HERO_SPRITE_WIDTH 5
#define HERO_LIVES 3
#define NOT_ON_FIELD (-1)
#define MISSILE_PACE 1
#define NO_COLLISION (-1)
const std::string HERO_SPRITE[] {R"(  ^  )", R"(|-V-|)"};

// ALIEN FLEET
#define ALIEN_PER_ROW 11
#define ALIEN_ROWS 5
#define SPRITE_FRAME 2
#define FIRST_CLASS_PTS 30
#define SECOND_CLASS_PTS 20
#define THIRD_CLASS_PTS 10
#define INITIAL_FLEET_X_POSITION 8
#define INITIAL_FLEET_Y_POSITION 10
#define Y_OFFSET_BETWEEN_ALIEN (SPRITE_HEIGHT + 1)
#define X_OFFSET_BETWEEN_ALIEN 6
#define ALIEN_EXPLOSION_DURATION 0.4
const std::string ALIEN_EXPLOSION_SPRITE[] {"\\\\//", "//\\\\"};


/// Hero Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct HeroMissile {
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    char frame0 =  '|';
} Missile;

struct HeroExplosionAnimation {
    const std::string frame0 = ".^-_.\n=====";  // TODO modify
    const std::string frame1 = "._-^.\n=====";  // TODO modify
    int active_frame = 0;  // frame0: 0 - frame2: 1  // TODO make sense?
};

typedef struct ShieldCollisionInfo {
    int shield_idx = NO_COLLISION;
    coords shield_part_hit = {NO_COLLISION, NO_COLLISION};
} shield_collision;

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
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    bomb_anim animation {};
} Bomb;

struct AlienExplosionAnimation {
    const std::array<std::string, SPRITE_HEIGHT> frame0 = {
            ALIEN_EXPLOSION_SPRITE[0],
            ALIEN_EXPLOSION_SPRITE[1]
    };
    float timer = FPS * ALIEN_EXPLOSION_DURATION;
    int active_frame = 0;  // frame0: 0 - frame2: 1  // TODO make sense?
};

typedef enum FleetDirection {
    RIGHT_DIRECTION = 0,
    LEFT_DIRECTION,
    DOWN_DIRECTION
} direction;

typedef enum AnimationFrame {
    NO_ANIM = -1,
    FRAME_1 = 0,
    FRAME_2
} frame;

typedef struct AlienFleetCollisionInfo {
    coords alien_idx = {NO_COLLISION, NO_COLLISION};
} alien_collision;

/// Gameplay Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
struct Hero {
    std::string name {};
    const std::array<std::string, SPRITE_HEIGHT> sprite = {HERO_SPRITE[0], HERO_SPRITE[1]};
    coords position {0, 0};
    Missile missile {};
    HeroExplosionAnimation explosion {};
    int lives = 0;
    int score = 0;
};

struct Alien {
    alien_type type = NONE;
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    alien_status status {};
    std::array<std::array<std::string, SPRITE_HEIGHT>, SPRITE_FRAME> sprite = {};
    AlienExplosionAnimation explosion {};
    std::array<Bomb, MAX_ALIEN_AMMO> bombs {};
    int ammo = MAX_ALIEN_AMMO;
    int points = 0;
};

struct AlienFleet {
    coords start_position {-1, -1};
    std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> aliens {};
    direction attack_direction = RIGHT_DIRECTION;
    int bombs_in_play = 0;
    int population = 0;  // number of Aliens in the fleet
    frame animation_frame = NO_ANIM;
    float movement_speed = 0.0; // how fast Aliens should be move down against the Hero
    int game_line = 0; // current Fleet position in field vertically. (used to update the movement speed)
};

struct SpecialAlien {
    coords position {0, 0};
    size dimension {0, 0};
    int points = 0;  // 50 - 100 - 150 - 200 randomly
};

/// Prototypes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void init_hero(Hero &h);

void refresh_missile_position(Hero &h);

void check_shield_collision(std::array<FieldShield, SHIELD_NUMBER> &shields, Missile &m);

void init_fleet(AlienFleet &f);

void check_fleet_collision(AlienFleet &f, Hero &h);

void check_alien_explosion(std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> &aliens);

void make_fleet_movement(AlienFleet &fleet);

#endif //SPACEINVADERS_SPACESHIP_H
