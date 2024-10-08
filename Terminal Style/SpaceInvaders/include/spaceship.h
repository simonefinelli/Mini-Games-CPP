/**
 * @file spaceship.h
 * @brief This file and the relative implementation collect oll the data and
 * operation of the spaceships that are involved in the Game: Aliens and Hero.
 * @author SimoX
 * @date 2023-09-16
 */

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H

#include <array>
#include <string>
#include <vector>
#include "common.h"
#include "utils.h"
#include "gui.h"

#define MAX_ALIEN_AMMO 5
#define NO_COLLISION (-1)

// ALIEN FLEET
#define ALIEN_PER_ROW 11
#define ALIEN_ROWS 5
#define ALIEN_FLEET_N (ALIEN_PER_ROW * ALIEN_ROWS)
#define SPRITE_FRAME 2
#define FIRST_CLASS_PTS 30
#define SECOND_CLASS_PTS 20
#define THIRD_CLASS_PTS 10
#define INITIAL_FLEET_X_POSITION 8
#define INITIAL_FLEET_Y_POSITION 10
#define Y_OFFSET_BETWEEN_ALIEN (SPRITE_HEIGHT + 1)
#define X_OFFSET_BETWEEN_ALIEN 6
#define ALIEN_EXPLOSION_DURATION 0.2
#define LATERAL_MOVEMENT_STEP 1
#define VERTICAL_MOVEMENT_STEP 1
#define INITIAL_FLEET_SPEED 35
#define FLEET_ADVANCE_STEP 1
#define MAX_BOMBS_IN_PLAY 3
const std::string ALIEN_EXPLOSION_SPRITE[] {R"(\\//)", R"(//\\)"};
const std::string ALIEN_BOMB_SPRITE[] {R"(/)", R"(\)"};
const std::string FIRST_CLASS_ALIEN_SPRITE[]  {R"(/oo\)", R"(<  >)", R"(/oo\)", R"(/^^\)"};
const std::string SECOND_CLASS_ALIEN_SPRITE[] {R"( 66 )", R"(|\/|)", R"(|66|)", R"(/  \)"};
const std::string THIRD_CLASS_ALIEN_SPRITE[]  {R"((--))", R"(/  \)", R"((--))", R"( <> )"};

// Hero
#define HERO_NAME "Player1"
#define HERO_SPRITE_WIDTH 5
#define INITIAL_HERO_X_POSITION ((W_WIDTH / 2 - HERO_SPRITE_WIDTH / 2) - 1)
#define INITIAL_HERO_Y_POSITION (INITIAL_FLEET_Y_POSITION + (ALIEN_ROWS * (SPRITE_HEIGHT + 1) * 2) - 1)
#define HERO_LIVES 3
#define NOT_ON_FIELD (-1)
#define MISSILE_PACE 1
#define HERO_EXPLOSION_DURATION 0.2
const std::string HERO_EXPLOSION_SPRITE[][2] {{R"(.^-_.)", R"(=====)"}, {R"(._-^.)", R"(=====)"}};
const std::string HERO_SPRITE[] {R"(  ^  )", R"(|-V-|)"};


typedef enum AnimationFrame {
    NO_ANIM = -1,
    FRAME_1 = 0,
    FRAME_2
} frame;

typedef enum SpaceshipStatus {
    ALIVE = 0,
    DEAD,
    EXPLODING
} spaceship_status;

/// Hero Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef struct HeroMissile {
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    char frame0 =  '|';
} Missile;

struct HeroExplosionAnimation {
    const std::array<std::string, SPRITE_HEIGHT> frame0 = {
            HERO_EXPLOSION_SPRITE[0][0],
            HERO_EXPLOSION_SPRITE[0][1]
    };
    const std::array<std::string, SPRITE_HEIGHT> frame1 = {
            HERO_EXPLOSION_SPRITE[1][0],
            HERO_EXPLOSION_SPRITE[1][1]
    };
    std::array<std::string, SPRITE_HEIGHT> curr_frame {};
    int curr_frame_idx = 0;
    float timer = FPS * HERO_EXPLOSION_DURATION;

    // overload copy assignment operator
    HeroExplosionAnimation& operator=(const HeroExplosionAnimation& other) {
        if (this != &other) {  // self-assignment check
            // copy only non-const members
            this->curr_frame = other.curr_frame;
            this->curr_frame_idx = other.curr_frame_idx;
            this->timer = other.timer;
            
            // no assignment for const members frame0 and frame1
        }
        return *this;
    }
};

/// Aliens Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef enum AlienType {
    NONE = 0,
    FIRST_CLASS,  // 30 points type
    SECOND_CLASS, // 20 points type
    THIRD_CLASS   // 10 points type
} alien_type;

