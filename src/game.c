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
    print("---------------------------------------------------------------------\n\n");
    print_room_info(room);
    print("1. Next Room | ");
    print("2. Previous Room | ");
    print("3. Solve Puzzle | ");
    print("4. Inspect Room \n\n");
}

void battle_step(GameState *state)
{   
    print("Choose your action!: \n");
    print("1. Attack | 2. Defend | 3. Heal \n\n");

    while (!state->button_pressed) {}
    state->button_pressed = 0;

    int action = get_switches();
    int now = state->timer.counter;

    // Spelarens tur
    switch (action) {
        case 0x01: 
            if (now - state->last_attack_time >= 5) { // 5 sek cooldown
                int dmg = state->player.damage;
                state->boss.life -= dmg;
                print("You attack the Boss for "); print_int(dmg); print(" damage!\n");
                state->last_attack_time = now;

                print("Boss HP: "); print_int(state->boss.life); print("\n\n");

            } else {
                int left = 5 - (now - state->last_attack_time);
                if (left < 0) left = 0;
                print("Attack is on cooldown ("); print_int(left); print("s left).\n\n");
            }
            break;

        case 0x02:  // Defend
            if (now - state->last_defend_time >= 15) { // 15 sek cooldown
                print("You brace yourself, incoming damage reduced!\n\n");
                state->last_defend_time = now;
                state->player.protection += 10; // tillfällig buff
            } else {
                int left = 15 - (now - state->last_defend_time);
                if (left < 0) left = 0;
                print("Defend is on cooldown ("); print_int(left); print("s left).\n\n");
            }
            break;

        case 0x04: // Heal
            if (now - state->last_heal_time >= 30) { // 30 sek cooldown
                state->player.life += 20; // heal amount
                if (state->player.life > state->player_max_hp) {
                    state->player.life = state->player_max_hp; // cap vid stridens start HP
                }

                print("You heal yourself for 20 HP!\n\n");
                state->last_heal_time = now;

                print("Your HP: "); print_int(state->player.life); print("\n\n");
                updatelife(&state->player);

            } else {
                int left = 30 - (now - state->last_heal_time);
                if (left < 0) left = 0;
                print("Heal is on cooldown("); print_int(left); print("s left).\n\n");
            }
            break;

        default:
            print("Invalid action.\n");
            break;
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
        state->battle_mode = 0;
        stopTimer();
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

        if (state->battle_mode == 0 && state->boss.current_room == state->player.current_room && !state->boss_dead) { // Boss encounters player
            print("You have been attacked! Entering battle mode...\n\n");
            state->battle_mode = 1; // Enter battle mode

            int now = state->timer.counter;
            state->last_attack_time = now - 1000;
            state->last_defend_time = now - 1000;
            state->last_heal_time = now - 1000;
            state->boss.last_action_time = now - 1000;

            state->player_max_hp = state->player.life;
        }

        if (state->battle_mode) // Enter battle mode if triggered
        {
            battle_step(state);
            int now = state->timer.counter;
            boss_take_action(&state->boss, &state->player, now);
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