#ifndef PLAYER_H
#define PLAYER_H

#define LED_ADDR (*(volatile int *)0x04000000) // LED display address

#include "dtekv-lib.h"
#include "room.h"

typedef struct Boss Boss; // Forward declaration

typedef struct Player{ // Player structure
    int life; 
    int damage;
    int protection;
    Room* current_room;
} Player;

void updatelife(volatile Player* p);
void player_attack(volatile Player* p, volatile Boss* b);
void change_player_life(volatile Player* p, int life);
void change_damage(volatile Player* p, int damage);
void change_protection(volatile Player* p, int protection);

#endif