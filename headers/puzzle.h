#ifndef PUZZLE_H
#define PUZZLE_H

#include "game.h"
#include "room.h"

void puzzle_life(GameState *state, int id);
void puzzle_damage(GameState *state, int id);
void puzzle_protection(GameState *state, int id);
void puzzle1(GameState *state);
void puzzle2(GameState *state);
void puzzle3(GameState *state);
void puzzle4(GameState *state);
void puzzle5(GameState *state);
void puzzle6(GameState *state);
void puzzle7(GameState *state);
void puzzle8(GameState *state);
void solve_puzzle(GameState *state, const Room* room);

#endif