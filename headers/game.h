#ifndef GAME_H
#define GAME_H

#define SW_ADDR (*(volatile int *)0x04000010) // Switches address

#include "dtekv-lib.h"
#include "interrupt.h"
#include "player.h"
#include "boss.h"
#include "timer.h"
#include "interrupt.h"
#include "room.h"
#include "puzzle.h"

typedef struct { // Game state structure
    volatile Timer timer;
    volatile Player player;
    volatile Boss boss;
    volatile int button_pressed;
    volatile int battle_mode;
    volatile int boss_dead;
} GameState;

extern GameState state; // Declare global game state

int game_loop(GameState *state);
int get_switches();
void move_next(volatile Player* p);
void move_previous(volatile Player* p);
void print_meny(Room* room);
void battle_mode(GameState *state);

#endif