#include "boss.h"
#include "player.h"
#include "game.h"

static unsigned int seed = 123456789;

    int my_rand() {
        seed = seed * 1103515245 + 12345;
        return (seed >> 16) & 0x7FFF; // returnerar ett positivt tal
    }

void boss_take_action(volatile Boss* b,volatile Player* p) {

    int r = my_rand();
    //Slumpa fram en action, 0 för attack, 1 för defend , och 2 för heal
    int choice = r % 2;

    switch (choice){
        case 0: { //Attack
            int dmg = b->damage - p->protection;
            if (dmg < 1) dmg = 1;
            change_player_life(p, -dmg);
            print("Boss attacks for "); print_int(dmg); print(" damage!\n\n");
            print("Your HP: "); print_int(p->life); print("\n\n");
            break;
        }
        case 1: { //Heal
            change_boss_life(b, +10);
            print("The boss heals its wounds! It regains 10 HP!\n\n");
            print("Boss HP: "); print_int(b->life); print("\n\n");
            break;
        }
    }
}

void change_boss_life(volatile Boss* b, int life) // Change boss's life
{
    b->life += life;
    if (b->life < 0) b->life = 0; // Prevent negative life
}

void change_current_room(volatile Boss* b, volatile Player* p) // Change boss's current room
{
    int distance_back = (b->current_room->id - p->current_room->id + 9) % 9; // Assuming 9 rooms in a circular manner
    int distance_forward = (p->current_room->id - b->current_room->id + 9) % 9; // Assuming 9 rooms in a circular manner

    if (distance_back <= distance_forward) { //if distance back is shorter or equal, move back
        b->current_room = b->current_room->previous_room;
    } else { //else move forward
        b->current_room = b->current_room->next_room;
    }
}