#include "puzzle.h"

void solve_puzzle(const Room* room) {
    switch (room->id) {
        case 1:
            print("You found a hidden lever in the Entrance Hall!\n");
            break;
        case 2:
            print("You deciphered an ancient text in the Library!\n");
            break;
        case 3:
            print("You assembled a broken sword in the Armory!\n");
            break;
        case 4:
            print("You arranged the dining table correctly in the Dining Room!\n");
            break;
        case 5:
            print("You unlocked a secret compartment in the Garden!\n");
            break;
        case 6:
            print("You mixed a powerful potion in the Laboratory!\n");
            break;
        case 7:
            print("You aligned the telescopes in the Observatory!\n");
            break;
        case 8:
            print("You solved the riddle of the Throne Room!\n");
            break;
        case 9:
            print("You activated the ancient mechanism in the Vault!\n");
            break;
        default:
            print("No puzzle to solve here.\n");
            break;
    }
}