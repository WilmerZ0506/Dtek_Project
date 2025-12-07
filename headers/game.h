#ifndef GAME_H
#define GAME_H

#define SW_ADDR (*(volatile int *)0x04000010) // Switches address

#include "dtekv-lib.h"
#include "interrupt.h"
#include "player.h"
#include "boss.h"
#include "timer.h"
#include "room.h"

// Game state structure
typedef struct {
    volatile Timer timer;
    volatile Player player;
    volatile Boss boss;
    volatile int button_pressed;
    volatile int battle_mode;
    volatile int boss_dead; // Kenan Hourie
    volatile int game_over; // Kenan Hourie
    int puzzles_solved[9]; // en flagga per puzzle (1 = löst, 0 = ej löst) // Kenan Hourie
} GameState;

extern GameState state; // Declare global game state

int game_loop(GameState *state);
int get_switches();
void move_next(volatile Player* p);
void move_previous(volatile Player* p);
void print_meny(Room* room);

#endif