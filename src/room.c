// src/room.c
#include "room.h"

Room room1, room2, room3, room4, room5, room6, room7, room8, room9; // Declare rooms

void create_rooms() { // Initialize rooms and their connections // Kenan Hourie
    room1.id = 1;
    room1.name = "Entrance Hall";
    room1.description = " is grand and welcoming.";
    room1.next_room = &room2;
    room1.previous_room = &room9;

    room2.id = 2;
    room2.name = "Library";
    room2.description = " is filled with dusty old books.";
    room2.next_room = &room3;
    room2.previous_room = &room1;

    room3.id = 3;
    room3.name = "Armory";
    room3.description = " holds weapons of all kinds.";
    room3.next_room = &room4;
    room3.previous_room = &room2;

    room4.id = 4;
    room4.name = "Dining Room";
    room4.description = " smells of delicious food.";
    room4.next_room = &room5;
    room4.previous_room = &room3;

    room5.id = 5;
    room5.name = "Garden";
    room5.description = " is peaceful and fragrant.";
    room5.next_room = &room6;
    room5.previous_room = &room4;

    room6.id = 6;
    room6.name = "Laboratory";
    room6.description = " has strange scientific equipment.";
    room6.next_room = &room7;
    room6.previous_room = &room5;

    room7.id = 7;
    room7.name = "Observatory";
    room7.description = " offers a stunning view of the stars.";
    room7.next_room = &room8;
    room7.previous_room = &room6;

    room8.id = 8;
    room8.name = "Throne Room";
    room8.description = " exudes power and authority.";
    room8.next_room = &room9;
    room8.previous_room = &room7;

    room9.id = 9;
    room9.name = "Dungeon";
    room9.description = " is dark and foreboding.";
    room9.next_room = &room1;
    room9.previous_room = &room8;
}

void print_room_info(const Room* room) { // Print room information // Kenan Hourie
    print("You are in the ");
    print(room->name);
    print(". It");
    print(room->description);
    print("\n\n");
}

void inspect_room(const Room* room) { // Inspect the current room // Kenan Hourie
    switch (room->id) {
        case 1:
            print("The Entrance Hall is grand and welcoming.\n\n");
            break;
        case 2:
            print("The Library is filled with dusty old books.\n\n");
            break;
        case 3:
            print("The Armory holds weapons of all kinds.\n\n");
            break;
        case 4:
            print("The Dining Room smells of delicious food.\n\n");
            break;
        case 5:
            print("The Garden is peaceful and fragrant.\n\n");
            break;
        case 6:
            print("The Laboratory has strange scientific equipment.\n\n");
            break;
        case 7:
            print("The Observatory offers a stunning view of the stars.\n\n");
            break;
        case 8:
            print("The Throne Room exudes power and authority.\n\n");
            break;
        case 9:
            print("The Dungeon is dark and foreboding.\n\n");
            break;
        default:
            print("Unknown room.\n\n");
            break;
    }
}
