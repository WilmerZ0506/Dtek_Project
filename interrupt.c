#include "interrupt.h"
#include "timer.h"
#include "dtekv-lib.h"

static int tick_count = 0; // Counts timer ticks (100ms each)
static int debounce_counter = 0; // Debounce counter for button press
volatile int button_pressed = 0; // Flag indicating button press

void handle_interrupt(unsigned cause) // Handle interrupts based on cause
{
    if (cause == 16) // Timer interrupt
    {
        TIMER_STATUS = 0; // Acknowledge interrupt
        tick_count++; // Increment tick count

        if (tick_count == 10) // 1 second has passed (10 * 100ms)
        {
            tick_count = 0; // Reset tick count
            tick(&timer, -1); // Decrement timer by 1 second
            updateTimer(&timer); // Update display
        }

        if (debounce_counter > 0) // Handle button debounce
        {
            debounce_counter--; // Decrement debounce counter
        }
    }
    if (cause == 18) // Button interrupt
    {
        if (debounce_counter == 0) // If not in debounce period
        {
            debounce_counter = 2; // Set debounce counter (200ms)
            button_pressed = 1; // Set button pressed flag
        }
        BTN_EDGE = BTN_EDGE; // Clear button interrupt
    }
}