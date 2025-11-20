#ifndef GAME_H
#define GAME_H

#include "timer.h"
#include "interrupt.h"
#include "player.h"
#include "dtekv-lib.h"

typedef struct { // Game state structure
    volatile Timer timer;
    volatile Player player;
    volatile int button_pressed;
} GameState;

extern GameState state;

int game_loop(GameState *state);

#endif