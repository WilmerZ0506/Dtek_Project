#ifndef PLAYER_H
#define PLAYER_H

#define LED_ADDR (*(volatile int *)0x04000000) // LED display address

typedef struct { // Player structure
    int life; 
    int damage; 
} Player;

void updatelife(volatile Player* p);
void change_life(volatile Player* p, int life);

#endif