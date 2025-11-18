extern void enable_interrupt(void); // function defined in boot.S

#include "game.h"
#include "dtekv-lib.h"

int main() {
    state.timer = (Timer){1, 30}; // Initialize timer to 1 minute 30 seconds
    state.player = (Player){100, 10}; // Initialize player with 100 life and 10 damage
    state.button_pressed = 0; // Initialize button pressed flag

    enable_interrupt(); // Enable interrupts
    startTimer(); // Start the timer
    game_loop(&state); // Start the game loop
    return 0;
}
