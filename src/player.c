#include "player.h"
#include "boss.h"

void updatelife(volatile Player* p) { // Update LED display with player's life // Wilmer Zetterström
    int percent = p->life / 10;
    if (percent > 10) percent = 10;
    if (percent < 0) percent = 0;

    int mask = (1 << percent) - 1; // Create bitmask for LED display
    LED_ADDR = mask;
}

void player_attack(volatile Player* p, volatile Boss* b) // Player attacks boss // Wilmer Zetterström
{
    change_boss_life(b, -p->damage);
}

void change_player_life(volatile Player* p, int delta) { // Change player's life // Wilmer Zetterström
    p->life += delta;
    if (p->life < 0) p->life = 0; // Stop negative values
    updatelife(p);
}

void change_damage(volatile Player* p, int damage) // Change player's damage // Wilmer Zetterström
{
    p->damage += damage;
}

void change_protection(volatile Player* p, int protection) // Change player's protection // Wilmer Zetterström
{
    p->protection += protection;
}
