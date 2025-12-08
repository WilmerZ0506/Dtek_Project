#include "puzzle.h"
#include "game.h"
#include "room.h"

void puzzle_life(GameState *state, int id) { // Puzzle that gives life boost // Kenan Hourie
    print("You've solved the puzzle!\n");
    print("+10 HP! \n\n");
    change_player_life(&state->player, +10);
    state->puzzles_solved[id - 1] = 1;   // mark as solved
}

void puzzle_damage(GameState *state, int id) { // Puzzle that gives damage boost // Kenan Hourie
    print("You've solved the puzzle!\n");
    print("+4 DMG \n\n");
    change_damage(&state->player, +4);
    state->puzzles_solved[id - 1] = 1;   // mark as solved
}

void puzzle_protection(GameState *state, int id) { // Puzzle that gives protection boost // Kenan Hourie
    print("You've solved the puzzle!\n");
    print("+2 DEF \n\n");
    change_protection(&state->player, +2);
    state->puzzles_solved[id - 1] = 1;   // mark as solved
}

void puzzle1(GameState *state){ // Puzzle in room 1 // Kenan Hourie
    print("You find three odd looking wall tiles, the third one seems to be more loose then the other two.\n\n");
    print("Which tile will you inspect?\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x04) {
        puzzle_life(state, 1);
    }
    else{
        print("The tile doesn't move, try inspecting another.\n\n");
    }
}
void puzzle2(GameState *state){ // Puzzle in room 2 // Kenan Hourie
    print("After looking around the libarary you come across a bookshelf with five books lacking both title and author\n\n");
    print("The second book looks old and torn up.\n\n");
    print("Which book do you want to pick up and read?\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x02) {
        print("When you try to take the book off the shelf a hidden compartment opens up\n\n");
        puzzle_damage(state, 2);
    }
    else{
        print("You pick up and read the book, it's empty...\n\n");
    }
}
void puzzle3(GameState *state){ // Puzzle in room 3 // Kenan Hourie
    print("In the armory you find a pressure plate\n, and next to it three different metals:\n\n");
    print("Iron, silver and steel\n\n");
    print("The pressure plate is inscribed with a text:\n\nOnly the strongest metal will grant you what you seek\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x04) {
        print("You put the steel on the pressure plate...\n\n");
        puzzle_protection(state, 3);
    }
    else
    {
        print("The metal doesn't seem to trigger the pressure plate...\n\n");
    }
}
void puzzle4(GameState *state){ // Puzzle in room 4 // Kenan Hourie
    print("In the Dining Hall you find a plate full of delicious food!\n");
    print("Will you eat it? (1 to eat it)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x01) {
        print("You eat the delicious food!\n\n");
        puzzle_life(state, 4);
    }
    else{
        print("Are you really gonna leave food on the plate?\n\n");
    }
}
void puzzle5(GameState *state){ // Puzzle in room 6 // Kenan Hourie
    print("In the laboratory you find five differently labeled potions\n");
    print("The potion in the middle is labeled with (Power).\nThe other potions are labeled with (Danger)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if(val == 0x04) {
        print("You drink the potion labeled with (Power)...\n\n");
        puzzle_damage(state, 5);
    }
    else{
        print("You drink one of the potions labeled with (Danger)...\n\n");
        print("The potion puts you to eternal sleep...\n\n");
        state->game_over = 1;
    }

}
void puzzle6(GameState *state){ // Puzzle in room 7 // Kenan Hourie
    print("Four stars blink in the sky. The fourth shines brightest. Which star do you align the telescope with?\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x08) {
        print("Aligning the telescope with the fourth star grants you strength\n\n");
        puzzle_protection(state, 6);
    }
    else {
        print("Perhaps you should align the telescope with the brightest star?\n\n");
    }
}
void puzzle7(GameState *state){ // Puzzle in room 8 // Kenan Hourie
    print("As you approach the throne you hear a voice in your head telling you to sit on it (1 to sit on the throne)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x01) {
        print("Sitting on the throne makes you surge with power.\n\n");
        puzzle_damage(state, 7);
    }
    else {
        print("Listen to the voice in your head\n");
    }

}
void puzzle8(GameState *state){ // Puzzle in room 9 // Kenan Hourie
    print("You find a massive vault door with intricate designs.\n\n");
    if (state->boss_dead){
        print("Having defeated the boss, it seems you now can open the vault...\n");
        print("You open the vault finding a hoard of treasure inside!\n\n");
        print("You've beaten the game! Congratulations!\n");
        state->win = 1;
    } 
    else {
        print("The vault is locked, it seems like a powerful magic is keeping it sealed.\n");
    }
}

void solve_puzzle(GameState *state, const Room* room) { // Solve puzzle based on current room // Kenan Hourie

    int id = room->id;

    if (state->puzzles_solved[id - 1]) {  // Check if puzzle already solved
        print("You have already solved this puzzle.\n\n");
        return;
    }

    switch (room->id) {
        case 1: puzzle1(state); break;
        case 2: puzzle2(state); break;
        case 3: puzzle3(state); break;
        case 4: puzzle4(state); break;
        case 5: print("There is no puzzle, only beautiful scenery\n\n"); print_meny(state->player.current_room); break;
        case 6: puzzle5(state); break;
        case 7: puzzle6(state); break;
        case 8: puzzle7(state); break;
        case 9: puzzle8(state); break;
        default:
            print("No puzzle to solve here.\n");
            break;
    }

}