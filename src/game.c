#include "game.h"
#include "puzzle.h"
#include "boss.h"

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
    print("----------------------------------------------------------------\n\n");
    print_room_info(room);
    print("1. Next Room | ");
    print("2. Previous Room | ");
    print("3. Solve Puzzle | ");
    print("4. Inspect Room \n\n");
}

// Kenan
void battle_step(GameState *state)
{   

    print("----------------------------------------------------------------\n\n");
    print("Choose your action!: \n");
    print("1. Attack | 2. Buff Defense | 3. Buff Attack\n\n");

    while (!state->button_pressed) {}
    state->button_pressed = 0;

    int action = get_switches();

    // Spelarens tur
    switch (action) {
        case 0x01: {
            int dmg = state->player.damage;
            state->boss.life -= dmg;
            print("You attack the Boss for "); print_int(dmg); print(" damage!\n");
            print("Boss HP: "); print_int(state->boss.life); print("\n\n");
            break;
        }

        case 0x02: {
            state->player.protection += 1; // buff
            print("You brace yourself, incoming damage reduced permanently!\n");
            print("+1 DEF\n\n");
            print("Your current DEF: "); print_int(state->player.protection); print("\n\n");
            break;
        }

        case 0x04: {
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

    // Bossens tur direkt efter spelarens
    if (state->boss.life > 0 && state->player.life > 0) {
        print("---------------------------BOSS TURN--------------------------\n\n");
        boss_take_action(&state->boss, &state->player);
    }

    // Kolla om bossen dog
    if (state->boss.life <= 0) {
        print("You have defeated the Boss! Congratulations on your victory!\n\n");
        state->battle_mode = 0;
        state->boss_dead = 1;
    }

    // Kolla om spelaren dog
    if (state->player.life <= 0) {
        print("You've been defeated...\n\n");
        print("---------------------------GAME OVER---------------------------\n\n");
        state->battle_mode = 0;
        stopTimer();
        state->game_over = 1;
        return;
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

        if (!state->game_over && state->battle_mode == 0 &&
        state->boss.current_room == state->player.current_room &&
        !state->boss_dead) {
        print("You have encountered THE BOSS! Commencing battle!\n\n");
        state->battle_mode = 1;
        }

        if (state->battle_mode && !state->game_over) {
            battle_step(state);
        }
        
        //Kenan Hourie
        if (check_timer_done(&state->timer)) {   // ändra check_timer_done att ta GameState*
            state->game_over = 1;
            break;
        }

    }
    return 0;
}