#include "interrupt.h"

static int tick_count = 0; // Counts timer ticks (100ms each)
static int debounce_counter = 0; // Debounce counter for button press
static int boss_timer = 0; // Timer for boss movement

void handle_interrupt(unsigned cause) // Handle interrupts based on cause
{
    if (cause == 16) // Timer interrupt
    {
        TIMER_STATUS = 0; // Acknowledge interrupt
        tick_count++; // Increment tick count
        boss_timer++; // Increment boss timer

        if (tick_count == 10) // 1 second has passed (10 * 100ms)
        {
            tick_count = 0; // Reset tick count
            tick(&state.timer, -1); // Decrement timer by 1 second
            state.timer.counter++;  // Increment elapsed time for cooldowns
            updateTimer(&state.timer); // Update display
        }

        if (debounce_counter > 0) // Handle button debounce
        {
            debounce_counter--; // Decrement debounce counter
        }

        if (boss_timer == 100 && !state.battle_mode && !state.boss_dead) // 10 seconds have passed (100 * 100ms) and not in battle mode
        {
            boss_timer = 0; // Reset boss timer
            change_current_room(&state.boss, &state.player); // Move boss closer to player

            int dist_forward = (state.player.current_room->id - state.boss.current_room->id + 9) % 9;
            int dist_back    = (state.boss.current_room->id - state.player.current_room->id + 9) % 9;

            if (dist_forward == 1 || dist_back == 1) {
                print("YOU HEAR HEAVY FOOTSTEPS NEARBY...\n\n");
            }
        }
    }
    if (cause == 18) // Button interrupt
    {
        if (debounce_counter == 0) // If not in debounce period
        {
            debounce_counter = 5; // Set debounce counter (500ms)
            state.button_pressed = 1; // Set button pressed flag
        }
        BTN_EDGE = BTN_EDGE; // Clear button interrupt
    }
}