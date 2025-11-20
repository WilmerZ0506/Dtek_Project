#include "game.h"

GameState state; // Declare global game state

int game_loop(GameState *state) {
    while (1) {

        updatelife(&state->player); // Initialize LED with player's life
        BTN_INTERRUPTMASK = 1; // Enable button interrupt

        if (state->timer.minutes == 0 && state->timer.seconds == 0) { // Timer reached zero
            print("Timer finished!\n");
            break;
        }

        if (state->button_pressed) // If button was pressed
        {
            state->button_pressed = 0; // Reset button pressed flag
            print("Damage taken!\n");
            change_life(&state->player, -state->player.damage); // Decrease player's life by damage amount
            if (state->player.life == 0) { // Player life reached zero
                print("Game Over\n");
                stopTimer();
                break;
            }
        }
    }
    return 0;
}