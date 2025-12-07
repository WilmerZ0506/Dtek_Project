#ifndef GAME_H
#define GAME_H

#define SW_ADDR (*(volatile int *)0x04000010) // Switches address

#include "dtekv-lib.h"
#include "interrupt.h"
#include "player.h"
#include "boss.h"
#include "timer.h"
#include "room.h"

typedef struct { // Game state structure // Kenan Hourie & Wilmer Zetterström
    volatile Timer timer; 
    volatile Player player; 
    volatile Boss boss; 
    volatile int button_pressed; // Button pressed flag
    volatile int battle_mode; // Battle mode flag
    volatile int boss_dead; // Boss dead flag
    volatile int game_over; // Game over flag
    volatile int win; // Win flag
    volatile int puzzles_solved[9]; // Flag for solved puzzles
} GameState;

extern GameState state; // Declare global game state

int game_loop(GameState *state);
int get_switches();
void move_next(volatile Player* p);
void move_previous(volatile Player* p);
void print_meny(Room* room);

#endif