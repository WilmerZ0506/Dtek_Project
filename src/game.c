#include "game.h"
#include "puzzle.h"
#include "boss.h"

GameState state; // Declare global game state

int get_switches() // Get current switch states // Wilmer Zetterström
{
    return SW_ADDR & 0x0F; // Return lower 4 bits of switch state
}

void move_next(volatile Player *p) // Move player to next room // Wilmer Zetterström
{
    p->current_room = p->current_room->next_room;
}

void move_previous(volatile Player *p) // Move player to previous room // Wilmer Zetterström
{
    p->current_room = p->current_room->previous_room;
}

void print_meny(Room* room) // Print menu options // Kenan Hourie
{
    print("----------------------------------------------------------------\n\n");
    print_room_info(room);
    print("1. Next Room | ");
    print("2. Previous Room | ");
    print("3. Solve Puzzle | ");
    print("4. Inspect Room \n\n");
}

void battle_step(GameState *state) // One step in the battle sequence // Kenan Hourie
{   

    print("----------------------------------------------------------------\n\n");
    print("Choose your action!: \n");
    print("1. Attack | 2. Buff Defense | 3. Buff Attack\n\n");

    while (!state->button_pressed) {}
    state->button_pressed = 0;

    int action = get_switches();

    // Player's turn
    switch (action) {
        case 0x01: { // attack
            int dmg = state->player.damage;
            state->boss.life -= dmg;
            print("You attack the Boss for "); print_int(dmg); print(" damage!\n");
            print("Boss HP: "); print_int(state->boss.life); print("\n\n");
            break;
        }

        case 0x02: { // buff defense
            state->player.protection += 1; // buff
            print("You brace yourself, incoming damage reduced permanently!\n");
            print("+1 DEF\n\n");
            print("Your current DEF: "); print_int(state->player.protection); print("\n\n");
            break;
        }

        case 0x04: { // buff attack
            state->player.damage += 2; // buff
            print("You eat some leftover shawarma, damage output increased permanently!\n");
            print("+2 ATK\n\n");
            print("Your current ATK: "); print_int(state->player.damage); print("\n\n");
            break;
        }

        default: {
            print("Invalid action.\n\n");
            break;
        }
    }

    // Boss's turn
    if (state->boss.life > 0 && state->player.life > 0) {
        print("---------------------------BOSS TURN--------------------------\n\n");
        boss_take_action(&state->boss, &state->player);
    }

    // Check if the boss is dead
    if (state->boss.life <= 0) {
        print("You have defeated the Boss! Congratulations on your victory!\n\n");
        state->battle_mode = 0;
        state->boss_dead = 1;
    }

    // Check if the player is dead
    if (state->player.life <= 0) {
        print("You've been defeated...\n\n");
        state->battle_mode = 0;
        state->game_over = 1;
        return;
    }
    
}

int game_loop(GameState *state) // Main game loop // Wilmer Zetterström & Kenan Hourie
{
    // Wilmer Zetterström

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

    while (!state->game_over)
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
                solve_puzzle(state, state->player.current_room);
                break;
            case 0x08: // Fourth switch
                inspect_room(state->player.current_room);
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

        // Kenan Hourie

        // Check for boss encounter
        if (!state->game_over && state->battle_mode == 0 &&
        state->boss.current_room == state->player.current_room &&
        !state->boss_dead) {
        print("You have encountered THE BOSS! Commencing battle!\n\n");
        state->battle_mode = 1;
        }

        // Handle battle if in battle mode
        if (state->battle_mode && !state->game_over) {
            battle_step(state);
        }

        // Check if timer is done
        if (check_timer_done(&state->timer)) {
            state->game_over = 1;
            print("Time's up! You've run out of time...\n\n");
            print("---------------------------GAME OVER---------------------------\n\n");
            stopTimer();
            break;
        }

        // Check for game over or win conditions
        if (state->game_over) {
            print("---------------------------GAME OVER---------------------------\n\n");
            stopTimer();
            break;
        }

        if (state->win) {
            print("---------------------------YOU WIN---------------------------\n\n");
            stopTimer();
            break;
        }

    }
    return 0;
}