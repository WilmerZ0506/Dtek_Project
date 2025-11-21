#include "player.h"

void updatelife(volatile Player* p) // Update LED display based on player's life
{
    int percent = p->life / 10; // Get life percentage (0-10)
    int mask = (1 << percent) - 1; // Create bitmask for LED display
    LED_ADDR = mask;
}

void change_life(volatile Player* p, int life) // Change player's life and update LED
{
    p->life += life;
    if (p->life < 0) p->life = 0; // Prevent negative life
    if (p->life > 100) p->life = 100; // Cap life at 100
    updatelife(p);
}

void change_damage(volatile Player* p, int damage) // Change player's damage
{
    p->damage = damage;
}

void change_protection(volatile Player* p, int protection) // Change player's protection
{
    p->protection = protection;
}