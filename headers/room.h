// headers/room.h
#ifndef ROOM_H
#define ROOM_H

#include "dtekv-lib.h"

typedef struct Room { // Room structure
    int id;
    char* name;
    char* description;
    struct Room* next_room; // Pointer to the next room
    struct Room* previous_room; // Pointer to the previous room
} Room;

extern Room room1, room2, room3, room4, room5, room6, room7, room8, room9; // Declare rooms

void create_rooms();
void print_room_info(const Room* room);
void inspect_room(const Room* room);

#endif
