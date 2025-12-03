#include "game.h"

GameState state; // Declare global game state

int get_switches()
{
    return SW_ADDR & 0x0F; // Return lower 4 bits of switch state
}

void move_next(volatile Player *p) // Move player to next room
{
    p->current_room = p->current_room->next_room;
}

void move_previous(volatile Player *p) // Move player to previous room
{
    p->current_room = p->current_room->previous_room;
}

void print_meny(Room* room) // Print menu options
{
    print("---------------------------------------------------------------------\n\n");
    print_room_info(room);
    print("1. Next Room | ");
    print("2. Previous Room | ");
    print("3. Inspect Room | ");
    print("4. Solve Puzzle \n\n");
}

void battle_mode(GameState *state) // Handle battle mode
{
    while (state->battle_mode)
    {
        //skriv här kinini
        // gör state->battle_mode = 0; när striden är över
        print("In battle mode! (This is a placeholder, implement battle logic here)\n");
        state->battle_mode = 0; // Exit battle mode for now
        state->boss_dead = 1; // Mark boss as dead
    }
}

int game_loop(GameState *state)
{
    BTN_INTERRUPTMASK = 1; // Enable button interrupt
    updatelife(&state->player); // Initialize LED with player's life
    print("Press to start the game!\n\n");

    while (!state->button_pressed) // Wait for button press to start
    {
    }

    state->button_pressed = 0;

    print_meny(state->player.current_room);
    startTimer();

    Room *last_room = state->player.current_room; // Track last room for menu updates

    while (1)
    {
        if (state->button_pressed) // Check for button press
        {
            state->button_pressed = 0;

            int switches = get_switches();

            switch (switches)
            {
            case 0x01: // First switch
                move_next(&state->player);
                break;
            case 0x02: // Second switch
                move_previous(&state->player);
                break;
            case 0x04: // Third switch
                inspect_room(state->player.current_room);
                break;
            case 0x08: // Fourth switch
                solve_puzzle(state->player.current_room);
                break;
            default:
                break;
            }

            if (state->player.current_room != last_room) // Print menu if room changed
            {
                print_meny(state->player.current_room);

                last_room = state->player.current_room;
            }
        }

        if (state->battle_mode == 0 && state->boss.current_room == state->player.current_room && !state->boss_dead) { // Boss encounters player
            print("You have been attacked! Entering battle mode...\n");
            state->battle_mode = 1; // Enter battle mode
        }

        if (state->battle_mode) // Enter battle mode if triggered
        {
            battle_mode(state);
        }

        if (check_timer_done(&state->timer)) // Check if timer is done
        {
            print("Game Over! Time's up.\n");
            stopTimer();
            break;
        }
    }
    return 0;
}