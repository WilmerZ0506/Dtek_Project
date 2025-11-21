#include "game.h"

GameState state; // Declare global game state

int get_switches()
{
    return SW_ADDR & 0x0F; // Return lower 4 bits of switch state
}

void move_next(volatile Player *p)
{
    p->current_room = p->current_room->next_room;
}

void move_previous(volatile Player *p)
{
    p->current_room = p->current_room->previous_room;
}

void print_meny(Room* room)
{
    print("---------------------------------------------------------------------\n\n");
    print_room_info(room);
    print("1. Next Room | ");
    print("2. Previous Room | ");
    print("3. Inspect Room | ");
    print("4. Solve Puzzle \n\n");
}

int game_loop(GameState *state)
{
    BTN_INTERRUPTMASK = 1;      // Enable button interrupt
    updatelife(&state->player); // Initialize LED with player's life
    print("Press to start the game!\n\n");

    while (!state->button_pressed)
    {
    }

    state->button_pressed = 0;

    print_meny(state->player.current_room);
    startTimer();

    Room *last_room = state->player.current_room;

    while (1)
    {
        if (state->button_pressed)
        {
            state->button_pressed = 0;

            int switches = get_switches();

            switch (switches)
            {
            case 0x01:
                move_next(&state->player);
                break;
            case 0x02:
                move_previous(&state->player);
                break;
            case 0x04:
                inspect_room(state->player.current_room);
                break;
            case 0x08:
                solve_puzzle(state->player.current_room);
                break;
            default:
                break;
            }

            if (state->player.current_room != last_room)
            {
                print_meny(state->player.current_room);

                last_room = state->player.current_room;
            }
        }

        if (check_timer_done(&state->timer))
        {
            print("Too slow!");
            break;
        }
    }
    return 0;
}