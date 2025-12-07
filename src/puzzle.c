#include "puzzle.h"
#include "game.h"
#include "room.h"

// Lägg till funktioner för varje pussel här Kinini
// case 9 ska endast gå att lösa om bossen är besegrad och då vinner spelaren spelet men det ska inte vara något särskilt pussel för det
// kalla dina funktioner i solve_puzzle nedan efter case nummer

void puzzle_life(GameState *state) {
    print("You've solved the puzzle!\n");
    print(" +10 HP! \n");
    change_player_life(&state->player, +10);
}

void puzzle_damage(GameState *state) {
    print("You've solved the puzzle!\n");
    print(" +2 DMG \n");
    change_damage(&state->player, +2);
}

void puzzle_protection(GameState *state) {
    print("You've solved the puzzle!\n");
    print(" +5 DEF \n");
    change_protection(&state->player, +5);
}

void puzzle1(GameState *state){
    print("You find three odd looking wall tiles, the third one seems to be more loose then the other two.\n\n");
    print("Which tile will you inspect?\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x04) {
        puzzle_life(state);
    }
    else{
        print("The tile doesn't move, try inspecting another.\n");
    }
}
void puzzle2(GameState *state){
    print("After looking around the libarary you come across a bookshelf with five books lacking both title and author\n");
    print("The second book looks old and torn up.\n\n");
    print("Which book do you want to pick up and read?\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x02) {
        print("When you try to take the book off the shelf a hidden compartment opens up\n");
        puzzle_damage(state);
    }
    else{
        print("You pick up and read the book, it's empty...\n");
    }
}
void puzzle3(GameState *state){
    print("In the armory you find a pressure plate, and next to it three different metals:\n");
    print("Iron, silver and steel\n\n");
    print("The pressure plate is inscribed with a text:\n\nOnly the strongest metal will grant you what you seek\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x04) {
        print("You put the steel on the pressure plate...\n");
        puzzle_protection(state);
    }
    else
    {
        print("The metal doesn't seem to trigger the pressure plate...\n");
    }
}
void puzzle4(GameState *state){
    print("In the Dining Hall you find a plate full of delicious food!\n");
    print("Will you eat it? (1 to eat it)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x01) {
        print("You eat the delicious food!\n");
        puzzle_life(state);
    }
    else{
        print("Are you really gonna leave food on the plate?\n");
    }
}
void puzzle5(GameState *state){
    print("In the laboratory you find five differently labeled potions\n");
    print("The potion in the middle is labeled with (Power), the other potions are labeled with (Danger)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if(val == 0x04) {
        print("You drink the potion labeled with (Power)...\n");
        puzzle_damage(state);
    }
    else{
        print("You drink one of the potions labeled with (Danger)...\n");
        print("The potion puts you to eternal sleep...\n");
        stopTimer();
    }

}
void puzzle6(GameState *state){
    print("Four stars blink in the sky. The fourth shines brightest. Which star do you align the telescope with?\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x08) {
        print("Aligning the telescope with the fourth star grants you strength\n");
        puzzle_protection(state);
    }
    else {
        print("Perhaps you should align the telescope with the brightest star?\n");
    }
}
void puzzle7(GameState *state){
    print("As you approach the throne you hear a voice in your head telling you to sit on it (1 to perform this action)\n\n");
    while (!state->button_pressed) {}
    state->button_pressed = 0;
    int val = get_switches();
    if (val == 0x01) {
        print("Sitting on the throne makes you surge with power.\n");
        puzzle_damage(state);
    }
    else {
        print("Listen to the voice in your head\n");
    }

}
void puzzle8(GameState *state){
    if (state->boss_dead){
        print("Having defeated the boss, it seems you now can open the vault...\n");
        print("You open the vault finding a hoard of treasure inside!\n");
        print("You've beaten the game! Congratulations!\n");
        stopTimer();
    } 
    else {
        print("The vault is locked, it seems like a powerful magic is keeping it sealed.\n");
    }
}

void solve_puzzle(GameState *state, const Room* room) {

    int id = room->id;

    if (state->puzzles_solved[id]) {
        print("You have already solved this puzzle.\n");
        return;
    }

    switch (room->id) {
        case 1: puzzle1(state); break;
        case 2: puzzle2(state); break;
        case 3: puzzle3(state); break;
        case 4: puzzle4(state); break;
        case 5: print("There is no puzzle, only beautiful scenery\n"); break;
        case 6: puzzle5(state); break;
        case 7: puzzle6(state); break;
        case 8: puzzle7(state); break;
        case 9: puzzle8(state); break;
        default:
            print("No puzzle to solve here.\n");
            break;
    }

    // Markera som löst
    state->puzzles_solved[id] = 1;
}