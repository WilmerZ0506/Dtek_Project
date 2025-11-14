extern void enable_interrupt(void); // function defined in boot.S

#include "timer.h"
#include "interrupt.h"
#include "player.h"
#include "dtekv-lib.h"

volatile Timer timer = {0, 30}; // Example timer set to 0 minutes and 30 seconds
volatile Player player = {100, 10}; // Example player with 100 life and 10 damage

int main()
{   
    updatelife(&player); // Initialize LED with player's life
    BTN_INTERRUPTMASK = 1; // Enable button interrupt
    enable_interrupt(); // Enable interrupts
    startTimer(); // Start the timer

    while (1)
    {
        if(timer.minutes == 0 && timer.seconds == 0) { // Timer reached zero
            print("Timer finished!\n");
            break;
        }

        if (button_pressed) // If button was pressed
        {
            button_pressed = 0; // Reset button pressed flag
            print("Damage taken!\n");
            change_life(&player, -player.damage); // Decrease player's life by damage amount
            if (player.life == 0) { // Player life reached zero
                print("Game Over\n");
                stopTimer();
                break;
            }
        }
    }
    return 0;
}