#include "boss.h"
#include "player.h"

void change_boss_life(volatile Boss* b, int life) // Change boss's life
{
    b->life += life;
    if (b->life < 0) b->life = 0; // Prevent negative life
}

void boss_attack(volatile Boss* b, volatile Player* p) // Boss attacks player
{
    change_player_life(p, p->protection * (-b->damage)); // Reduce player's life considering protection
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