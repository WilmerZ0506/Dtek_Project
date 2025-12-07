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
    volatile int boss_dead;
    int puzzles_solved[9]; // en flagga per puzzle (1 = löst, 0 = ej löst)

    // Cooldowns (i sekunder)
    int attack_cd;
    int defend_cd;
    int heal_cd;

    // Senaste tidpunkter (t.ex. timer.counter eller egen tidsräknare)
    int last_attack_time;
    int last_defend_time;
    int last_heal_time;

    int player_max_hp;
} GameState;

extern GameState state; // Declare global game state

int game_loop(GameState *state);
int get_switches();
void move_next(volatile Player* p);
void move_previous(volatile Player* p);
void print_meny(Room* room);
void battle_mode(GameState *state);

#endif