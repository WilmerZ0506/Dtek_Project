#ifndef PLAYER_H
#define PLAYER_H

#include "room.h"
#include "dtekv-lib.h"

#define LED_ADDR (*(volatile int *)0x04000000) // LED display address

typedef struct { // Player structure
    int life; 
    int damage;
    int protection;
    Room* current_room;
} Player;

void updatelife(volatile Player* p);
void change_life(volatile Player* p, int life);
void change_damage(volatile Player* p, int damage);
void change_protection(volatile Player* p, int protection);

#endif