#ifndef BOSS_H
#define BOSS_H

#include "dtekv-lib.h"
#include "room.h"

typedef struct Player Player; // Forward declaration

typedef struct Boss{ // Boss structure
    volatile int life;
    volatile int damage;
    volatile int protection; 
    volatile Room* current_room;
    int last_action_time; // Senaste gången bossen agerade
} Boss;

void change_boss_life(volatile Boss* b, int life);
void boss_attack(volatile Boss* b, volatile Player* p);
void change_current_room(volatile Boss* b, volatile Player* p);
void boss_take_action(volatile Boss* b, volatile Player* p, int now);

#endif // BOSS_H