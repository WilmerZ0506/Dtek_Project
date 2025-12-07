extern void enable_interrupt(void); // function defined in boot.S

#include "game.h"

int main() {

    state.timer = (Timer){5, 0}; // Initialize timer to 5 minutes
    state.player = (Player){100, 10, 0}; // Initialize player with 100 life and 10 damage
    state.boss = (Boss){125, 25}; // Initialize boss with 150 life and 15 damage
    state.player.current_room = &room1; // Set initial room
    state.boss.current_room = &room7; // Set boss's initial room
    state.button_pressed = 0; // Initialize button pressed flag
    state.battle_mode = 0; // Initialize battle mode flag
    state.boss_dead = 0; // Initialize boss dead flag

    create_rooms();
    enable_interrupt(); // Enable interrupts
    game_loop(&state); // Start the game loop
    return 0;
}
