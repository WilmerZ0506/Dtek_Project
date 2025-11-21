#ifndef GAME_H
#define GAME_H

#include "timer.h"
#include "interrupt.h"
#include "player.h"
#include "room.h"
#include "puzzle.h"
#include "dtekv-lib.h"

#define SW_ADDR (*(volatile int *)0x04000010) // Switches address

typedef struct { // Game state structure
    volatile Timer timer;
    volatile Player player;
    volatile int button_pressed;
} GameState;

extern GameState state;

int game_loop(GameState *state);
int get_switches();
void move_next(volatile Player* p);
void move_previous(volatile Player* p);

#endif