typedef struct AlienBomb {
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    std::array<std::array<std::string, SPRITE_HEIGHT>, SPRITE_FRAME> sprite ={
            {{ALIEN_BOMB_SPRITE[0], ALIEN_BOMB_SPRITE[1]},
             {ALIEN_BOMB_SPRITE[1], ALIEN_BOMB_SPRITE[0]}}};
    frame animation_frame = FRAME_1;
} Bomb;

struct AlienExplosionAnimation {
    const std::array<std::string, SPRITE_HEIGHT> frame0 = {
            ALIEN_EXPLOSION_SPRITE[0],
            ALIEN_EXPLOSION_SPRITE[1]
    };
    float timer{0};

    // overload copy assignment operator
    AlienExplosionAnimation& operator=(const AlienExplosionAnimation &other) {
        if (this != &other) {  // Self-assignment check
            // Assign non-const members
            this->timer = other.timer;
        }
        return *this;
    }
};

typedef enum FleetDirection {
    RIGHT_DIRECTION = 1,
    LEFT_DIRECTION = 0
} direction;

typedef struct AlienFleetCollisionInfo {
    coords alien_idx = {NO_COLLISION, NO_COLLISION};
} alien_collision;

/// Gameplay Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
struct Hero {
    std::string name {};
    const std::array<std::string, SPRITE_HEIGHT> sprite {HERO_SPRITE[0], HERO_SPRITE[1]};
    coords position {0, 0};
    Missile missile;
    HeroExplosionAnimation explosion {};
    spaceship_status status {};
    int lives = 0;
    int score = 0;

    // overload copy assignment operator
    Hero& operator=(const Hero &other) {
        if (this != &other) {  // Self-assignment check
            // Assign non-const members
            this->name = other.name;
            this->position = other.position;
            this->missile = other.missile;
            this->explosion = other.explosion;
            this->status = other.status;
            this->lives = other.lives;
            this->score = other.score;
            
            // no need to assign `sprite` because it is const
        }
        return *this;
    }
};

struct Alien {
    alien_type type = NONE;
    coords position {NOT_ON_FIELD, NOT_ON_FIELD};
    spaceship_status status {};
    std::array<std::array<std::string, SPRITE_HEIGHT>, SPRITE_FRAME> sprite {};
    AlienExplosionAnimation explosion {};
    std::array<Bomb, MAX_ALIEN_AMMO> bombs {};
    int ammo = MAX_ALIEN_AMMO;
    int points = 0;

    // overload copy assignment operator
    Alien& operator=(const Alien &other) {
        if (this != &other) {  // self-assignment check
            // assign non-const members
            this->type = other.type;
            this->position = other.position;
            this->status = other.status;
            this->sprite = other.sprite;
            this->explosion = other.explosion;
            this->ammo = other.ammo;
            this->points = other.points;
        }
        return *this;
    }
};

struct AlienFleet {
    coords start_position {-1, -1};
    std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS> aliens {};
    direction attack_direction = RIGHT_DIRECTION;
    int bombs_in_play = 0;
    int population = 0;  // number of Aliens in the fleet
    frame animation_frame = NO_ANIM;
    int movement_speed = 0; // how fast Aliens should be move down against the Hero
    int game_line = 0; // current Fleet position in field vertically.
    bool advancing = false;  // flag that indicates if the Fleet is advancing or not during the game

    // overload copy assignment operator
    AlienFleet& operator=(const AlienFleet &other) {
        if (this != &other) {  // self-assignment check
            // assign non-const members
            this->start_position = other.start_position;
            this->aliens = other.aliens;
            this->attack_direction = other.attack_direction;
            this->bombs_in_play = other.bombs_in_play;
            this->population = other.population;
            this->animation_frame = other.animation_frame;
            this->movement_speed = other.movement_speed;
            this->game_line = other.game_line;
            this->advancing = advancing;
            
            // no need to assign `aliens` because it is const
        }
        return *this;
    }
};

struct SpecialAlien {
    coords position {0, 0};
    size dimension {0, 0};
    int points = 0;  // 50 - 100 - 150 - 200 randomly
};

/// Prototypes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void init_hero(Hero& h);
void refresh_hero_on_playfield(Hero& h, key user_choice);
void refresh_missile_position(Hero& h);
void init_fleet(AlienFleet& f);
void check_fleet_collision(AlienFleet& f, Hero &h);
void check_alien_explosion(std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS>& aliens);
void make_fleet_movement(AlienFleet& fleet);
void make_fleet_shoot(AlienFleet& f);
void refresh_bombs_position(AlienFleet& fleet);
void check_hero_collision(AlienFleet& fleet, Hero& hero);
bool is_hero_exploding(Hero& hero);
bool no_alien_explosion(const std::array<std::array<Alien, ALIEN_PER_ROW>, ALIEN_ROWS>& aliens);
void reset_all_alien_bombs(AlienFleet& f);

#endif //SPACEINVADERS_SPACESHIP_H
